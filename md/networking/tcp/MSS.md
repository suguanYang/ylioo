The maximum amount of data that can be grabbed
and placed in a segment is limited by the maximum segment size (MSS). The MSS
is typically set by first determining the length of the largest link-layer frame that
can be sent by the local sending host (the so-called maximum transmission unit,
MTU), and then setting the MSS to ensure that a TCP segment (when encapsulated
in an IP datagram) plus the TCP/IP header length (typically 40 bytes) will fit into a
single link-layer frame. Both Ethernet and PPP link-layer protocols have an MTU of
1,500 bytes. Thus, a typical value of MSS is 1460 bytes.


