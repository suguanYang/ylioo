As a case study, consider the delay in receiving a response for a search query.
Typically, the server requires three TCP windows during slow start to deliver the response
[Pathak 2010]. Thus the time from when an end system initiates a TCP connection until the
time when it receives the last packet of the response is roughly 4 # RTT (one RTT to set up
the TCP connection plus three RTTs for the three windows of data) plus the processing time
in the data center. These RTT delays can lead to a noticeable delay in returning search
results for a significant fraction of queries. Moreover, there can be significant packet loss
in access networks, leading to TCP retransmissions and even larger delays.
One way to mitigate this problem and improve user-perceived performance is to
(1) deploy front-end servers closer to the users, and (2) utilize TCP splitting by break-
ing the TCP connection at the front-end server. With TCP splitting, the client establishes
a TCP connection to the nearby front-end, and the front-end maintains a persistent TCP
connection to the data center with a very large TCP congestion window [Tariq 2008,
Pathak 2010, Chen 2011]. With this approach, the response time roughly becomes
4 # RTTFE + RTTBE + processing time, where RTTFE is the round-trip time between client and
front-end server, and RTTBE is the round-trip time between the front-end server and the data
center (back-end server). If the front-end server is close to client, then this response time
approximately becomes RTT plus processing time, since RTTFE is negligibly small and RTTBE
is approximately RTT. In summary, TCP splitting can reduce the networking delay roughly
from 4 # RTT to RTT, significantly improving user-perceived performance, particularly for
users who are far from the nearest data center. TCP splitting also helps reduce TCP
retransmission delays caused by losses in access networks. Google and Akamai have
made extensive use of their CDN servers in access networks (recall our discussion in
Section 2.6) to perform TCP splitting for the cloud services they support [Chen 2011].