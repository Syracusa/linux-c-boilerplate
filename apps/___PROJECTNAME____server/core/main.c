#include <stdio.h>
#include "app.h"
#include "server.h"

int main(int argc, char *argv[])
{
    char *cfgfile;

    if (argc == 1)
    {
        cfgfile = DEFAULT_CONFIG_FILENAME;
    }
    else
    {
        cfgfile = argv[1];
    }
    
    LOGI("USE CONFIGFILE : %s\n", cfgfile);
    init_app(cfgfile);
    server_start();
    return 0;
}