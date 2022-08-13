#ifndef CFG_H
#define CFG_H

#include "netutil.h"

#define DUMP_CFG 1
#define MAX_CFGNAME_LEN 100
#define DEFAULT_CONFIG_FILENAME "app.cfg"

typedef struct AppConfig{
    char ipstr[IP_STR_LEN];
    int port;

    char target_ipstr[IP_STR_LEN];
    int target_port;
} AppConfig;

void parse_config(AppConfig *cfg,
                  char *cfg_filename);

#endif