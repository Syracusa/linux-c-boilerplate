#ifndef CFG_H
#define CFG_H

#define DUMP_CFG 1
#define MAX_CFGNAME_LEN 100
#define DEFAULT_CONFIG_FILENAME "app.cfg"


#define INETADDR_STR_LEN 20
typedef struct AppConfig{
    char ipstr[INETADDR_STR_LEN];
    int port;

    char target_ipstr[INETADDR_STR_LEN];
    int target_port;
} AppConfig;

void parse_config(AppConfig *cfg,
                  char *cfg_filename);

#endif