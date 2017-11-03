#include"server.h"
#define SERV_PORT 8740
typedef struct {
	short			sin_family;		//AF_INET(IPv4)
	unsigned short	sin_port;		//port No
	struct	in_addr	sin_addr;
	char			sin_zero[8];
} sockaddr_in;

typedef struct {
	unsigned long s_addr;			//load with inet+pton()
} in_addr;

typedef struct {
	unsigned short   sa_family;//addr of family, AF_XXXX
	char            sa_data[14];//14 bytes of protocol addr
} sockaddr;

char buffer[2048];
char message[]= {"Hi, this is server.\n"};
int sockfd = 0,ClientSockfd = 0, new_sock=0;
int main (int argc, char **argv)
{
	sockaddr_in serv_info,client_info;
	int addrlen = sizeof(client_info);
	bzero(&serv_info,sizeof(serv_info));	//init
	serv_info.sin_family = AF_INET;
	serv_info.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP addr
	serv_info.sin_port = htons(SERV_PORT); //host to network short int
	//creat a socket
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd <0)	printf("Fail to creat a socket.");

	//connect
	if(bind(sockfd,(sockaddr *)&serv_info, sizeof(serv_info))<0)	{
		printf("Address already in use.");
		return 0;
	}
	listen(sockfd, 5);
	//pthread
	while(new_sock = accept(sockfd, (sockaddr*)&client_info, &addrlen))	{
		puts("Connection accepted");
		pthread_t new_thread;
		if( pthread_create(&new_thread, NULL, connection_handler, (void*)&new_sock)<0) {
			perror("Couldn't create thread.\n");
			return 1;
		}
		pthread_join(new_thread, NULL);
	}
	/*
		while(1) {
			ClientSockfd = accept(sockfd, (sockaddr*)&client_info, &addrlen);

			//	send(ClientSockfd, buffer, sizeof(buffer), 0);
			send(ClientSockfd, message, sizeof(message), 0);
			recv(ClientSockfd, buffer, sizeof(message), 0);
			printf("%s\n",buffer);
		}
	*/
	return 0;
}
void *connection_handler(void *sockfd)
{
	//Get socket descriptor
	int sock = *(int*)sockfd;
	//commute
	send(sock, message, sizeof(message), 0);


}
