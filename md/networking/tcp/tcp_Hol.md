---
title: "TCP Head-of-Line Blocking in HTTP/2"
---

For HTTP/1.1, the resource-loading process is quite simple, because each file is given its own TCP connection and downloaded in full. For example, if we have files A, B, and C, we would have three TCP connections. The first would see a byte stream of AAAA, the second BBBB, the third CCCC (with each letter repetition being a TCP packet). This works but is also very inefficient because each new connection has some overhead.

In practice, browsers impose limits on how many concurrent connections may be used (and thus how many files may be downloaded in parallel) — typically, between 6 and 30 per page load. Connections are then reused to download a new file once the previous has fully transferred. These limits eventually started to hinder web performance on modern pages, which often load many more than 30 resources.

Improving this situation was one of the main goals for HTTP/2. The protocol does this by no longer opening a new TCP connection for each file, but instead downloading the different resources over a single TCP connection. This is achieved by "multiplexing" the different byte streams. That's a fancy way of saying that we mix data of the different files when transporting it. For our three example files, we would get a single TCP connection, and the incoming data might look like AABBCCAABBCC (although many other ordering schemes are possible). This seems simple enough and indeed works quite well, making HTTP/2 typically just as fast or a bit faster than HTTP/1.1, but with much less overhead.

take a closer look at the difference:
![](./assets/multiplexing-basic.png)

HTTP/1 versus HTTP/2 and HTTP/3 multiplexing
HTTP/1.1 does not allow multiplexing, unlike both HTTP/2 and HTTP/3. (Large preview)
However, there is a problem on the TCP side. You see, because TCP is a much older protocol and not made for just loading web pages, it doesn't know about A, B, or C. Internally, TCP thinks it's transporting just a single file, X, and it doesn't care that what it views as XXXXXXXXXXXX is actually AABBCCAABBCC at the HTTP level. In most situations, this doesn't matter (and it actually makes TCP quite flexible!), but that changes when there is, for example, packet loss on the network.

Suppose the third TCP packet is lost (the one containing the first data for file B), but all of the other data are delivered. TCP deals with this loss by retransmitting a new copy of the lost data in a new packet. This retransmission can, however, take a while to arrive (at least one RTT). You might think that's not a big problem, as we see there is no loss for resources A and C. As such, we can start processing them while waiting for the missing data for B, right?

Sadly, that's not the case, because the retransmission logic happens at the TCP layer, and TCP does not know about A, B, and C! TCP instead thinks that a part of the single X file has been lost, and thus it feels it has to keep the rest of X's data from being processed until the hole is filled. Put differently, while at the HTTP/2 level, we know that we could already process A and C, TCP does not know this, causing things to be slower than they potentially could be. This inefficiency is an example of the "head-of-line (HoL) blocking" problem.