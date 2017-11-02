#include "client.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char choose, pid;
int initial(){
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
		if(choose=='k')	exit(-1);
		else if((choose<61||choose>106))return 0;
		else{
				printf("pid? ");
				scanf("%c", &pid);
				printf("\n");
		}
}
int main(int argc, char **argv)
{
	while(1){
			initial();	
	}
	return 0;
}

