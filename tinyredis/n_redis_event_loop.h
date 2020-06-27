//
// Created by Administrator on 2020/6/27.
//

#ifndef TINYREDIS_N_REDIS_EVENT_LOOP_H
#define TINYREDIS_N_REDIS_EVENT_LOOP_H
#include <sys/epoll.h>
#define EVENT_NONE 0
#define EV_ERR -1;


typedef struct n_event {
    int mask;



} t_event;

typedef struct event_loop {
    int e_fd;
    size_t size;
    struct epoll_event *events;

} event_loop_t;

int eventLoopCreate(event_loop_t *eventLoop,size_t size);
struct epoll_event * createEpollEvent(event_loop_t *eventLoop,int fd,int mask);
int ctlLoopEvent(event_loop_t *eventLoop,int fd,int events);
int loop(event_loop_t *eventLoop);

#endif //TINYREDIS_N_REDIS_EVENT_LOOP_H
