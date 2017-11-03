#include"client.h"
#define SERV_PORT 8740
char choose, pid;
int initial()
{
	puts("===================================================");
	puts("(a)list all process ids");
	puts("(b)thread's IDs");
	puts("(c)child's PIDs");
	puts("(d)process name");
	puts("(e)state of process(D,R,S,T,t,w,x,z)");
	puts("(f)commnad line of excuting process(cmdline)");
	puts("(g)parent's PID");
	puts("(h)all ancients of PIDs");
	puts("(i)virtual memory size(VmSize)");
	puts("(j)physical memory size(VmRSS)");
	puts("(k)exit");
	printf("which? ");
	scanf("%c", &choose);
	printf("\n");
	if(choose=='k')	exit(-1);
	else if((choose<65||choose>105))return 0;
	else if(choose=='a')return 0;
	else {
		getchar();
		printf("pid? ");
		scanf("%c", &pid);
		printf("\n");
		getchar();
	}
	return 0;
}
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
	unsigned short  sa_family;//addr of family, AF_XXXX
	char			sa_data[14];//14 bytes of protocol addr
} sockaddr;
char buffer[2048];
int	sockfd;
sockaddr_in server;
int main(int argc, char **argv)
{
	while(1) {
		//initial();
		/*	switch (choose){
			case 'a':
			break;
			}	*/

		bzero(&server,sizeof(server));	//init
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP addr
		server.sin_port = htons(SERV_PORT); //host to network short int

		//creat socket
		sockfd = socket(PF_INET, SOCK_STREAM, 0);
		if (sockfd == -1) {
			printf("Fail to create a socket.\n");
		}

		int err = connect(sockfd,(sockaddr*)&server, sizeof(server));
		if(err<0) {
			printf("Fail to connect.\n");
			return 1;
		} else printf("Connected\n");
		char message[]= {"client"};
		send(sockfd, message, sizeof(message), 0);
		recv(sockfd, buffer, sizeof(buffer), 0);
		printf("%s\n",buffer);
		close(sockfd);
		return 0;
	}
}

