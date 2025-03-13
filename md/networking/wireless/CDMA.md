---
title: proof of CDMA
---

let 2 encode codes are codeA and codeB, the length of the code is N = 4

codeA = [1, -1, 1, -1]
codeB = [1, 1, -1, -1]

They are orthogonal to each other, which means:

codeA *(dot product) codeB = 0

[1, -1, 1, -1] * [1, 1, -1, -1] = 1*1 + (-1)*1 + 1*(-1) + (-1)*(-1) = 0

let 2 data bits x and y that send by 2 users at 2 different time slots

let xA and xB are encoded data of x with codeA and codeB respectively

xA = x * codeA
xB = x * codeB


At receiver side:

The receiver will receive a aggregated signal that is the sum of the 2 encoded data

s = xA + yB
s= x * codeA + y * codeB

if the receiver use codeA to decode the singal by taking dot product of s with codeA

s * codeA = (x * codeA + y * codeB) * codeA

= x * (codeA * codeA) + y * (codeB * codeA)

= x * N + y * 0

= 4x


thus the receiver can decode x from the signal s by taking dot product of s with codeA and divide the result by N

x = s * codeA / N










