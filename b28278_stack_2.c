#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct stack {
	int *storage;
	int top;
	int size;
} _stack_t;

void initialize_stack(_stack_t *stk) {
	stk->top = -1;
	stk->size = 1;
	stk->storage = malloc(sizeof(int) * stk->size);
}

void push(_stack_t *stk, int value) {
	stk->top += 1;
	if (stk->size == stk->top) {
		stk->size <<= 1;
		stk->storage = realloc(stk->storage, sizeof(int) * stk->size);
	}
	stk->storage[stk->top] = value;
}

int pop(_stack_t *stk) {
	if (stk->top == -1) {
		return -1;
	}
	else {
		return stk->storage[stk->top--];
	}
}

int number(_stack_t *stk) {
	return stk->top + 1;
}

int isempty(_stack_t *stk) {
	return stk->top == -1;
}

int peek(_stack_t *stk) {
	if (stk->top == -1) {
		return -1;
	}
	else {
		return stk->storage[stk->top];
	}
}

void remove_stack(_stack_t *stk) {
	free(stk->storage);
	stk->storage = NULL;
	stk->top = -1;
	stk->size = 0;
}

void operate(_stack_t *stk, int cmd) {
	int value;
	switch (cmd) {
		case 1:
			scanf("%d", &value);
			push(stk, value);
			break;
		case 2:
			printf("%d\n", pop(stk));
			break;
		case 3:
			printf("%d\n", number(stk));
			break;
		case 4:
			printf("%d\n", isempty(stk));
			break;
		case 5:
			printf("%d\n", peek(stk));
			break;
		default:
			break;
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	_stack_t stk;
	initialize_stack(&stk);
	for (int i = 0; i < n; ++i) {
		int cmd;
		scanf("%d", &cmd);
		operate(&stk, cmd);
	}
	remove_stack(&stk);
}
