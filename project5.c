#include <stdio.h>
#include <signal.h>

void f(int);


int main ( ) {
	
	printf("Students:\n");
	printf("\t-James Brinkerhoff - 10621032\n");
	printf("\t-Bryson Murray - \n");
	printf("\t-Kory Kehl - \n");
	printf("Class CS 3060 - Project 5\n");

	//switch statment
	
    int i;
    signal ( SIGINT, f); //install signal handler
    for (i = 0; i < 10; i++) {
       printf(“hello\n”);
       sleep(1);
    }
    return 0;
}

void f ( int signum )
{
    printf(“\nOUCH”);
}
