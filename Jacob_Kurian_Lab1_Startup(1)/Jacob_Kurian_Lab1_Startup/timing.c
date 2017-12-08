//Jacob Kurian
//09/14/2016
//CIS : 3207
//Section: 003
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int main(){

printf("Application and Application Copy executing in this program\n");
printf("-----------------------------------------------------------\n");
for(int i =0 ; i <100; i++) {
	//creating Timer1 and timer 2
	struct timeval timer1;
	struct timeval timer2;
	//getting the time of the prpgram launch
	gettimeofday(&timer1, NULL);
	printf("Launch Time of the Timing         : %ld : %ld \n", timer1.tv_sec, timer1.tv_usec);
	//printf("%ld  %ld\n", timer1.tv_sec, timer1.tv_usec);

	//creating fork1
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
		pid_t pid2 = fork();

		//child of fork 2
		if(pid2  == 0) {
			// executing the the "ApplicationCopy"
			execlp("./file2.out", "./file2.out", NULL);
			//Message for error in execution
			printf("Error in execitable file\n");
		}
		// parent of the second fork
		else if(pid2 > 0)
		{
			waitpid(pid2, NULL, 0);
		}
		// error message if fork 2 fails.
		else{
			printf("FOrk 2 Error\n");
		}

	}
//error message if fork 1 fails.
	else {
		printf("************FORK FAILED****************");
	}
//printf("\n");
}
}
