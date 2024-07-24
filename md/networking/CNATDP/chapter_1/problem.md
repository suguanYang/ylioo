# Problems   

## R1. What is the difference between a host and an end system? List several different types of end systems. Is a Web server an end system?

There's no difference between host and end systems they usually can be used interchangeblely, but the end system often has a border meaning.
Some end systems like web server, smart phone, personal computer, and some embedded device connected to network/

## R2. The word protocol is often used for describe diplomatic relations. How does Wikipedia descrube diplomatic protocol?
> pass

## R3. Why are standard important for protocols?
The protocol needs to define standards, it describe how different parts operate with each other by following the standards, we can build a very complex system piece by piece and integrate them by the common protocol standards.without the standards there is no interoperates, also can not exchange informations between different parts, and the change of standards also will impact the integrity of system.

## R4. List four access technologies. Classify each one as home access, enterprise access, or wide-area wireless access.
Home access:
    DSL(digital subscriber line: 数字用户线路)
    Cable Internet access(有线上网)
    FTTH(fiber to the home: 光纤入户)
Enterprise access(also in Home access):
    Ethernet LAN
    IEEE 802.11 WiFi
Wide-area wireless:
    4G
    5G
    satellite internet

## R5. Is HFC transmission rate dedicated or shared among users? Are collisions possible in a downstream HFC channel? Why or why not?
It's shared among the users on the link, There is no collisions for downstream since every packets is sent by the same head end to every users.

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
     
   
