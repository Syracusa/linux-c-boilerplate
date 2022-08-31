#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>

#include "piapi.h"

static void hex_dump(void *addr, int len, FILE* stream)
{
   fprintf(stream, "length of hexdump = %d\n", len);
   int            i;
   unsigned char  buff[17];
   unsigned char *pc = (unsigned char *)addr;

   // Process every byte in the data.
   for (i = 0; i < len; i++)
   {
      // Multiple of 16 means new line (with line offset).
      if ((i % 16) == 0)
      {
         // Just don't print ASCII for the zeroth line.
         if (i != 0)
            fprintf(stream, " %s\n", buff);

         // Output the offset.
         fprintf(stream, " %04x ", i);
      }

      // Now the hex code for the specific character.
      fprintf(stream, " %02x", pc[i]);

      // And store a printable ASCII character for later.
      if ((pc[i] < 0x20) || (pc[i] > 0x7e))
         buff[i % 16] = '.';
      else
         buff[i % 16] = pc[i];
      buff[(i % 16) + 1] = '\0';
   }

   // Pad out last line if not exactly 16 characters.
   while ((i % 16) != 0)
   {
      fprintf(stream, " ");
      i++;
   }

   // And print the final ASCII bit.
   fprintf(stream, " %s\n", buff);
}
#define WBUFSZ  4000
#define WNUM    100000
int main(){
    init_mmapbuf();
    
    char buf[WBUFSZ];
    memset(buf, 0xfa, WBUFSZ);
    
    for (int i = 0; i < WNUM; i++){
        fprintf(stderr, "Try write Seq:%d\n", i);
        write_mmapbuf(i * WBUFSZ, buf, WBUFSZ);
    }

    int failcnt = 0;
    for (int i = 0; i < WNUM; i++){
        fprintf(stderr, "Try check Seq:%d\n", i);
        int cmpres = memcmp(((uint8_t*)get_mmap_ptr()) + i * WBUFSZ, buf, WBUFSZ);
        if (cmpres != 0){
            hex_dump(((uint8_t*)get_mmap_ptr()) + i * WBUFSZ, WBUFSZ, stdout);
            failcnt++;
            fprintf(stderr, "FAIL(%d)\n", cmpres);
        }
    }

    fprintf(stderr, "FAIL COUNT : %d\n", failcnt);

    free_mmapbuf();
    return 0;
}