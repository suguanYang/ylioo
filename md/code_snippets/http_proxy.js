const fs = require("fs");
const path = require("path");
const pkg = require("./package.json");

const port = process.env.PORT || 3000;
let web_o = require("http-proxy/lib/http-proxy/passes/web-outgoing");

const appName = pkg.name;
const removeUrlDuplicateSlash = (url) => url.replace(/([^:]\/)\/+/g, "$1");

web_o = Object.keys(web_o).map(function (pass) {
  return web_o[pass];
});

module.exports = (config, env) => {
  if (env === "development" && config.devServer) {
    const apis = {
      "/custom-extensions": `http://127.0.0.1:${port}/`,
      [`/${appName}`]: `http://127.0.0.1:${port}/`,
    };

    Object.keys(apis).forEach((path) => {
      config.devServer.proxy.push({
        context: [path],
        secure: false,
        changeOrigin: true,
        target: apis[path],
        pathRewrite: (from, req) => {
          let target = from.replace(/\/service/, "");

          if (path === "/custom-extensions") {
            target = from.replace("/custom-extensions", "custom-static");
          }

          const origin = removeUrlDuplicateSlash(
            `${req.protocol}://${req.headers.host}${from}`
          );
          const upstream = removeUrlDuplicateSlash(`${apis[path]}${target}`);

          console.log(`${req.method} [proxy]`);
          console.log(`origin  : ${origin}`);
          console.log(`upstream: ${upstream}`);

          return target;
        },
        selfHandleResponse: true,
        onProxyRes: async (proxyRes, req, res) => {
          const reqUrl = req.url;
          if (
            proxyRes.headers["content-type"] === "text/html" &&
            reqUrl.includes("/main")
          ) {
            return responseInterceptor(
              async (responseBuffer, proxyRes, req, res) => {
                const response = responseBuffer.toString("utf8");
                const isMobile = reqUrl.includes("main-mobile");
                const html = await readHTML(isMobile);
                return response.replace(
                  "<!-- custom_head_start_inject -->",
                  `<!-- custom_head_start_inject -->${html}`
                );
              }
            )(proxyRes, req, res);
          }

          if (!res.headersSent) {
            for (var i = 0; i < web_o.length; i++) {
              if (web_o[i](req, res, proxyRes, {})) {
                break;
              }
            }
          }
          proxyRes.pipe(res);
        },
      });
    });
    config.output.publicPath = `/${appName}/`;
    config.devtool = "source-map";
    config.devServer.client = { overlay: false };
    config.devServer.static = {
      publicPath: `/custom-static`,
      directory: path.resolve(__dirname, "../dist/custom-extensions"),
      watch: true,
    };
  }

  return config;
};

const readHTML = async (isMobile) => {
  const html = fs.readFileSync(
    path.resolve(
      __dirname,
      `../dist/custom-extensions/${
        isMobile ? "main-mobile" : "main"
      }/custom_head_start_inject.html`
    ),
    "utf8"
  );
  return html;
};

import type * as http from 'http';
import * as zlib from 'zlib';

type Interceptor = (
  buffer: Buffer,
  proxyRes: http.IncomingMessage,
  req: http.IncomingMessage,
  res: http.ServerResponse
) => Promise<Buffer | string>;

/**
 * Intercept responses from upstream.
 * Automatically decompress (deflate, gzip, brotli).
 * Give developer the opportunity to modify intercepted Buffer and http.ServerResponse
 *
 * NOTE: must set options.selfHandleResponse=true (prevent automatic call of res.end())
 */
function responseInterceptor(interceptor: Interceptor) {
  return async function proxyRes(
    proxyRes: http.IncomingMessage,
    req: http.IncomingMessage,
    res: http.ServerResponse
  ): Promise<void> {
    const originalProxyRes = proxyRes;
    let buffer = Buffer.from('', 'utf8');

    // decompress proxy response
    const _proxyRes = decompress(proxyRes, proxyRes.headers['content-encoding']);

    // concat data stream
    _proxyRes.on('data', (chunk) => (buffer = Buffer.concat([buffer, chunk])));

    _proxyRes.on('end', async () => {
      // copy original headers
      copyHeaders(proxyRes, res);

      // call interceptor with intercepted response (buffer)
      const interceptedBuffer = Buffer.from(await interceptor(buffer, originalProxyRes, req, res));

      // set correct content-length (with double byte character support)
      res.setHeader('content-length', Buffer.byteLength(interceptedBuffer, 'utf8'));

      res.write(interceptedBuffer);
      res.end();
    });

    _proxyRes.on('error', (error) => {
      res.end(`Error fetching proxied request: ${error.message}`);
    });
  };
}

/**
 * Streaming decompression of proxy response
 * source: https://github.com/apache/superset/blob/9773aba522e957ed9423045ca153219638a85d2f/superset-frontend/webpack.proxy-config.js#L116
 */
function decompress(proxyRes: http.IncomingMessage, contentEncoding: string) {
  let _proxyRes = proxyRes;
  let decompress;

  switch (contentEncoding) {
    case 'gzip':
      decompress = zlib.createGunzip();
      break;
    case 'br':
      decompress = zlib.createBrotliDecompress();
      break;
    case 'deflate':
      decompress = zlib.createInflate();
      break;
    default:
      break;
  }

  if (decompress) {
    _proxyRes.pipe(decompress);
    _proxyRes = decompress;
  }

  return _proxyRes;
}

/**
 * Copy original headers
 * https://github.com/apache/superset/blob/9773aba522e957ed9423045ca153219638a85d2f/superset-frontend/webpack.proxy-config.js#L78
 */
function copyHeaders(originalResponse, response) {
  response.statusCode = originalResponse.statusCode;
  response.statusMessage = originalResponse.statusMessage;

  if (response.setHeader) {
    let keys = Object.keys(originalResponse.headers);

    // ignore chunked, brotli, gzip, deflate headers
    keys = keys.filter((key) => !['content-encoding', 'transfer-encoding'].includes(key));

    keys.forEach((key) => {
      let value = originalResponse.headers[key];

      if (key === 'set-cookie') {
        // remove cookie domain
        value = Array.isArray(value) ? value : [value];
        value = value.map((x) => x.replace(/Domain=[^;]+?/i, ''));
      }

      response.setHeader(key, value);
    });
  } else {
    response.headers = originalResponse.headers;
  }
}