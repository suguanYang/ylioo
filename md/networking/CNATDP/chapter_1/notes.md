---
title: "Network Delay Types and Packet Loss"
---

# Chapter 1   
## Delay in Packet-Switched Networks   
The most important delays are the ***node processing delay, queuing delay, transmission delay,***  and **propagation delay.**   
    
- Processing delay   
    The time required to examine the packet's header and determine where to direct the packet is part of the **processing delay, **it also includes other factors, such as the time needed to check for bit-level errors in the packet that occurred   
    in the transmission.   
- Queuing Delay   
    At the queue, the packet needs to wait to be transmitted onto the link. The length of the delay depends on the number   
    of earlier-arriving packets that are queued and waiting for transmission onto the link.   
- Transmission Delay   
    The amount of time required to push all of the packet's bits into the link. Denote the length if the packet by L bits, and the transmission rate of the link by R bits/sec, the **Transmission Delay**  is L/R.   
- Propagation Delay   
    The time required to propagate from the start of link to destination router is the **Propagation Delay.** The speed depends on the physical medium of the link. The delay can be formulate by d/s, where the d is the distance between 2 nodes and the s is the speed of the signal propagate in the link medium   
   
## Packet Loss
When a packet arrived at the router, the router's buffer is full, the packet will be dropped.
