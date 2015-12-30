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
	char buf[1024];
	int fd_client_to_server;
	char* fifo1 = "client_to_server_fifo";
	int fd_server_to_client;
	char* fifo2 = "server_to_client_fifo";
			
	mkfifo(fifo1,0666);	
	mkfifo(fifo2,0666);	

	fd_client_to_server = open(fifo1,O_RDONLY);
	if(fd_client_to_server < 0)
		sys_err("open client",1);

	fd_server_to_client = open(fifo2,O_WRONLY);
	if(fd_server_to_client < 0)	
		sys_err("open server",2);
	
	printf("Server On ...");	
	while(1)
	{
		read(fd_client_to_server,buf,strlen(buf));			
		printf("receive data from client:%s",buf);

		write(fd_server_to_client,buf,strlen(buf));
		printf("send data back to client ... ");
	
	}
	
	close(fd_client_to_server);
	close(fd_server_to_client);
	return 0;
}
