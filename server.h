#ifndef SERVER_H
#define SERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>
#include "protocol.h"
void *connection_handler(void *);
#endif
