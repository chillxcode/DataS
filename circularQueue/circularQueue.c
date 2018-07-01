#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

typedef struct QUEUE{
	int qu[SIZE];
	int front, rear, cnt;
}

void initialize(QUEUE *queue){
	queue -> front = queue -> rear = queue -> cnt = 0;
}

int isEmpty(QUEUE *queue){
	if(queue -> cnt == 0){
		printf("Empty\n");
		return 1;
	}
	else{
		return 0;
	}
}

int isFull(QUEUE *queue){
	if(queue -> cnt == SIZE){
		printf("Full\n");
		return 1;
	}
	else{
		return 0;
	}
}

int en