#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void do_sig(int n)
{
	printf("wake up !");
}

int mysleep(int n)
{
	signal(SIGALRM,do_sig);
	alarm(n);
	pause();
}

int main(void)
{
	mysleep(10);
	return 0;
}
