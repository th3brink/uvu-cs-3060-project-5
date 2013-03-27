/*
Class CS 3060 - Project 5
Students:
-James Brinkerhoff - 10621032
-Bryson Murray - 10501259
-Kory Kehl - 1043993
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//void f(int);
/*
 parentFunction
 Description: 
 Return: None
 Paramaters: Takes child ppid
*/
void parentFunction();
void parentSigUser1Handler();
void parentSigUser2Handler();
void childFunction();
void childSigUser1Handler();
void childSigUser2Handler();

static volatile sig_atomic_t sigreceived = 0;
/*
 
*/
int main ( ) {
	printf("Class CS 3060 - Project 5\n");
	printf("Students:\n");
	printf("\t-James Brinkerhoff - 10621032\n");
	printf("\t-Bryson Murray - 10501259\n");
	printf("\t-Kory Kehl - 1043993\n");
	

	int child;
	printf("creating child...\n");
	child = fork();
	int switchCommand = child;
	if(child > 0)
	{
		switchCommand = 1;
	}
	switch(switchCommand)
	{
		case 1:
			parentFunction();
			break;
		case 0:		
			childFunction();
			break;
		case  -1:
			printf("failed\n");                                      	
			break;
	}
/*	int i;
    	signal ( SIGINT, f); //install signal handler
    	for (i = 0; i < 10; i++) {
       		printf("hello\n");
       		sleep(1);
	}*/
    	return 0;
}

/*void f ( int signum )
{
    printf("\nOUCH\n");
}*/

void parentFunction() {
/*	struct sigaction SIGUSER1;
	SIGUSER1.sa_handler = parentSigUser1Handler;
	sigemptyset(&SIGUSER1.sa_mask);
	SIGUSER1.sa_flags = 0;
	if(sigaction(SIGINT, &SIGUSER1, NULL)<0)
	{
		
	}
	struct sigaction SIGUSER2;
        SIGUSER2.sa_handler = parentSigUser2Handler;
        sigemptyset(&SIGUSER2.sa_mask);
        SIGUSER2.sa_flags = 0;
        if(sigaction(SIGINT, &SIGUSER2, NULL)<0)
        {

       	}*/

	sigset_t masknew, maskold;
        int signum1 = SIGUSR1;
        int signum2 = SIGUSR2;	

	struct sigaction SIGUSER1;
	SIGUSER1.sa_handler = parentSigUser1Handler;
	sigemptyset(&SIGUSER1.sa_mask);
	SIGUSER1.sa_flags = 0;
	sigaction(SIGUSR1, &SIGUSER1, NULL);

	struct sigaction SIGUSER2;
        SIGUSER2.sa_handler = parentSigUser2Handler;
        sigemptyset(&SIGUSER2.sa_mask);
        SIGUSER2.sa_flags = 0;
        sigaction(SIGUSR2, &SIGUSER2, NULL);

	sigprocmask(SIG_SETMASK, NULL, &masknew);
        sigaddset(&masknew, signum1);
        sigprocmask(SIG_SETMASK, &masknew, &maskold);
        sigdelset(&masknew, SIGUSR1);
	sleep(3);
	printf("p- Child Process Start\n");
        kill(childId,SIGUSR1);
//        sigsuspend(&masknew);

	while (sigreceived == 0)
                sigsuspend(&masknew);
        sigreceived = 0;
        sigprocmask(SIG_SETMASK, &maskold, NULL);
	sleep(3);	

	sigprocmask(SIG_SETMASK, NULL, &masknew);
        sigaddset(&masknew, signum2);
        sigprocmask(SIG_SETMASK, &masknew, &maskold);
        sigdelset(&masknew, SIGUSR2);

	kill(childId,SIGUSR2);
	printf("p- Parent has sent SIGUSR2.\n");
	
	while (sigreceived == 0)
                sigsuspend(&masknew);
        sigreceived = 0;
        sigprocmask(SIG_SETMASK, &maskold, NULL);
	
	printf("p- %d Finished\n",getpid());
	
/*	printf("Parent Process\n");
	sleep(1);
        printf("parent stuff\n");
        sleep(1);
        printf("parent stuff\n");
        sleep(1);
        printf("parent stuff\n");
        sleep(1);
        printf("parent stuff\n");
        sleep(1);*/
}
void parentSigUser1Handler() {

}

void parentSigUser2Handler() {

}

void childFunction() {
	struct sigaction SIGUSER1;
        SIGUSER1.sa_handler = childSigUser1Handler;
        sigemptyset(&SIGUSER1.sa_mask);
        SIGUSER1.sa_flags = 0;
        if(sigaction(SIGINT, &SIGUSER1, NULL)<0)
        {

        }
        struct sigaction SIGUSER2;
        SIGUSER2.sa_handler = childSigUser2Handler;
        sigemptyset(&SIGUSER2.sa_mask);
        SIGUSER2.sa_flags = 0;
        if(sigaction(SIGINT, &SIGUSER2, NULL)<0)
        {

        }

/* 	printf("child Process\n");
        sleep(1);
        printf("child stuff\n");
        sleep(1);
        printf("child stuff\n");
        sleep(1);
        printf("child stuff\n");
        sleep(1);
        printf("child stuff\n");
        sleep(1);
        printf("exiting child\n");
        exit(1);*/
}

void childSigUser1Handler() {

}

void childSigUser2Handler() {

}

