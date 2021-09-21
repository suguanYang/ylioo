#include <stdio.h>

typedef int src_t;
typedef long dest_t;
int main()
{
    int s = 8;
    /* long d = 4; */
    src_t *sp = &s;
    /* dest_t *dp = &d; */
    /* *dp = (dest_t) *sp; */
    printf("%d", *sp);
}
