---
title: "TCP Connection Establishment Process"
---

The following scenario occurs when a TCP connection is established:
  - 1. The server must be prepared to accept an incoming connection. This is normally done by calling `socket`, `bind` and `listen` and is called a `passive open`.
  - 2. The client issues an active open by calling connect. This causes the client TCP to send a 'synchronize'(SYN) segment, which tells the server it's initial sequence number for the data that the client will send on the connection. Normally, there is no data sent with SYN, it just contains IP header, TCP header and possible TCP options
  - 3. The server must acknowledge(ACK) the client's SYN and must also send it's own SYN which contains, the server sends it's own SYN and the ACK of client's SYN in one segment.