#include <sys/stat.h>

#include "iniparser.h"
#include "cfg.h"
#include "log.h"
#include "sample.h"

static void create_sample_cfgfile(char *filename)
{
    FILE *f;

    if ((f = fopen(filename, "w")) == NULL)
    {
        LOGF("iniparser: cannot create %s\n", filename);
        exit(2);
    }
    else
    {
        fprintf(f, "%s", CONFIG_SAMPLE);
        chmod(filename, 0666);
        fclose(f);
    }
}

static void parse_int_cfg(dictionary *dict,
                          int *val,
                          char *name,
                          int is_optional)
{
    char cfgname[MAX_CFGNAME_LEN];
    sprintf(cfgname, "APP_CONFIG:%s", name);
    *val = iniparser_getint(dict, cfgname, -1);
    if (*val == -1)
    {
        if (!is_optional){
            LOGF("Parse fail(%s)\n", cfgname);
            exit(2);
        } else {
            LOGW("Parse fail(%s)\n", cfgname);
        }
    }
}

static void parse_string_cfg(dictionary *dict,
                             void *buf,
                             char *name,
                             int is_optional)
{
    char cfgname[MAX_CFGNAME_LEN];
    sprintf(cfgname, "APP_CONFIG:%s", name);
    const char *tmpptr = iniparser_getstring(dict, cfgname, NULL);

    if (tmpptr == NULL)
    {
        if (!is_optional){
            LOGF("Parse fail(%s)\n", cfgname);
            exit(2);
        } else {
            LOGW("Parse fail(%s)\n", cfgname);
        }
    }
    else
    {
        memcpy(buf, tmpptr, strlen(tmpptr));
    }
}

void parse_config(AppConfig *cfg,
                  char *cfg_filename)
{
    dictionary *dict = iniparser_load(cfg_filename);
    if (dict == NULL)
    {
        LOGI("File %s doesn't exist... create one\n", cfg_filename);
        create_sample_cfgfile(cfg_filename);
        dict = iniparser_load(cfg_filename);
        if (dict == NULL)
        {
            LOGF("Can't create File %s\n", cfg_filename);
            exit(2);
        }
    }

    if (DUMP_CFG)
    {
        iniparser_dump(dict, stderr);
    }

    parse_string_cfg(dict, cfg->ipstr, "IP", 0);
    parse_int_cfg(dict, &cfg->port, "PORT", 0);
    
    parse_string_cfg(dict, cfg->target_ipstr, "TARGET_IP", 0);
    parse_int_cfg(dict, &cfg->target_port, "TARGET_PORT", 0);

    iniparser_freedict(dict);
}