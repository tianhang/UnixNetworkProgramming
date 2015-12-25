#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int fd[2];
	char str[1024]= "hello zhang tian hang !!\n\n";
	char buf[1024];
	pid_t pid;
	//fd[0] read
	//fd[1] write	 
	if(pid > 0){
		close(fd[0]);
		sleep(5);
		write(fd[1],str,strlen(str));
		close(fd[1]);
	}
	else if(pid == 0){
		int len;
		close(fd[1]);
		len = read(fd[0],buf,sizeof(len));
		write(STDOUT_FILENO,buf,len);
	}
	else{
		perror("fork");	
		exit(1);
	}
	return 0;
}
