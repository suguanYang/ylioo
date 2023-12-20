#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("/home/binqi/github.com/ylioo/examples/os/file1", O_RDONLY, 0);

    int fd2 = open("/home/binqi/github.com/ylioo/examples/os/file12", O_RDONLY, 0);

    printf("fd2: %d\n", fd2);

    return 0;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;
    while (rp->rio_cnt <= 0)
    {
        /* Refill if buf is empty */
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf,
                           sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR) /* Interrupted by sig handler return */
                return -1;
        }
        else if (rp->rio_cnt == 0)
            /* EOF */
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf; /* Reset buffer ptr */
    }
    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;
    for (n = 1; n < maxlen; n++)
    {
        if ((rc = rio_read(rp, &c, 1)) == 1)
        {
            *bufp++ = c;
            if (c == ’\n’)
            {
                n++;
                break;
            }
        }
        else if (rc == 0)
        {
            if (n == 1)
                return 0; /* EOF, no data read */
            else
                break;
            /* EOF, some data was read */
        }
        else
            return -1;
        /* Error */
    }
    *bufp = 0; // The line *bufp = 0; is adding a null terminator to the end of the string that has been read.
    return n - 1;
}