#include"client.h"
char choose[100],pid[100] ;
char buffer[2048], message[100];
int	sockfd;
sockaddr_in server;
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
	memset(choose,0,100);
	memset(pid,0,100);
	printf("which?");
//	setbuf(stdin, NULL);
	gets(choose);
	//scanf("%s", choose);
	if((choose[0]>'a'&&choose[0]<'k')) {
		strcpy(pid,"");
		//setbuf(stdin, NULL);
		printf("pid?");
		gets(pid);
		//scanf("%s", pid);
	}
	return 0;
}
int main(int argc, char **argv)
{
	bzero(&server,sizeof(server));	//init
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP addr
	server.sin_port = htons(SERV_PORT); //host to network short int

	//creat socket
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		printf("Fail to create a socket.\n");
	int err = connect(sockfd,(sockaddr*)&server, sizeof(server));
	if(err<0) {
		printf("Fail to connect.\n");
		return 1;
	}
	while(1) {
		initial();
		memset(message,0,100);
//		printf("choose=%s\n",choose);
//		printf("pid=%s\n",pid);
		send(sockfd, choose, sizeof(choose), 0);
		if(choose[0]!='k') printf("Connected\n");
		else return 0;
//		if(choose[0]!='a')
		send(sockfd, pid, sizeof(pid), 0);
		recv(sockfd, buffer, sizeof(buffer), 0);
		recv(sockfd, message, sizeof(message), 0);
		printf("%s\n", buffer);
		printf("%s\n", message);
	}
	close(sockfd);
	return 0;
}

