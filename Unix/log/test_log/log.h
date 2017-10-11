#pragma once
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include<syslog.h>

void set_loglevel(int level);
void sys_log(int log_level, const char *file_name, int line_num, const char *format, ...);

