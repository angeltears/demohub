#include"log.h"

#define LOG_BUFFER_SIZE 256

static int loglevel = LOG_INFO;

static char * loglevels[] = 
{
    "LOG_EMERG!", "LOG_ALERT", "LOG_CRIT", "LOG_ERR", "LOG_WARNING", "LOG_NOTICE",
    "LOG_INFO", "LOG_DEBUG"
};

void set_loglevel(int level)
{
    loglevel = level;
}

void sys_log(int log_level, const char *file_name, int line_num, const char *format, ...)
{
    if (log_level > loglevel)
        return;
    time_t te;
    time(&te);   //取本地时间
    struct tm *cur_time = localtime(&te);

    char buffer[LOG_BUFFER_SIZE];
    memset(buffer, 0, LOG_BUFFER_SIZE);   //将BUFFER全部初始化为０
    strftime(buffer, LOG_BUFFER_SIZE - 1, " [%x %X]", cur_time);
    printf("%s", buffer);
    printf("%s:%04d ", file_name, line_num);  //最多万行日志
    printf("< %s > ", loglevels[log_level]);

    va_list arg_list;
    va_start(arg_list, format);
    memset(buffer, 0, LOG_BUFFER_SIZE);
    vsnprintf(buffer, LOG_BUFFER_SIZE - 1, format, arg_list);
    printf("%s\n", buffer);
    va_end(arg_list);
    fflush(stdout);
}
