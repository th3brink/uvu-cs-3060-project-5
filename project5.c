/*
Class CS 3060 - Project 5
Students:
-James Brinkerhoff - 10621032
-Bryson Murray - 10501259
-Kory Kehl - 10439952
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
	printf("\t-Kory Kehl - 10439952\n");
	

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
    	return 0;
}

void parentFunction() {

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

}
void parentSigUser1Handler(){
    char handlerMsg[] ="**** Parent SIGUSR1 handler - Received a 'task started' signal from child ****\n";
        write(1, handlerMsg, strlen(handlerMsg));
	sigreceived = 1;
}

void parentSigUser2Handler(){
	char handlerMsg[] ="**** Parent SIGUSR2 handler - Received a 'task completed' signal from the child ****\n";
        write(1, handlerMsg, strlen(handlerMsg));
	sigreceived = 1;
}

void childFunction() {
		sigset_t masknew, maskold; 
		int signum1 = SIGUSR1; 
		int signum2 = SIGUSR2; 

		struct sigaction SIGUSER1;
	        SIGUSER1.sa_handler = childSigUser1Handler;
	        sigemptyset(&SIGUSER1.sa_mask);
	        SIGUSER1.sa_flags = 0;
	        sigaction(SIGUSR1, &SIGUSER1, NULL);

	        struct sigaction SIGUSER2;
	        SIGUSER2.sa_handler = childSigUser2Handler;
	        sigemptyset(&SIGUSER2.sa_mask);
	        SIGUSER2.sa_flags = 0;
		sigaction(SIGUSR2, &SIGUSER2, NULL);

		sigprocmask(SIG_SETMASK, NULL, &masknew); 
		sigaddset(&masknew, signum1); 
		sigprocmask(SIG_SETMASK, &masknew, &maskold); 
		sigdelset(&masknew, SIGUSR1);

	/*	sigprocmask(SIG_SETMASK, NULL, &masknew);
	        sigaddset(&masknew, signum2);
	        sigprocmask(SIG_SETMASK, &masknew, &maskold);
	        sigdelset(&masknew, SIGUSR2);*/

		char waitingStartTask[] = "c- Child Running and Waiting for 'task start' Signal.\n";
		write(1,waitingStartTask,strlen(waitingStartTask));

		while (sigreceived == 0) 
	   		sigsuspend(&masknew);
		sigreceived = 0; 
		sigprocmask(SIG_SETMASK, &maskold, NULL); 
		printf("c- child starting task\n");
		sleep(3);
		kill(getppid(),SIGUSR1);

		printf("c- does work\n");

		sigprocmask(SIG_SETMASK, NULL, &masknew);
	        sigaddset(&masknew, signum2);
	        sigprocmask(SIG_SETMASK, &masknew, &maskold);
	        sigdelset(&masknew, SIGUSR2);

		while (sigreceived == 0)
	                sigsuspend(&masknew);
	        sigreceived = 0;
	        sigprocmask(SIG_SETMASK, &maskold, NULL);

		printf("c- work is done.\n");
		kill(getppid(),SIGUSR2);
		printf("c- %d Finished\n",getpid());
	//	exit(1);
}

void childSigUser1Handler(){
    char handlerMsg[] = "**** Child SIGUSR1 handler - Received a 'task start' signal from the parent process ***\n";
        write(1, handlerMsg, strlen(handlerMsg));
	sigreceived = 1;
}

void childSigUser2Handler(){
	char handlerMsg[] ="**** Child SIGUSR2 handler - Received a 'task complete verification' signal from the parent ****\n";
        write(1, handlerMsg, strlen(handlerMsg));
	sigreceived = 1;
}

