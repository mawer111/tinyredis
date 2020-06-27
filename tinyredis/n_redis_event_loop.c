//
// Created by Administrator on 2020/6/27.
//
#include <stdlib.h>
#include "n_redis_event_loop.h"

int eventLoopCreate(event_loop_t *eventLoop , size_t size){
    int epfd = epoll_create(1024);
    if (epfd == -1){
        return -1;
    }
    eventLoop -> e_fd = epfd;
    struct epoll_event *event = malloc(sizeof(struct epoll_event) * size);
    eventLoop -> events = event;
    eventLoop -> size = size;
}

int ctlLoopEvent(event_loop_t *eventLoop,int fd,int events){

    struct epoll_event ee = {0};
    if (eventLoop -> e_fd == 0){
        return -1;
    }
    struct epoll_event event = eventLoop -> events[fd];
    int op = event.events == EVENT_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;
    ee.data.fd = fd;

    //merge old event
    events |= event.events;
    ee.events = events;
    if (epoll_ctl(eventLoop -> e_fd,op,fd,&ee) == -1) return -1;
    return 0;
}


struct epoll_event * createEpollEvent(event_loop_t *eventLoop,int fd,int mask){
    if (fd >= eventLoop->size){
        return EV_ERR;
    }

    struct epoll_event *event = &(eventLoop -> events[fd]);
    event -> data.fd = fd;
    return event;
}


int delLoopEvent(event_loop_t *eventLoop,int fd){
    return 0;
}

int loop(event_loop_t *eventLoop){
    return epoll_wait(eventLoop -> e_fd,eventLoop -> events,eventLoop -> size, -1);
}