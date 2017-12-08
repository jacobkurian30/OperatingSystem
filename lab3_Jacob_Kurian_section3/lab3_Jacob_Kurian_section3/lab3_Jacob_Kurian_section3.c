//Jacob Kurian
//Lab 3 Threads
//11/05/2016
//Operating System
//Section 03
#include<semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
void* thread1();
void* handler( void *arg);
void* handler2( void *arg);
void* thread2();
void* receiver(void *arg);
volatile int totalSignal = 0;
volatile int totalSent = 0;
volatile int limit = 100;
volatile int reportUSR1 = 0;
volatile int reportUSR2 = 0;
volatile int sent1 = 0;
volatile int sent2 = 0;
volatile int receiveUSR1 = 0;
volatile int receiveUSR2 = 0;
volatile int reportCount = 0;
volatile long totalAverage1 = 0;
volatile long totalAverage2 = 0;


pthread_t threadA, threadB, threadC;
pthread_t threadHandler1, threadHandler2, threadHandler3, threadHandler4;
pthread_t reporterThread;
sem_t signalSent;

sigset_t signal_set, set2, set3;

pthread_mutex_t lockHandler = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockHandler3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockGenerator = PTHREAD_MUTEX_INITIALIZER;


int main(){

int status;

//Creating the set for 'SIGUSR1'
sigemptyset(&signal_set);
sigaddset(&signal_set, SIGUSR1);
status = pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
//creting the set for 'SIGUSR2'
sigemptyset(&set2);
sigaddset(&set2, SIGUSR2);
status = pthread_sigmask(SIG_BLOCK, &set2, NULL);
//creating the set for reporter
sigemptyset(&set3);
sigaddset(&set3, SIGUSR1);
sigaddset(&set3, SIGUSR2);
pthread_sigmask(SIG_BLOCK, &set2, NULL);
//initiating the semaphores
sem_init(&signalSent, 0, 0);
//Creting the threads for handlers
status = pthread_create(&threadHandler1, NULL, &handler, (void *) &signal_set);
	if(status != 0)
	write(STDOUT_FILENO,"Creation of Hanlder 1 failed\n",30);
status = pthread_create(&threadHandler3, NULL, &handler, (void *) &signal_set);
	if(status != 0)
        write(STDOUT_FILENO,"Creation of Hanlder 3 failed\n",30);
status = pthread_create(&threadHandler2, NULL, &handler2, (void *) &set2);
	if(status != 0)
        write(STDOUT_FILENO,"Creation of Hanlder 2 failed\n",30);

status = pthread_create(&threadHandler4, NULL, &handler2, (void *) &set2);
	if(status != 0)
        write(STDOUT_FILENO,"Creation of Hanlder 4 failed\n",30);

//Creating reporter thread
status = pthread_create(&reporterThread, NULL,receiver, (void *) &set3 );
	if(status != 0)
        write(STDOUT_FILENO,"Creation of reporter failed\n",28);

// creating threads for signal generators
status = pthread_create(&threadA, NULL, &thread1, NULL);
	if(status != 0)
        write(STDOUT_FILENO,"Creation of signal generatir failed\n",36);
status =pthread_create(&threadB, NULL, &thread1, NULL);
        if(status != 0)
	write(STDOUT_FILENO,"Creation of signal generator failed\n",36);
status = pthread_create(&threadC, NULL, &thread1, NULL);
	if(status != 0)
        write(STDOUT_FILENO,"Creation of signal generator failed\n",36);
//Joining all the threads
pthread_join(threadHandler1, NULL);
pthread_join(threadHandler2, NULL);
pthread_join(threadHandler3, NULL);
pthread_join(threadHandler4, NULL);
pthread_join(reporterThread, NULL);
pthread_join(threadA, NULL);
pthread_join(threadB, NULL);
pthread_join(threadC, NULL);
//Displaying the message
printf("~~~~~~~~~~~~~~Data Summary~~~~~~~~~~~~~~~~~~~~\n");
printf("Total Sent: %d\n", totalSent);
printf("Sent USR1: %d USR2: %d\n", sent1, sent2);
printf("Total Received : %d\n", totalSignal);
printf("Received USR1: %d Received USR2: %d\n", receiveUSR1, receiveUSR2);
printf("Total Report: %d\n", reportCount);
printf("Report USR1: %d ReportUSR2: %d\n",reportUSR1, reportUSR2);
if(reportUSR1 != 0)
printf("Total Average time of SIGUSR1: %lu microSec\n", totalAverage1/reportUSR1);
if(reportUSR2 != 0)
printf("Total Average time of SIGUSR2: %lu microSec\n", totalAverage2/reportUSR2);
return 0;
}

