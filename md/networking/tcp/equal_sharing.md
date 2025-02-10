---
title: "TCP Bandwidth Sharing and RTT Impact"
---

TCP results in an equal sharing of bandwidth among connections with congestion control,
but connections with a smaller RTT are able to grab the available bandwidth at that link more quickly as it becomes free
(that is, open their congestion windows faster) and thus will enjoy higher throughput than those connections with larger RTTs.
When an application uses multiple parallel connections, it gets a larger fraction of the bandwidth in a congested link.