---
title: "TCP Protocol Design Decisions and Tradeoffs"
---

## End to End
TCP is an end to end protocol by design, as IP only provides connectivity function to the upper layers, and hidden the lower layers complexity, its simple abstraction is easily used by the ends when they want the connection.
The key point is here: Certain functions can only be fully and correctly implemented at the "end points" (the applications that are communicating), because only they have the complete knowledge needed.
Such as reliability, any layer under transport layer usually is “incomplete” and not sufficient to provide end-to-end reliable data transfer.

## Tradeoffs
TCP is a full-duplex protocol, so it would be easy to open a TCP connection between the client and server, send the request message in one direction, and send the reply message in the other direction. There are two complications, however. The first is that TCP is a byte-oriented protocol rather than a message-oriented protocol, and request/reply applications always deal with messages. The second complication is
that in those situations where both the request message and the reply message fit in a single network packet, a well-designed request/reply protocol needs only two packets to implement the exchange, whereas
TCP would need at least nine: **three to establish the connection, two for the message exchange, and four to tear down the connection**. 
Of course, if the request or reply messages are large enough to require multiple network packets (e.g., it might take 100 packets to send a 100,000-byte
reply message), then the overhead of setting up and tearing down the connection is inconsequential. In other words, it isn't always the case that a particular protocol cannot support a certain functionality; it's sometimes the case that one design is more efficient than another under particular circumstances.

Second, as just suggested, you might question why TCP chose to provide a reliable byte-stream service rather than a reliable message-stream service; messages would be the natural choice for a database application that wants to exchange records. There are two answers to this question. The first is that a message-oriented protocol must, by definition, establish an upper bound on message sizes. After all, an infinitely long message is a byte stream. For any message size that a protocol
selects, there will be applications that want to send larger messages, rendering the transport protocol useless and forcing the application to implement its own transport-like services. The second reason is that, while message-oriented protocols are definitely more appropriate for applications that want to send records to each other, you can easily insert record boundaries into a byte stream to implement this functionality.

A third decision made in the design of TCP is that it delivers bytes in order to the application. This means that it may hold onto bytes that were received out of order from the network, awaiting some missing bytes to fill a hole. This is enormously helpful for many applications but turns out to be quite unhelpful if the application is capable of processing data out of order. As a simple example, a Web page containing multiple embedded objects doesn't need all the objects to be
delivered in order before starting to display the page. In fact, there is a class of applications that would prefer to handle out-of-order data at the application layer, in return for getting data sooner when packets are dropped or misordered within the network. The desire to support such applications led to the creation of not one but two IETF standard transport protocols. The first of these was SCTP, the Stream Control Transmission Protocol. SCTP provides a partially ordered delivery
service, rather than the strictly ordered service of TCP. (SCTP also makes some other design decisions that differ from TCP, including message orientation and support of multiple IP addresses for a single session.) More recently, the IETF has been standardizing a protocol optimized for Web traffic, known as QUIC. More on QUIC in a moment.

Fourth, TCP chose to implement explicit setup/teardown phases, but this is not required. In the case of connection setup, it would be possible to send all necessary connection parameters along with the first data message. TCP elected to take a more conservative approach that gives the receiver the opportunity to reject the connection before any data arrives. In the case of teardown, we could quietly close a connection that has been inactive for a long period of time, but this would
complicate applications like remote login that want to keep a connection alive for weeks at a time; such applications would be forced to send out-of-band "keep alive" messages to keep the connection state at the other end from disappearing.


