#include <stdio.h>
#include <string.h>

#include "bp.h"

#include "log.h"

#define TESTAPP_VERSION "v0.0.1"

char *get_buildinfo()
{
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;

    /* Init buffer */
    static char buildinfo[40];
    buildinfo[0] = '\0';

    /* Write Library Info */
    strcat(buildinfo, "Build Date : ");
    strcat(buildinfo, _date);

    strcat(buildinfo, "\nBuild Time : ");
    strcat(buildinfo, _time);

    strcat(buildinfo, "\n");

    return buildinfo;
}

int main()
{
    LOGI("TestApp %s\n", TESTAPP_VERSION);
    LOGI("Build info\n%s\n", get_buildinfo());

    LOGI("Library Info\n%s\n", bp_get_libinfo());
    bp_initialize();
    LOGI("%s", bp_get_helloworld());
    bp_finalize();

    LOGF("TestApp %s\n", TESTAPP_VERSION);
    LOGC("TestApp %s\n", TESTAPP_VERSION);
    LOGE("TestApp %s\n", TESTAPP_VERSION);
    LOGW("TestApp %s\n", TESTAPP_VERSION);
    LOGN("TestApp %s\n", TESTAPP_VERSION);
    LOGI("TestApp %s\n", TESTAPP_VERSION);
    LOGD("TestApp %s\n", TESTAPP_VERSION);

    WLOGF("TestApp %s\n", TESTAPP_VERSION);
    WLOGC("TestApp %s\n", TESTAPP_VERSION);
    WLOGE("TestApp %s\n", TESTAPP_VERSION);
    WLOGW("TestApp %s\n", TESTAPP_VERSION);
    WLOGN("TestApp %s\n", TESTAPP_VERSION);
    WLOGI("TestApp %s\n", TESTAPP_VERSION);
    WLOGD("TestApp %s\n", TESTAPP_VERSION);

    TLOGF("TestApp %s\n", TESTAPP_VERSION);
    TLOGC("TestApp %s\n", TESTAPP_VERSION);
    TLOGE("TestApp %s\n", TESTAPP_VERSION);
    TLOGW("TestApp %s\n", TESTAPP_VERSION);
    TLOGN("TestApp %s\n", TESTAPP_VERSION);
    TLOGI("TestApp %s\n", TESTAPP_VERSION);
    TLOGD("TestApp %s\n", TESTAPP_VERSION);
    return 0;
}
