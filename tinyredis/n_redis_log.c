//
// Created by Administrator on 2020/6/27.
//

#include "n_redis_log.h"
#include <time.h>
#include <stdarg.h>


void fmtTime() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[18];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    size_t size = strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", timeinfo);
    printf("%s", buffer, size);
}


void n_redis_log(char *log, ...) {
    va_list vaList;
    va_start(vaList,log);
    fmtTime();
    vprintf(log, vaList);
    va_end(vaList);
}

