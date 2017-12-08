#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int main(){


for(int i =0 ; i <100; i++) {
	//creating Timer1 and timer 2
	struct timeval timer1;
	struct timeval timer2;
	//getting the time of the prpgram launch
	gettimeofday(&timer1, NULL);
	printf("Launch Time of the Timer           : %ld : %ld \n", timer1.tv_sec, timer1.tv_usec);
//printf("%ld  %ld\n", timer1.tv_sec, timer1.tv_usec);
	//creating fork
	pid_t pid = fork();

	//child processor
	if(pid  == 0) {
		gettimeofday(&timer1, NULL);
		execlp("./file1.out", "./file1.out", NULL);
//Message if the exec function fails
		printf("Error in execitable file\n");
	}

	// parent processor of the fork 1
	else if(pid > 0) {
		// wating for child to done
		waitpid(pid,NULL,0);
		// fork and calling the "copy of Application"
	}
//error message if fork 1 fails.
	else {
		printf("************FORK FAILED****************");
	}
}
}
