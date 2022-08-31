
#include <stdio.h>

#include "piapi.h"
#include "netutil.h"

void be32_to_ipstr(in_addr_t addr, char *buf)
{
    uint8_t *ip_int = (uint8_t *)&addr;
    sprintf(buf, "%d.%d.%d.%d",
            ip_int[0], ip_int[1], ip_int[2], ip_int[3]);
}

#define _be32_to_ipstr_nobuf_bufsize 4
char *be32_to_ipstr_nobuf(in_addr_t addr)
{
    static int bufidx = 0;
    static char ipstr[_be32_to_ipstr_nobuf_bufsize][IP_STR_LEN];
    if (bufidx > _be32_to_ipstr_nobuf_bufsize - 1)
        bufidx = 0;
    be32_to_ipstr(addr, ipstr[bufidx]);

    return ipstr[bufidx++];
}
