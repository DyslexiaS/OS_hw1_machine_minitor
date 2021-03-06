#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
int main ()
{
	char path[101] = "/proc/";
	char task[10]="/task";
	char choose;
	char *pid = (char*)malloc(20);
	bzero(pid, 20);
	int a;
	char *ppid;
	char buffer[2048];
	FILE* fptr;
	memset(buffer, 0, 2048);
	printf("what?");
	scanf("%c",&choose);
	printf("pid?");
	setbuf(stdin, NULL);
	scanf("%s",pid);
	DIR* dir;
	struct dirent* ptr;
	switch (choose) {
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
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, task);
		dir = opendir(path);
		if (errno == ENOENT) {
			printf("Direction is not exist.");
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
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, task);
		strcat(path, "/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "children");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		fgets(buffer,2048,fptr);
		if(strlen(buffer)==0) {
			printf("Your child is killed.");
			return 1;
		}
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'd':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'e':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		for(int i=0; i<2; ++i)
			fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'f':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "cmdline");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'g':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		for(int i=0; i<6; ++i)
			fgets(buffer,2048,fptr);
		fclose(fptr);
		printf("%s\n", buffer);
		break;
	case 'h':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		errno=0;
		fptr = NULL;
		while((fptr = fopen(path, "r"))!=NULL) {
			if(errno) {
				printf("This pid isn't exist.");
				return 1;
			}
			//memset(ppid, 0, 20);  (segmentation fault)
			for(int i=0; i<6; ++i)
				fgets(buffer,2048,fptr);
			ppid = strtok(buffer, "\t");
			ppid = strtok(NULL, "\n");
			if(ppid[0] != '0') {
				strcpy(pid,ppid);
				strcpy(path,"/proc/");
				strcat(path, pid);
				strcat(path, "/");
				strcat(path, "status");
				printf("path=%s",path);
				fclose(fptr);
				continue;
			} else {
				fclose(fptr);
				fptr = fopen(path, "r");
				for(int i=0; i<5; ++i)
					fgets(buffer,2048,fptr);
				fclose(fptr);
				printf("%s\n", buffer);
				break;
			}
			errno=0;
		}
		break;
	case 'i':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		for(int i=0; i<17; ++i)
			fgets(buffer,2048,fptr);
		if(buffer[0]!='V') {
			printf("The process don't have VmSize.");
			fclose(fptr);
		} else
			printf("%s\n", buffer);
		break;
	case 'j':
		strcpy(path,"/proc/");
		strcat(path, pid);
		strcat(path, "/");
		strcat(path, "status");
		fptr = fopen(path,"r");
		if(fptr==NULL) {
			printf("Open failure");
			return 1;
		}
		for(int i=0; i<21; ++i)
			fgets(buffer,2048,fptr);
		if(buffer[0]!='V') {
			printf("The process don't have VmRSS.");
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
