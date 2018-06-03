#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int amount_students;
int number_chairs;
int chairs_occupied = 0;
int number_students_finished = 0;
int assistant_chair;
pthread_t assistant_tid;
pthread_attr_t assistant_attr;

sem_t chairs_queue, assistant_sleep, student_being_helped;
pthread_mutex_t chairs_mutex, student_mutex; 

void wake_assistant(void){
	sem_post(&assistant_sleep);	
}

void being_helped(void){
	sem_wait(&student_being_helped);
}

void *go_program(int student_id){
	int program_time = rand() % 100000 + 100000;
	printf("I'm student %d and I will program for %d us.\n", student_id, program_time);
	usleep(program_time);
}

void *assistant(void *param){

	int help_time;

	while(1){
		printf("I'm the assistant. I'm gonna sleep now.\n");
		sem_wait(&assistant_sleep);

		help_time = rand() % 100000 + 100000;
		printf("I'm the assistant. I'm ready to help the student %d for %d us.\n",assistant_chair,help_time);

		usleep(help_time);
		printf("I'm the assistant. I've finished with student %d.\n",assistant_chair);
		sem_post(&student_being_helped);
	}
	printf("I've finished work today.\n");
	pthread_exit(0);
}

int get_help(int student_id){

	if(chairs_occupied < number_chairs){

		pthread_mutex_lock(&chairs_mutex);	
		chairs_occupied ++;
		pthread_mutex_unlock(&chairs_mutex);	
		sem_wait(&chairs_queue);
		assistant_chair = student_id;
		printf("I'm student %d and I'll be helped now.\n", student_id);
		wake_assistant();
		being_helped();
		assistant_chair = -1;
		printf("I'm student %d and I got help.\n", student_id);
		sem_post(&chairs_queue);
		pthread_mutex_lock(&chairs_mutex);
		chairs_occupied--;
		pthread_mutex_unlock(&chairs_mutex);
		return 1;
	}
	else{
		return 0;
    }
}

void *student(void *param){
	int *my_id = (int *) param;
	int help_counter = 0;

	printf("I'm student %d.\n",*my_id);

	while(help_counter < 3){
		//pthread_mutex_lock(&student_mutex);	
			go_program(*my_id);
			if(get_help(*my_id) == 1){
				help_counter ++;
				printf("I'm student %d and I've been helped for %d times.\n", *my_id, help_counter);
			}
			else{
				printf("I'm student %d. I didn't get my help now. I'll be back another time.\n", *my_id);
			}
		//pthread_mutex_unlock(&student_mutex);	
		}
	
	printf("I'm student %d and I'm finishing now.\n", *my_id);
	
	number_students_finished++ ;
	if(number_students_finished == amount_students){
		pthread_cancel(assistant_tid);
	}

	pthread_exit(0);
}
