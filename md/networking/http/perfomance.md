---
title: "HTTP Performance Optimization Techniques"
---

## HTTP perfomance
The performance of HTTP is only about the protocol itself.
## Why?
## Optimization?
The 2 fundament optimization are
- 1. Eliminate and reduce unnecessaty network latency.
  -a. Reduce DNS lookups
  -b. Use CDN
  -c. Keepalive connection
  -d. Pipelining
  -e. Using multiple TCP connections
  -f. Domain Sharding
- 2. Minimize the amount of bytes that need transferrd
  -a. Make fewer HTTP requests
  -b. Add cache header(expires, ETags)
  -c. Gzip assets
  -d. Concatenation and Spriting
  -e. Calculating image memory requirements
  -f. Resource Inlining

## HTTP/2
The primary goals of HTTP/2 are reduce the latency by enabling full request and response
multiplexing, minimize protocl overhead via effecient compression of HTTP header fields,
and support for request priorotizaion and sever push.
