#include"client.h"
char choose[100] = "";
char pid[200] = "";
char buffer[2048];
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
	printf("which?");
	setbuf(stdin, NULL);
	scanf("%s", &choose);
	if((choose[0]>'a'&&choose[0]<'k')) {
		strcpy(pid,"");
		printf("pid?");
		setbuf(stdin, NULL);
		scanf("%s", &pid);
	}
	return 0;
}
int main(int argc, char **argv)
{
	while(1) {
		initial();
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
		send(sockfd, choose, sizeof(choose), 0);
		if(choose[0]!='k') printf("Connected\n");
		else exit(1);
		send(sockfd, pid, sizeof(pid), 0);
		recv(sockfd, buffer, sizeof(buffer), 0);
		char message[100];
		recv(sockfd, message, sizeof(message), 0);
		printf("%s\n", buffer);
		printf("%s\n", message);
		close(sockfd);
	}
	return 0;
}

