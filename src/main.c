#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> //rand() e srand() estao aqui
#include <time.h>

#define MAX_STUDENTS 40
#define MIN_STUDENTS 3

int *chairs;
int number_chairs;
int lock;


int verify_chair(void){
	/*
	- returns the number of an available chair if
	it's available.
	
	- returns -1 if no chair is available
	*/
	int i;


	for(i=0;i<number_chairs;i++){

		if(chairs[i] == 0){
			return i;
		}
	}

}


void std_assistant(void *param){

	lock = 1;
	while(lock == 1); //SA sleeping...

	pthread_exit(0);
}

void student(void *param){

	lock = 0;
	pthread_exit(0);
}


int main(int argc, char argv[]){


	srand(time(NULL));

	int amount_std = rand % (MAX_STUDENTS + 1 - MIN_STUDENTS) + MIN_STUDENTS;
	number_chairs = amount_std/2;
	chairs = (int *)calloc(number_chairs,sizeof(int));

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

	return 0;
}



