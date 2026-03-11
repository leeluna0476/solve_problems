#include <stdio.h>
#include <ctype.h>

#define MAX 100
typedef struct stack {
	char storage[MAX];
	int top;
} _stack_t;

void init_stk(_stack_t *stk) {
	stk->top = -1;
}

int is_empty_stk(_stack_t *stk) {
	return stk->top == -1;
}

int is_full_stk(_stack_t *stk) {
	return stk->top + 1 == MAX;
}

void push_stk(_stack_t *stk, char val) {
	stk->storage[++stk->top] = val;
}

char pop_stk(_stack_t *stk) {
	return stk->storage[stk->top--];
}

char peek_stk(_stack_t *stk) {
	return stk->storage[stk->top];
}

int priority(char c) {
	if (c == '(' || c == ')') {
		return 1;
	}
	else if (c == '+' || c == '-') {
		return 2;
	}
	else {
		return 3;
	}
}

int compar(char a, char b) {
	return priority(a) - priority(b);
}

void infix_to_postfix(char *notation) {
	_stack_t stk;
	init_stk(&stk);
	while (*notation) {
		if (isalpha(*notation)) {
			putchar(*notation);
		}
		else if (*notation == '(' && !is_full_stk(&stk)) {
			push_stk(&stk, '(');
		}
		else {
			while (!is_empty_stk(&stk) && compar(peek_stk(&stk), *notation) >= 0) {
				char c = pop_stk(&stk);
				if (c == '(') {
					break;
				}
				else {
					putchar(c);
				}
			}
			if (*notation != ')') {
				push_stk(&stk, *notation);
			}
		}
		++notation;
	}
	while (!is_empty_stk(&stk)) {
		char c = pop_stk(&stk);
		if (c != '(') {
			putchar(c);
		}
	}
	putchar('\n');
}

int main(void) {
	char notation[MAX + 1];
	scanf("%s", notation);
	infix_to_postfix(notation);
}
