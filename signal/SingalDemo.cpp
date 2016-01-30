#include<signal.h>
#include<stdio.h>
#include<unistd.h>

void printsigset(const sigset_t *set)
{
	int i;
	for(int i=1;i<32;i++)
	{
		if(sigismember(set,i) == 1)
			putchar('1');	
		else
			putchar('0');
	}
	puts("");
}
int main(void)
{
	int i=0;
	sigset_t s,p;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigaddset(&s,SIGTSTP);
	sigprocmask(SIG_BLOCK,&s,NULL);
	while(1){
		sigpending(&p);		
		printsigset(&p);

		if(i==10)
		{
			int k =	sigdelset(&s,SIGTSTP);
//			int g =	sigdelset(&s,SIGINT);

			puts("--1----");	
			printsigset(&s);
			puts("--1---");	
//			printf("%d\n",k);
			int n =	sigprocmask(SIG_UNBLOCK,&s,NULL);
//			printf("after procmask :%d\n",n);

			puts("--2----");        
                        printsigset(&s);
                        puts("--2---");			

			sigpending(&p);		
			printsigset(&p);
			printf("\n\n");

		}
		sleep(1);
		i++;
	}
	return 0;
}
