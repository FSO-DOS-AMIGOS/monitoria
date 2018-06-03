#include <stdio.h>
#include "functions.h"

//$ gcc main.c -o main -lpthread

#define MAX_STUDENTS 40
#define MIN_STUDENTS 3

int main(){

	srand(time(NULL));
	sem_init(&chairs_queue, 0, 1);
	sem_init(&assistant_sleep, 0, 1);
	sem_init(&student_being_helped, 0, 1);
	pthread_mutex_init(&chairs_mutex, NULL);
	pthread_mutex_init(&student_mutex, NULL);

	sem_wait(&assistant_sleep); //this makes the assistant sleep
	sem_wait(&student_being_helped); //this makes the student waits until he/she gets helped by the assistant

	int i, *student_id;
	amount_students = rand() % (MAX_STUDENTS + 1 - MIN_STUDENTS) + MIN_STUDENTS;
	printf("Number of students today: %d \n", amount_students);
	number_chairs = amount_students/2;
	
	//Creating the assistant thread
	pthread_attr_init(&assistant_attr);
	pthread_create(&assistant_tid,&assistant_attr, assistant, NULL);

	pthread_t *tid;
	pthread_attr_t *attr;

	tid = (pthread_t *) malloc(sizeof(pthread_t)*amount_students);
	attr = (pthread_attr_t *) malloc(sizeof(pthread_attr_t)*amount_students);
	student_id = (int *) malloc(sizeof(int)*amount_students);

	for(i=0; i < amount_students; i++){
		student_id[i] = i;
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], student, &student_id[i]);
	}

	for(i=0; i < amount_students; i++){
		pthread_join(tid[i], NULL);
	}

	pthread_join(assistant_tid, NULL);

	sem_destroy(&chairs_queue);
	sem_destroy(&assistant_sleep);
	pthread_mutex_destroy(&chairs_mutex);
	pthread_mutex_destroy(&student_mutex);
	free(tid);
	free(attr);
	free(student_id);

	return 0;
}
