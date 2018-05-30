#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> //rand() e srand() estao aqui
#include <time.h>

#define MAX_STUDENTS 40
#define MIN_STUDENTS 3

/*This number indicates how many chairs exists in the hall*/
int number_chairs;
int chairs_occupied = 0;
int being_helped;
int assistant_sleeping = 0;
int can_sleep = 0;
/*This variable indicates who (using the student id) is sitting in the assistant_chair and
  is being helped in the exact moment.
  If no one is being helped in the moment, the number id is set to -1.*/

int assistant_chair = -1;

sem_t semaphore, sleep;
pthread_mutex_t mutexLock; 


void go_program(void){

	int program_time = rand() % 10;
	sleep(program_time);
}


void wakeup_assistant(void){
	sem_post(&sleep);
}

void make_assistant_sleep(void){
	can_sleep = 1;
	sem_wait(&sleep);
}

int get_help(int student_id){

	/*  get_help:

	  - Verifies if the assistant chair is free and he is available to help.
	  - If the assistant chair is occupied, the student should wait in a chair in the hall.
	  - If the number of chairs occupied is equal to the number of chairs, the function will 
	  return 0 meaning that there's no chair available anymore, and the student should go away.
	  - If the student got help, the variable being_helped will be set to 0 by the assistant, and
	  this function will return 1, meaning that the student got help.

	*/


	if(chairs_occupied < number_chairs){

		pthread_mutex_lock(&mutexLock);	
			chairs_occupied ++;
		pthread_mutex_unlock(&mutexLock);

		sem_wait(&semaphore);
			assistant_chair = student_id;
			being_helped = 1;
			if(assistant_sleeping == 1){
				wakeup_assistant();
			}
				while(being_helped > 0);
			make_assistant_sleep();
			assistant_chair = -1;
		sem_post(&semaphore);

		pthread_mutex_lock(&mutexLock);
			chairs_occupied--;
		pthread_mutex_unlock(&mutexLock);
		return 1;
	}

	else{
		return 0;
	}

}


void *std_assistant(void *param){

	
	while(1){

		sem_wait(&sleep);

		

		while(can_sleep == 0);

	}
	pthread_exit(0);
}

void *student(void *param){


	int *my_id = (int *) param;
	int help_counter = 0;

	while(help_counter < 3){
		go_program();
		help_counter = help_counter + get_help(*my_id);
	}

	pthread_exit(0);
}


int main(int argc, char argv[]){


	srand(time(NULL));

	sem_init(&semaphore, 0, 1);
	sem_init(&sleep, 0, 1);
	pthread_mutex_init(&mutexLock, NULL);

	sem_wait(&sleep); //the assistant initialize and sleep until the first student appears.

	int amount_std = rand % (MAX_STUDENTS + 1 - MIN_STUDENTS) + MIN_STUDENTS;
	number_chairs = amount_std/2;
	int i;

	pthread_t *tid;
	pthread_attr_t *attr;

	tid = (pthread_t *) malloc(sizeof(pthread_t));
	attr = (pthread_attr_t *) malloc(sizeof(pthread_attr_t));

	for(i=1; i <= amount_std; i++){
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], student, &i);
	}

	for(i=1; i <= amount_std; i++){
		pthread_join(tid[i], NULL);
	}

	free(chairs);
	free(tid);
	free(attr);
	pthread_mutex_destroy(&mutexLock);

	return 0;
}



