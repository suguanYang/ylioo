---
title: "TCP Zero Window Probe Mechanism"
---

how does the sending side know that the advertised window is no longer 0? As mentioned above, TCP always sends a segment in response to a received data segment, and this response contains the latest values for the Acknowledge and AdvertisedWindow fields, even if these values have not changed since the last time they were sent. The problem is this. Once the receive side has advertised a window size of 0, the sender is not permitted to send any more data, which means it has no way to discover
that the advertised window is no longer 0 at some time in the future. TCP on the receive side does not spontaneously send nondata segments; it only sends them in response to an arriving data segment.

TCP deals with this situation as follows. Whenever the other side advertises a window size of 0, the sending side persists in sending a segment with 1 byte of data every so often. It knows that this data will probably not be accepted, but it tries anyway, because each of these 1-byte segments triggers a response that contains the current advertised window. Eventually, one of these 1-byte probes triggers a response that reports a nonzero advertised window.

Note that these 1-byte messages are called Zero Window Probes and in practice they are sent every 5 to 60 seconds. As for what single byte of data to send in the probe: it's the next byte of actual data just outside the window. (It has to be real data in case it's accepted by the receiver.)
