#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<iostream>

using namespace std;


int get_filesize(char *filename)
{
	int fd;	
	off_t curr;
	fd = open(filename,O_RDWR);
	curr = lseek(fd,0,SEEK_END);
	close(fd);
	return curr;
}

void mmap_file(char *filename,char *mapaddress)
{
	int fd = open(filename,O_RDWR);

	if(fd<0)	
	{
		perror("open file");
		exit(1);
	}

	int size = get_filesize(filename);

	mapaddress = (char*)mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
	while(size--)
	{
//		cout<<"--->"<<*mapaddress++<<endl;
	}
	if(mapaddress == MAP_FAILED)	
	{
		perror("mmap");
		exit(1);
	}
	close(fd);
}

void *thr_fn(void *arg)
{
	int i=4;
	int *p = (int*)arg;
	while(i--)
	{
		cout<<p[i]<<endl;
	}
	return (void *)1;
}

int main(int argc,int *argv[])
{
	pthread_t tid;
	void *tret;

	char *p = new char;
	char filename [] = "./demo"; 
	// map file to memory and the address is p
	int fd = open(filename,O_RDWR);

	if(fd<0)	
	{
		perror("open file");
		exit(1);
	}

	int size = get_filesize(filename);

	p = (char*)mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);

	if(p == MAP_FAILED)	
	{
		perror("mmap");
		exit(1);
	}
	close(fd);

// start to write

	char filename2 [] = "demo12";
	int fd2 = open(filename2,O_RDWR|O_CREAT,0644);	
	//expand file
	int size2 = get_filesize(filename2);
	
	lseek(fd2,size,SEEK_END);
	close(fd2);


	fd2 = open(filename2,O_RDWR|O_CREAT,0644);	

	char buf[1];
	int l = size;
	while(l--)
	{
		buf[0] = *p++;
		write(fd2,buf,1); 	
	}
	
	 size2 = get_filesize(filename2);
	cout<<"size1:"<<size<<endl;
	cout<<"size2:"<<size2<<endl;
	close(fd2);

	int num = 10;
	for(int i =0 ;i<num;i++)
	{
		//param: p(head address),size,num,i
		int param_arr[4] = {(int*)p,2,3,4};
		int err = pthread_create(&tid,NULL,thr_fn,param_arr);
	
	}

	sleep(2);
	printf("err:%d\n",err);

	return 0;		
}
