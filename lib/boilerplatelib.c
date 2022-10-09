#include <string.h>
#include "boilerplatelib_log.h"

#ifdef LOG_HDR
    #undef LOG_HDR
    #define LOG_HDR "[LIBLOG]"
#endif

char* boilerplate_get_libinfo(){
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;

    /* Init buffer */
    static char libinfo[200];
    libinfo[0] = '\0';

    /* Write Library Info */
    strcat(libinfo, "Library Build Date : ");
    strcat(libinfo, _date);

    strcat(libinfo, "\nLibrary Build Time : ");
    strcat(libinfo, _time);

    strcat(libinfo, "\n");

    return libinfo;
}

void boilerplate_initialize(){
    TLOGI("BOILERPLATE_LIB INITILAIZED\n");
}

void boilerplate_finalize(){
    TLOGI("BOILERPLATE_LIB FINALIZED\n");
}

char* boilerplate_get_helloworld(){
    static char helloworld[14] = "Hello World!\n";
    return helloworld;
}

#ifdef LOG_HDR
    #undef LOG_HDR
    #define LOG_HDR DEFAULT_LOG_HDR
#endif
