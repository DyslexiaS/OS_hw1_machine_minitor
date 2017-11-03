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
	else if((choose<61||choose>106))return 0;
	else {
		printf("pid? ");
		scanf("%c", &pid);
		printf("\n");
	}
	return 0;
}
typedef struct {
	short			sin_family;		//AF_INET(IPv4)
	unsigned short	sin_port;		//port No
	struct	in_addr	sin_addr;
	char			sin_zero[8];

} SocketAddr_in;

typedef struct {
	unsigned long s_addr;			//load with inet+pton()
} in_addr;

int main(int argc, char **argv)
{
	/*	while(1){
				initial();
				switch (choose){
					case 'a':
						break;

				}
		}
	*/
	int	ClientSocket;
	ClientSocket = socket(PF_INET, SOCK_STREAM, 0);		//create socket
	if (ClientSocket == -1) {
		printf("Fail to create a socket.\n");
	}
	return 0;
}

