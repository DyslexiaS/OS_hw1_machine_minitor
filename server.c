#include"server.h"
#define SERV_PORT 8740
char buffer[2048];
char ppid_buf[100];
int sockfd, *new_sock, accept_sock;
char path[30] = "/proc/";
char task[10] = "/task";
char choose[100],pid[100],message[100];
char* ppid;
FILE* fptr;
DIR* dir;
struct dirent* ptr;
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
	while(accept_sock = accept(sockfd, (sockaddr*)&client_info, &addrlen))	{
		puts("Connection accepted");
		pthread_t new_thread;
		new_sock = malloc(1);
		*new_sock = accept_sock;
		if( pthread_create(&new_thread, NULL, connection_handler, (void*)new_sock)<0) {
			perror("Couldn't create thread.\n");
			return 1;
		}

	}
	return 0;
}
void *connection_handler(void *sockfd)
{
	//Get socket descriptor
	int sock = *(int*)sockfd;
	while(1) {
		memset(choose,0,100);
		memset(pid,0,100);
		recv(sock, choose, sizeof(choose), 0);
		if(choose[0]=='k') break;
		printf("choose=%s\n",choose);
		//if(choose[0]!='a')
		recv(sock, pid, sizeof(pid), 0);
		printf("pid=%s\n",pid);
		client_choice();
		send(sock, buffer, sizeof(buffer), 0);
		send(sock, message, strlen(message), 0);
	}
	pthread_exit(1);
	return 0;
}
int client_choice()
{
	memset(buffer, 0, 2048);
	memset(message, 0, 100);
	strcpy(message, "You can continue to key in.");
	strcpy(path, "/proc/");
	strcat(path, pid);
	switch (choose[0]) {
	case 'a':
		dir = opendir("/proc");
		while((ptr = readdir(dir))!= NULL) {
			if(ptr->d_name[0]>'0' && ptr->d_name[0]<='9') {
				strcat(buffer,ptr->d_name);
				strcat(buffer," ");
			}
		}
		printf("%s\n", buffer);
		closedir(dir);
		break;
	case 'b':
		strcat(path, task);
		dir = opendir(path);
		if (errno == ENOENT) {
			strcpy(message, "Direction is not exist.");
			printf("Direction is not exist.\n");
			return 1;
		}
		while((ptr = readdir(dir))!= NULL) {
			if(ptr->d_name[0]>'0' && ptr->d_name[0]<='9') {
				strcat(buffer,ptr->d_name);
				strcat(buffer," ");
			}
		}
		printf("%s\n", buffer);
		closedir(dir);
		break;
	case 'c':
		strcat(path, task);
		strcat(path, "/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "children");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		fgets(buffer,2048,fptr);
		if(strlen(buffer)==0) {
			strcpy(message, "Your child is killed.");
			printf("Your child is killed.\n");
			return 1;
		}
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'd':
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'e':
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		for(int i=0; i<2; ++i)
			fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'f':
		strcat(path, "/");
		strcat(path, "cmdline");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		fgets(buffer,2048,fptr);
		if(strlen(buffer)==0) strcpy(message, "NO cmdline");
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'g':
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		for(int i=0; i<6; ++i)
			fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'h':
		strcat(path, "/");
		strcat(path, "status");
		errno=0;
		fptr = NULL;
		while((fptr = fopen(path, "r"))!=NULL) {
			if(errno) {
				strcpy(message, "This pid isn't exist.");
				printf("This pid isn't exist.\n");
				return 1;
			}
			//	memset(ppid, 0, 20);  (segmentation fault)
			for(int i=0; i<6; ++i)
				fgets(ppid_buf,2048,fptr);
			ppid = strtok(ppid_buf, "\t");
			ppid = strtok(NULL, "\n");
			if(ppid[0] != '0') {
				strcpy(pid,ppid);
				strcpy(path,"/proc/");
				strcat(path, pid);
				strcat(path, "/");
				strcat(path, "status");
				printf("path=%s\n",path);
				strcat(buffer,ppid);
				strcat(buffer," ");
				fclose(fptr);
				continue;
			} else {
				fclose(fptr);
				//	fptr = fopen(path, "r");
				//	for(int i=0; i<5; ++i)
				//		fgets(ppid_buf,100,fptr);
				//	fclose(fptr);
				strcat(buffer,"0");
				printf("%s\n", buffer);
				break;
			}
			errno=0;
		}
		break;
	case 'i':
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		for(int i=0; i<17; ++i)
			fgets(buffer,2048,fptr);
		if(strncmp(buffer,"VmSize",6)!=0) {
			strcpy(message, "The process don't have VmSize.");
			printf("The process don't have VmSize.\n");
			memset(buffer,0,2048);
			fclose(fptr);
		} else
			printf("%s\n", buffer);
		break;
	case 'j':
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			strcpy(message, "This pid isn't exist.");
			printf("Open failure\n");
			return 1;
		}
		for(int i=0; i<21; ++i)
			fgets(buffer,2048,fptr);
		if(strncmp(buffer,"VmRSS",5)!=0) {
			strcpy(message, "The process don't have VmRSS.");
			printf("The process don't have VmRSS.\n");
			memset(buffer,0,2048);
			fclose(fptr);
		} else
			printf("%s\n", buffer);
		break;
	case 'k':
		exit(1);
		break;
	}
	return 0;
}

