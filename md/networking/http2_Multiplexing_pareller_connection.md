Interleave multiple requests in parallel without blocking on any one

Interleave multiple responses in parallel without blocking on any one

Use a single connection to deliver multiple requests and responses in parallel

Remove unnecessary HTTP/1.x workarounds, such as concatenated files, image sprites, and domain sharding

Deliver lower page load times by eliminating unnecessary latency and improving utilization of available network capacity

multiple connections only adds overhead compare to http2 multiplexing, they all can use the full network capacity

In practice, with 170 http requests, http2 only use 900ms, but http1 with 6 connection needs 3600ms

