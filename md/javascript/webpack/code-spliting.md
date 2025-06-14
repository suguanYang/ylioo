---
title: "Code Splitting"
---

## Code Splitting

### The main trade-off is:
the main trade-off is:
1. the less shared chunks, the more duplicated modules
2. the more shared chunks, the less chunk fine-grained distribution
3. the more distributed chunks, the more overhead of loading chunks

example: if A, and B are different chunks, suppose they have common module x and y, then we make a seprate chunk called C,
then we get 3 chunks: A, B, and C(x, y)
then if there is another chunk D, and D also import module x, if we do not change the current chunk structure,
and we do not want the D has a duplicate of x, then we need to load chunk C in D,
but if D is the only chunk we loaded, we also loaded a unused module y which is included in C, 
due to the nature weakness of static analysis and bundle, we can not make a perfect chunk structure
because it is different from the real runtime behavior, like the ES6 Module system. webpack at runtime
actually not follow its static generated chunk structure, its module system is focused on the module level
by simulate the ES6 Module behavior.

The following implementation's do:
1. reduce the initial files size
2. share modules between page chunks and initial files

it did not follow the default webpack chunking algorithm, this will cause lots of duplicated modules in the async chunks, but we do not care, and this plugin operates on one critical assumption: the initial chunks will always be loaded and fully executed before any page chunk that relies on its shared modules is loaded.

```javascriptj
class PageModuleSharingPlugin {
  apply(compiler) {
    compiler.hooks.thisCompilation.tap('PageModuleSharingPlugin', (compilation) => {
      compilation.hooks.optimizeChunks.tap('PageModuleSharingPlugin', (chunks, ...args) => {
        let indexChunk = null;

        // Separate initial chunks and page chunks
        for (const chunk of chunks) {
          if (chunk.isOnlyInitial()) {
            if (chunk.name === 'index') {
              indexChunk = chunk;
            }
          }
        }

        if (!indexChunk) {
          console.error('can not find index chunk');
          process.exit(1);
        }

        const indexAsyncChunks = indexChunk.getAllAsyncChunks();

        // Find modules that exist in both initial and page chunks
        const initialModules = new Set();
        indexChunk.getModules().forEach((module) => {
          initialModules.add(module);
        });

        // Remove shared modules from page chunks
        indexAsyncChunks.forEach((pageChunk) => {
          const modulesToRemove = [];

          pageChunk.getModules().forEach((module) => {
            if (initialModules.has(module)) {
              modulesToRemove.push(module);
              console.log('----module.resource:', module.resource);
            }
          });

          // Remove modules that are already in initial chunks
          modulesToRemove.forEach((module) => {
            compilation.chunkGraph.disconnectChunkAndModule(pageChunk, module);
          });
        });
      });
    });
  }
}

const splitChunks = {
  chunks: 'all',
  minSize: 20000,
  enforceSizeThreshold: 100000,
  minSizeReduction: 0,
  cacheGroups: {
    // Keep initial chunks grouped
    vendors: {
      test: /[\\/]node_modules[\\/]/,
      name: 'vendors',
      chunks: 'initial',
      priority: 50,
      reuseExistingChunk: true,
      enforce: true,
    },
    UI: {
      test: /[\\/]src\/ui[\\/]/,
      name: 'ui',
      chunks: 'initial',
      priority: 50,
      enforce: true,
      reuseExistingChunk: true,
    },
    common: {
      chunks: 'async',
      reuseExistingChunk: true,
      minChunks: 2,
      chunks(chunk) {
        return chunk.name && !chunk.name.startsWith('page-');
      },
    },
    default: false,
    defaultVendors: false,
  },
};

module.exports = {
  splitChunks,
  PageModuleSharingPlugin,
};

```