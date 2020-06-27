//
// Created by Administrator on 2020/6/27.
//

#ifndef TINYREDIS_N_REDIS_SERVER_H
#define TINYREDIS_N_REDIS_SERVER_H
#include "n_redis_event_loop.h"
#include "n_redis_log.h"
typedef struct server {

    int socketfd;
    int port;

} server_t ;



void opentiny_redis_server();

#endif //TINYREDIS_N_REDIS_SERVER_H

