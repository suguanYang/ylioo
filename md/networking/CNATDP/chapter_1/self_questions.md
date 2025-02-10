---
title: "TCP and Network Protocol Questions"
---

1. Can TCP payload size less than 1 byte since the seq number will accumlated by byte size?
The minimum payload size for TCP is 0 bytes (which is possible in certain cases, like pure ACK packets). The sequence number does indeed accumulate based on the number of bytes sent, but it's not possible to send a fraction of a byte.

2. Are the 2 init seq number(client and server) both determined by the client
 the initial sequence numbers are not both determined by the client. In a TCP connection:
The client chooses its own initial sequence number (ISN) for the SYN packet.
The server chooses its own independent ISN for the SYN-ACK packet.
Both sides generate their ISNs independently, typically using a clock-based algorithm to ensure uniqueness and security.

3. If tcp has no payload, will the seq number will be accumalted?
the sequence number can be incremented even when there's no payload, but only in specific cases:
SYN and FIN flags consume one sequence number each.
Regular packets with no payload (like pure ACKs) do not increment the sequence number.

4. Will the timeoutIterval will be always doubled if every packets get timeout but arrived quickly just after the retransimmstion?
each time TCP retransmits, it sets the next timeout interval to twice the previous value,
rather than deriving it from the last EstimatedRTT and DevRTT