#include <string.h>
#include "bp_log.h"

#define _BP_VERSION "v0.0.1"

char* bp_get_libinfo(){
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;
    int dtlen = 12;

    /* Init buffer */
    static char libinfo[200];
    libinfo[0] = '\0';

    /* Write Library Info */
    strcat(libinfo, "LibLinuxCBoilerplate " _BP_VERSION " - INFO\n");
    strcat(libinfo, "Library Build Date : ");
    strcat(libinfo, _date);

    strcat(libinfo, "\nLibrary Build Time : ");
    strcat(libinfo, _time);

    strcat(libinfo, "\n");

    return libinfo;
}

void bp_initialize(){
    TLOGI("BPLIB INITILAIZED\n");
}

void bp_finalize(){
    TLOGI("BPLIB FINALIZED\n");
}

char* bp_get_helloworld(){
    static char helloworld[14] = "Hello World!\n";
    return helloworld;
}