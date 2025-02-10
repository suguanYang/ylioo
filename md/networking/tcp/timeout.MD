---
title: "TCP Timeout Calculation and Handling"
---

EstimatedRTT = (1 – α) * EstimatedRTT + α * SampleRTT

DevRTT = (1 – β) * DevRTT + β * | SampleRTT – EstimatedRTT |


TimeoutInterval = EstimatedRTT + 4 * DevRTT

An initial TimeoutInterval value of 1 second is recommended [RFC
6298]. Also, when a timeout occurs, the value of TimeoutInterval is doubled
to avoid a premature timeout occurring for a subsequent segment that will soon be
acknowledged. However, as soon as a segment is received and EstimatedRTT is
updated, the TimeoutInterval is again computed using the formula above.

TCP never computes a SampleRTT for a segment that has been retransmitted; it only measures
SampleRTT for segments that have been transmitted once.

each time TCP retransmits, it sets the next timeout interval to twice the previous value,
rather than deriving it from the last EstimatedRTT and DevRTT