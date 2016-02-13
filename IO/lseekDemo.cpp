#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;
int get_file_size(int fd)
{
	off_t currpos;
	currpos = lseek(fd,0,SEEK_END);
	return currpos;
}

int  create_file_with_size(char* filename,int size)
{
	int fd;
	char buf[] = "fdsfdf";
	fd = open(filename,O_RDWR|O_CREAT,0644);	
	lseek(fd,size,SEEK_END);
	write(fd,buf,1);
	close(fd);
	return fd;
}
int main()
{
 	char filename[] = "seekfile2";
	int size = 1024*1024;
	create_file_with_size(filename,size);
	int fd = open(filename,O_RDWR);
	cout<<"fd->"<<fd<<endl;
	cout<<get_file_size(fd)<<endl;
	
	return 0;	
}
int main2()
{
	int fd;
	ssize_t in;
	char buf[1024];
//	fd = open("myfile",O_RDWR|O_CREAT|O_TRUNC,0644);
	fd = open("tianhang.txt",O_RDWR|O_CREAT,0644);
//	write(fd,buf,sizeof(buf));
	while((in = read(fd,&buf,5)) > 0 )
	{
//		cout<<in<<endl;
		cout<<buf<<endl;	
	}
	return 0;
}
