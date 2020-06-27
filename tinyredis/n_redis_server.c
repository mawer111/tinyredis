//
// Created by Administrator on 2020/6/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "n_redis_server.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define LISTEN_PORT 6780

void opentiny_redis_server(){
    server_t  *server = malloc(sizeof(server));
    server -> port = LISTEN_PORT;

    struct sockaddr_in address;

    if((server -> socketfd = socket(AF_INET,SOCK_STREAM,0)) == 0){
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(LISTEN_PORT);

    if(bind(server -> socketfd, (struct sockaddr *) &address, sizeof(address)) < 0 ){
        perror("bind port failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server -> socketfd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    event_loop_t *eventLoop = malloc(sizeof(event_loop_t));
    if(eventLoopCreate(eventLoop,1048) == -1){
        perror("create event loop failed");
        exit(EXIT_FAILURE);
    }

    if (ctlLoopEvent(eventLoop,server -> socketfd,EPOLLIN) == -1){
        perror("ctl event failed");
        exit(EXIT_FAILURE);
    }


    while (1){
        int eventNum = loop(eventLoop);

        for(int i = 0; i < eventNum; i++){
            struct epoll_event event = eventLoop -> events[i];
            n_redis_log("loop event %d\n", eventNum);

            if (event.events & EPOLLIN){
                if (event.data.fd == server -> socketfd){
                    struct sockaddr_in client_addr;
                    socklen_t client_socket_len;
                    int conn_fd = accept(server -> socketfd,(struct sockaddr_in *)&client_addr,&client_socket_len);
                    int flags = fcntl(conn_fd,F_GETFL);
                    flags |= O_NONBLOCK;
                    fcntl(conn_fd,F_SETFL,flags);
                    createEpollEvent(eventLoop,conn_fd,-1);
                    ctlLoopEvent(eventLoop,conn_fd,EPOLLIN);
                    char * hello = "hello world";
                    send(conn_fd,hello,strlen(hello),0);
                }else{
                    char buff[128];
                    int read_size = read(event.data.fd,buff,128);
                    n_redis_log("read from peer:%s",buff);
                    int send_size = send(event.data.fd,buff,read_size,0);
                    if (send_size < read_size){

                    }

                    //TODO if send_size is less than read_size ,we should listen out event and send buffer on next send event;
                }
            }
        }

    }




}




