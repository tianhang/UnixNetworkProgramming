#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

void sys_err(char *str,int exitno)
{
	perror(str);
	exit(exitno);
}

int main(int argc,char* argv[])
{
	int fd;
	char buf[1024] = "hello tianhang\n";
	if(argc < 2)
	{
		printf("./a.out fifoname\n");
		exit(1);
	}

	fd = open(argv[1],O_RDWR|O_NONBLOCK);
	if(fd < 0)
		sys_err("write",1);
	
	write(fd,buf,strlen(buf));
	close(fd);	

	return 0;
}
