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

struct download_param{
	char *filename;
	char *p ;
	int size;
	int num; // the num of threads
	int i;//thread i	
}*param;

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
	struct download_param *p = (struct download_param *)arg;
	
	char buf[1];
	int b = p->size/p->num;
	char * a = p->p;
	char * r_start =  a+b*(p->i);
	char * r_end;

	cout<<"thread num:"<<p->i<<endl;
//	cout<<"r_start:"<<r_start<<endl;

	if(p->i == p->num-1)
	{
		r_end = a+ p->size-1;
	}
	else{
		r_end = a + b*(p->i) + b-1;
	}
	

//	cout<<"r_end:"<<r_end<<endl;
	int fd2 = open(p->filename,O_RDWR|O_CREAT,0644);	

	lseek(fd2,p->i*b,SEEK_SET);

	for(;r_start <= r_end;r_start++)	
	{
		buf[0] = *r_start;
		cout<<"thread:	"<<p->i<<"---->"<<"print:"<<buf[0]<<endl;
		write(fd2,buf,1); 	
	}
	
	close(fd2);
	return (void *)1;
}

int main(int arg,char *argv[])
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

	cout<<"p:"<<p<<endl;		

	char filename2 [] = "demo13";
	int fd2 = open(filename2,O_RDWR|O_CREAT,0644);	
	//expand file
	int size2 = get_filesize(filename2);
	
	lseek(fd2,size,SEEK_END);
	close(fd2);



	 size2 = get_filesize(filename2);
	cout<<"size1:"<<size<<endl;
	cout<<"size2:"<<size2<<endl;
	close(fd2);

	int num = 10;
	int detachstate;	
	pthread_t tid_arr[num]; 	
	struct download_param parameter[num];

	for(int i =0 ;i<num;i++)
	{
		//param: p(head address),size,num,i
		parameter[i].filename = filename2;
		parameter[i].p = p;
		parameter[i].size = size;
		parameter[i].num = num;
		parameter[i].i = i;
		param = &parameter[i];

		pthread_attr_t attr;

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		int err = pthread_create(&tid_arr[i],&attr,thr_fn,param);

//		sleep(1);
		printf("err:%d\n",err);
	
	}

	sleep(2);
//	printf("err:%d\n",err);

	return 0;		
}
