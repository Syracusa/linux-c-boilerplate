#include <string.h>
#include <stdio.h>


#define BUILDINFO_BUFSIZE 300
char *get_buildtime()
{
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;

    /* Init ascii_bufer */
    static char libinfo[BUILDINFO_BUFSIZE];
    libinfo[0] = '\0';

    /* Write App Info */
    strcat(libinfo, "Build Date : ");
    strcat(libinfo, _date);

    strcat(libinfo, "\nBuild Time : ");
    strcat(libinfo, _time);

    strcat(libinfo, "\n");

    return libinfo;
}

void hexdump(void *data, int len, FILE* stream)
{
   const int BYTE_INLINE = 16;
   char ascii_buf[BYTE_INLINE + 1];
   unsigned char *ptr = data;

   ascii_buf[BYTE_INLINE] = '\0';

   int linecount = 0;
   int lineoffset;
   for (int i = 0; i < len; i++)
   {
      lineoffset = i % BYTE_INLINE;

      /* Print offset if newline */
      if (lineoffset == 0)
         fprintf(stream, " %04x ", i);
      
      /* Add space at every 4 bytes.. */
      if (lineoffset % 4 == 0)
         fprintf(stream, " ");

      fprintf(stream, " %02x", ptr[i]);
      if ((ptr[i] < 0x20) || (ptr[i] > 0x7e))
         ascii_buf[lineoffset] = ' ';
      else
         ascii_buf[lineoffset] = ptr[i];

      /* Print ASCII if end of line */
      if (lineoffset == BYTE_INLINE - 1){
         fprintf(stream, "  %s\n", ascii_buf);
         linecount++;

         /* Print additional newline at every 5 lines */
         if (linecount != 0 && linecount % 5 == 0)
            fprintf(stream, "\n");
      }
   }

   ascii_buf[lineoffset + 1] = '\0';
   fprintf(stream, " %s\n", ascii_buf);
}