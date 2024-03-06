For inherently unpredictable cases, program performance can be greatly enhanced if 
the compiler is able to generate code using conditional data transfers rather than
conditional control transfers

/* Rearrange two vectors so that for each i, b[i] >= a[i] */
void minmax1(long a[], long b[], long n) {
long i;
for (i = 0; i < n; i++) {
if (a[i] > b[i]) {
long t = a[i];
a[i] = b[i];
b[i] = t;
}
}
}
for this function show a CPE of around 13.5 for random data
and 2.5–3.5 for predictable data, an indication of a misprediction penalty of around
20 cycles.


void minmax2(long a[], long b[], long n) {
long i;
for (i = 0; i < n; i++) {
long min = a[i] < b[i] ? a[i] : b[i];
long max = a[i] < b[i] ? b[i] : a[i];
a[i] = min;
b[i] = max;
}
}
 for this function show a CPE of around 4.0 regardless of
whether the data are arbitrary or predictable


 Mispredicting a jump, on the other hand, requires that the processor
discard much of the work it has already done on future instructions and then begin
filling the pipeline with instructions starting at the correct location. As we will see,
such a misprediction can incur a serious penalty, say, 15–30 clock cycles of wasted
effort, causing a serious degradation of program performance.

the code compiled using conditional moves requires
fixed clock cycles regardless of the data being tested. The flow of control
does not depend on data, and this makes it easier for the processor to keep its
pipeline full.



The critical path:
The instructions that must need to be executed in sequence(before the next loop), all of these instructions depend on the previous loop iteration.

while (i < n) {
    acc = acc + 1
    i++
}

the i and acc are both dependent on the previous loop iteration