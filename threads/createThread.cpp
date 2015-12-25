#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void *th_fun(void *arg)
{
	int *p = (int *)arg;
	printf("thread PID= %d\n",getpid());
	printf("thread ID= %x\n",(unsigned int)pthread_self());
	printf("thread *arg = %d\n",*p);
	printf("\n\n");
//	sleep(3);

}
int main(void)
{
	pthread_t tid;
	int n = 10;
	pthread_create(&tid,NULL,th_fun,(void*)&n);

	printf("main thread PID= %d\n",getpid());
	printf("main thread ID= %x\n",(unsigned int)pthread_self());
	printf("child thread ID= %x\n",(unsigned int)tid);
	printf("\n\n");

//	sleep(2);
	return 0;
}
