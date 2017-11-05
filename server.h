#ifndef SERVER_H
#define SERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>
#include "protocol.h"
#define SERV_PORT 8740
void *connection_handler(void *);
int client_choice();
typedef struct {
	short           sin_family;     //AF_INET(IPv4)
	unsigned short  sin_port;       //port No
	struct  in_addr sin_addr;
	char            sin_zero[8];
} sockaddr_in;

typedef struct {
	unsigned long s_addr;           //load with inet+pton()
} in_addr;

typedef struct {
	unsigned short   sa_family;//addr of family, AF_XXXX
	char            sa_data[14];//14 bytes of protocol addr
} sockaddr;

#endif
