# Problems   

## P13. a) Suppose n packets arrive simultaneously to a link at which no packets are currently being transmitted or queued. Each packet is of length L and the link has transmission rate R. What is the average queuing delay for then packets?   

For the first arrived packet the queuing delay is 0, for second packet the queuing delay is    
$$
\frac{L}{R}
$$
For the total delay is   

$$
S = 0 + \frac{L}{R} + 2\frac{L}{R} + 3\frac{L}{R} + ... + (n-1)\frac{L}{R} 
$$
$$
S = n* \frac{(n-1)}{2}* \frac{L}{R}
$$
The average queuing delay is   
$$
n* \frac{(n-1)}{2}* \frac{L}{R} * \frac{1}{n} = \frac{(n-1)L}{2R}
$$

## b). Now suppose that N such packets arrive to the link every LN/R seconds. What is the average queuing delay of a packet?   
The arrive rate of packet is   
$$
\frac{R}{LN}
$$
per seconds, the total size of N packets will be   
$$
N * L *\frac{R}{LN} = R
$$
which is equal to the transmit rate of the link, thus when the N packets arrive there would be no queue, the average queuing    
delay is equal to the average queuing delay of single batch, which is equal to   
$$
 \frac{(n-1)L}{2R}
$$
- be notice that the sum of all packets' queuing delay is not equal to the process time but instead the last queuing delay is*   
     
   
