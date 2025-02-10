Why window size of Selective Repate needs most half of the max sequence number?

The main problem of the why windows size matter is the receiver can not tell the diffence between a retransmition and a new packet,
if the receiver's expected sequence number [n, n + N) overlapped between the acked sequence number (n - N, n - 1].
Proof:
    the 2 area size is 2N, if the max seq numebr is M, we need to provides 2N <= M to make sure the 2 area not overlap,
    thus N <= M / 2

Since the sender will not move forward its window unless all continous acked seq number have received, we can safly ensure that only
receiver's expected window's seq number or the previous window's seq number will be sent. the receiver can easily distinct which is new
packet or retransmition