/*
@param arg is the set created to block the SIGUSR2.
This is the function of the SIGUSR2 handler. It wil also
calculate the total number of SIGUSR2 received. Also it
will increment the total number for received signal.
*/
void* handler2( void *arg){
        sigset_t *set2 = arg;
        int s, sig_number;
	struct timespec timedout;
        timedout.tv_sec = 0;
        timedout.tv_nsec = 0.01;

        while(totalSent < limit){
        pthread_mutex_lock(&lockHandler3);

	if(totalSent >= limit){
        pthread_mutex_unlock(&lockHandler3);
	break;
	}
       s = sigtimedwait(set2, NULL, &timedout);
	if(s > 0){
        totalSignal = totalSignal+1;
	receiveUSR2 = receiveUSR2+1;
        }
        sem_post(&signalSent);
        pthread_mutex_unlock(&lockHandler3);
        }
	return NULL;
}

/*
@param arg is the set created to block the SIGUSR1.
This is the function of the SIGUSR1 handler. It wil also
calculate the total number of SIGUSR1 received. Also it
will increment the total number for received signal.
*/


void* handler( void *arg){
	sigset_t *signal_set = arg;
	int s, sig_number;
	struct timespec timedout;
        timedout.tv_sec =0;
        timedout.tv_nsec = 0.01;

	while(totalSent < limit){
	pthread_mutex_lock(&lockHandler);

	if(totalSent >= limit){
        	pthread_mutex_unlock(&lockHandler);
	        break;
        }
       s = sigtimedwait(signal_set, NULL, &timedout);

	if(s > 0){
	totalSignal = totalSignal+1;
        receiveUSR1 = receiveUSR1+1;
	}
	sem_post(&signalSent);
	pthread_mutex_unlock(&lockHandler);
	}
	pthread_exit(0);
}

/*
This is the function for signal generating threads.
This function has the global counter for total signal
sent, toatl number of SIGUSR1 sent and toatl number of
SIGUSR2 sent.
*/
void* thread1(){
int result;
time_t t;
srand((unsigned) time(&t));
int picker;
int picker2;
int num = 0;

//while loop run until it generates signal up to the 'limit'
	while(totalSent < limit){
        	pthread_mutex_lock(&lockGenerator);
               if(totalSent >=limit)
                {
	                pthread_mutex_unlock(&lockGenerator);
        	        break;
                }
		//Randomly choosing what signal to sent
		picker = rand();
		if((picker%2) == 0){
		//randomly choosing the handler for SIGUSR1
			picker2 = rand();

			if((picker2%2) == 1){
			result = pthread_kill(threadHandler1, SIGUSR1);
			}
			else{
			result = pthread_kill(threadHandler3, SIGUSR1);
			}
			sent1++;
			pthread_kill(reporterThread, SIGUSR1);
	}
		else{

		//Randomly choosing the handler for SIGUSR2
			picker2 = rand();

			if((picker2%2) == 0){
			result =pthread_kill(threadHandler2, SIGUSR2);
			}
			else{
			result = pthread_kill(threadHandler4, SIGUSR2);
			}
			sent2++;
			pthread_kill(reporterThread, SIGUSR2);
		}

		//microsecond from 10000 to 100000
		num = rand()/100000;
		if(num < 50000)
			num =  50000;
		usleep(num);
		if(totalSent >=limit)
		{
                pthread_mutex_unlock(&lockGenerator);
		break;
		}
		sem_wait(&signalSent);
  		totalSent++;
	      	pthread_mutex_unlock(&lockGenerator);
	}
	return NULL;
}
/*
@param: arg is the 'set3' that blocks both SIGUSR1 and SIGUSR2
This is the funtion for reporter thread. This will get the
the signal from the 'signal Generating' threads. Each
SIGUSR1 and SIGUSR2 has seperate counter. After the funtion get
10 signals, it will print the number of signals, system time
and average time.
*/

