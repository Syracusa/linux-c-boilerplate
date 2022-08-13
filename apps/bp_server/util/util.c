#include <string.h>

char* get_buildtime(){
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
