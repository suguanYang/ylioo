maintain a counter, ex a range of 10 as the transaction ID
whenever a transcation occurs, the ID is given by mod((previousID + 1), 10)

way 1. we can set a max_transcation_queue as 10 / 2,
the T ID number will compared within the queue size, eg, if the IDs are
[9, 0, 1, 2, 3], we will know the 1 is later than 9

way2. mark the head and tail ID, at the start, head would be 0,
the tail will be the next T ID, after the T ID cleanup, we update the
head be the (last cleand ID + 1), when compare 2 T ID a and b,
if (a < head)
    a = a + (max - head) + 1
if (b < head)
    b = b + (max - head) + 1

return a - b
