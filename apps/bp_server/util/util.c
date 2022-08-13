#include <string.h>
#include <stdio.h>

char *get_buildtime()
{
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;

    /* Init buffer */
    int buf_margin = 100;
    int buflen = strlen(_date) + strlen(_time) + buf_margin;
    char libinfo[buflen];
    libinfo[0] = '\0';

    /* Write App Info */
    strcat(libinfo, "Build Date : ");
    strcat(libinfo, _date);

    strcat(libinfo, "\nBuild Time : ");
    strcat(libinfo, _time);

    strcat(libinfo, "\n");

    return libinfo;
}

void hex_dump(void *addr, int len, FILE* stream)
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