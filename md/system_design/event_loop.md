## Why we need this?


Event-loop is an algrithm to retrive event handlers from Event queue.

## When to use?
When program are io-bound process, and there has a non-blocking version of IO operates(eg, epoll),
> Node.js uses the Worker Pool to handle "expensive" tasks. This includes I/O for which an operating system does not provide a non-blocking version, as well as particularly CPU-intensive tasks.

## Combined with worker
How many workers to create?
1. for cpu-bound task, it's 1:1
more worker not helps since the CPU is the bottleneck.
2. for io-bound task, it's 1:many
more worker can handle leverage more cpus, since the cpus are waiting for io for most of the time.


## References

[The reactor pattern](https://subscription.packtpub.com/book/web_development/9781783287314/1/ch01lvl1sec09/the-reactor-pattern)
[web app apis, event-loops](https://html.spec.whatwg.org/multipage/webappapis.html#event-loops)
[wiki event-loop](https://en.wikipedia.org/wiki/Event_loop)
