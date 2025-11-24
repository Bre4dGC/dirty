#include <stdio.h>

#include "config.h"
#include "logs.h"

static FILE *conf_f = NULL;

int conf_init()
{
    if (conf_f)
    {
        return log_report(REPORT_SUCCESS, "Configuration already initialized");
    }
    conf_f = fopen("config/settings.conf", "a");
    if (!conf_f)
    {
        fprintf(stderr, "Failed to open configuration file.\n");
        return log_report(REPORT_EXECUTE_ERROR, "Configuration initialize");
    }
    return log_report(REPORT_SUCCESS, "Configuration initialized");
}

int conf_reset()
{
    // TODO: Implement configuration reset logic
    return log_report(REPORT_SUCCESS, "Configuration reset");
}

int conf_save()
{
    // TODO: Implement configuration saving logic
    return log_report(REPORT_SUCCESS, "Configuration saved");
}

int conf_load()
{
    // TODO: Implement configuration loading logic
    return log_report(REPORT_SUCCESS, "Configuration loaded");
}

int conf_cleanup()
{
    if (conf_f)
    {
        fclose(conf_f);
        conf_f = NULL;
    }
    return log_report(REPORT_SUCCESS, "Configuration cleaned up");
}
