#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void do_sig(int n)
{
	printf("signal was triggered !\n");
}

int main(void)
{
	
	struct sigaction newact;
	
	newact.sa_handler = do_sig;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGINT,&newact,NULL);

	while(1)
	{
		printf("*****\n");	
		sleep(1);
	}
	return 0;
}
