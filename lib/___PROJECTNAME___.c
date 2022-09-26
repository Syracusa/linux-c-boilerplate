#include <string.h>
#include "___PROJECTNAME____log.h"

#define ___PROJECTNAMECAPITAL____VERSION "v0.0.1"

char* ___PROJECTNAME____get_libinfo(){
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;
    int dtlen = 12;

    /* Init buffer */
    static char libinfo[200];
    libinfo[0] = '\0';

    /* Write Library Info */
    strcat(libinfo, "Lib___PROJECTNAME___ " ___PROJECTNAMECAPITAL____VERSION " - INFO\n");
    strcat(libinfo, "Library Build Date : ");
    strcat(libinfo, _date);

    strcat(libinfo, "\nLibrary Build Time : ");
    strcat(libinfo, _time);

    strcat(libinfo, "\n");

    return libinfo;
}

void ___PROJECTNAME____initialize(){
    TLOGI("___PROJECTNAME___LIB INITILAIZED\n");
}

void ___PROJECTNAME____finalize(){
    TLOGI("___PROJECTNAME___LIB FINALIZED\n");
}

char* ___PROJECTNAME____get_helloworld(){
    static char helloworld[14] = "Hello World!\n";
    return helloworld;
}