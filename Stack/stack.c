#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

typedef struct STACK{
	int top; //Stack Pointer
	int st[SIZE]; //Stack Array
}STACK;

void initialize(STACK *stack){
	stack -> top = 0;
}

int isEmpty(STACK *stack){
	if(stack -> top == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int isFULL(STACK *stack){
	if(stack -> top == SIZE){
		return 1;
	}
	else{
		return 0;
	}
}

void push(STACK *stack, int value){
	if(isFULL(stack))
	{
		printf("Stack Full\n");
	}
	else{
		stack -> st[stack -> top] = value;
		stack -> top++;
	}
}

int pop(STACK *stack){
	if(isEmpty(stack)){
		printf("Stack Empty\n");
		return -1;
	}
	else{
		stack -> top--;
		return stack -> st[stack -> top];
	}
}

void printStack(STACK *stack){
	for (int i = 0; i < stack -> top; i++)
	{
		printf("%d -> ", stack -> st[i]);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int value;
	STACK stack;
	initialize(&stack);
	push(&stack, 5);
	push(&stack, 9);
	push(&stack, 12);

	printStack(&stack);

	value = pop(&stack);
	printf("value: %d\n", value);
	push(&stack, 7);

	printStack(&stack);
	return 0;
}





