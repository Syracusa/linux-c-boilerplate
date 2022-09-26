#include <stdio.h>
#include <string.h>

#include "___PROJECTNAME___.h"

#include "log.h"

#define TESTAPP_VERSION "v0.0.1"

char *get_buildinfo()
{
    /* Get build time */
    char _date[] = __DATE__;
    char _time[] = __TIME__;

    /* Init buffer */
    static char buildinfo[200];
    buildinfo[0] = '\0';

    /* Write Library Info */
    strcat(buildinfo, "Build Date : ");
    strcat(buildinfo, _date);

    strcat(buildinfo, "\nBuild Time : ");
    strcat(buildinfo, _time);

    strcat(buildinfo, "\n\0");

    return buildinfo;
}

int main()
{
    LOGI("TestApp %s\n", TESTAPP_VERSION);
    LOGI("Build info\n%s\n", get_buildinfo());

    LOGI("Library Info\n%s\n", ___PROJECTNAME____get_libinfo());
    ___PROJECTNAME____initialize();
    LOGI("%s", ___PROJECTNAME____get_helloworld());
    ___PROJECTNAME____finalize();

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