void* receiver(void *arg){
struct timeval start, start2, sysTime ;
long startSecUSR1  = 0;
long startMSecUSR1 = 0;
long endSecUSR1 = 0;
long endMSecUSR1 =0;
long startSecUSR2  = 0;
long startMSecUSR2 = 0;
long endSecUSR2 = 0;
long endMSecUSR2 =0;
long localUSR1 = 0;
long localUSR2 = 0;
long total1 = 0;
long total2 = 0;
//long totalAverage1 = 0;
//long totalAverage2 = 0;
        sigset_t *set3 = arg;
        int s, sig_number;
        struct timespec timedout;
        timedout.tv_sec =1;
        timedout.tv_nsec = 0.01;
char *str;
int Repcounter = 0;
gettimeofday(&start, NULL);
long startTime = start.tv_sec;
long startTimeMicro= start.tv_usec;
	while( (s = sigtimedwait(set3, NULL, &timedout)) > 0){
		//checking signal type
		if(s == SIGUSR1){
		reportUSR1 = reportUSR1 + 1;
		localUSR1 = localUSR1 + 1;
		gettimeofday(&start, NULL);
		endMSecUSR1 = start.tv_usec;
			if(endMSecUSR1 < startMSecUSR1){
	                  total1 = total1 + ((endMSecUSR1+1000000) - startMSecUSR1);
			  totalAverage1 = totalAverage1 +  ((endMSecUSR1+1000000) - startMSecUSR1);
			}
			else{
                         total1 = total1 + (endMSecUSR1 - startMSecUSR1);
			totalAverage1 = totalAverage1 +  (endMSecUSR1 - startMSecUSR1);
		}
//			 printf("--------end %lu start:  %lu total: %lu:  \n",endMSecUSR1, startMSecUSR1, total1);
                         startMSecUSR1 = endMSecUSR1;
		}
		else{
		reportUSR2 = reportUSR2 + 1;
		localUSR2 = localUSR2 +1;
		gettimeofday(&start2, NULL);
		endMSecUSR2 = start2.tv_usec;
			if(endMSecUSR2 < startMSecUSR2){
			 total2 = total2 + ((endMSecUSR2 + 1000000) - startMSecUSR2);
			totalAverage2 = totalAverage2 +  ((endMSecUSR2 + 1000000) - startMSecUSR2);
			}
			else{
			total2 = total2+ (endMSecUSR2 - startMSecUSR2);
			totalAverage2 = totalAverage2 + (endMSecUSR2 - startMSecUSR2);
			}
//                         printf("--------end %lu start:  %lu total: %lu:  \n",endMSecUSR2, startMSecUSR2, total2);

			startMSecUSR2 = endMSecUSR2;
		}
		reportCount= reportCount +1 ;
		Repcounter= Repcounter + 1;
		//The print message that should print after 10 signals

		if(Repcounter == 10){
		gettimeofday(&sysTime, NULL);
		printf("---------------Report After 10 Signals------------\n");
		printf("System Time: %lu.%lu\n",sysTime.tv_sec, sysTime.tv_usec);
		if(localUSR1 != 0)
			printf("Average Time SIGUSR1 %lu microSec\n", total1/localUSR1);
		else
			printf("No SIGUSR1 generated\n");
		if(localUSR2 != 0)
			printf("Average Time SIGUSR2 %lu microSec\n", total2/localUSR2);
		else
			printf("NO SIGUSR2 geberated\n");
		total1 = 0;
		total2 =0;
		localUSR2 =0;
		localUSR1 = 0;
		Repcounter =0;
		printf("---------------------------------------------------\n\n");
		}
	}
gettimeofday(&start, NULL);
long endTime = start.tv_sec;
long endTimeMicro= start.tv_usec;
if(endTimeMicro < startTimeMicro);
endTimeMicro = endTimeMicro + 1000000;
printf("Total Time Taken (sec, microSec) : %lu.%lu\n ", (endTime- startTime), (endTimeMicro- startTimeMicro));

}
