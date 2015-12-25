#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int fd;
	char buf[1024] = "hello,zhang tianhang!";
	fd = open(argv[1],O_CREAT|O_RDWR|O_APPEND,0644);
	
	int size = write(fd,buf,strlen(buf));
	printf("the written size is %d\n",size);
	
	return 0;
}
