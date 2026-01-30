#include <stdio.h>
#include <ctype.h>

#define ERROR 2000000001
#define STACK_MAX 100
double stack[STACK_MAX + 1];
int top;

void initialize_stack(void) {
	top = -1;
}

double push(double value) {
	if (top == STACK_MAX) {
		return ERROR;
	}
	else {
		++top;
		stack[top] = value;
		return 1;
	}
}

double pop(void) {
	if (top == -1) {
		return ERROR;
	}
	else {
		return stack[top--];
	}
}

int isoperator(char c) {
	char *o = "+-*/";
	int i = 0;
	while (o[i]) {
		if (o[i] == c) {
			return i;
		}
		++i;
	}
	return -1;
}

double add(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double mul(double a, double b) {
	return a * b;
}

double div(double a, double b) {
	return a / b;
}

double calculate(char *notation, int *operands) {
	double (*op[4])(double, double) = { add, sub, mul, div };
	initialize_stack();
	while (*notation) {
		if (isupper(*notation)) {
			push(operands[*notation - 'A']);
		}
		else {
			double a = pop();
			double b = pop();
			double result = op[isoperator(*notation)](b, a);
			push(result);
		}
		++notation;
	}
	return pop();
}

int main(void) {
	int n;
	char notation[101];
	int operands[26];
	scanf("%d", &n);
	scanf("%s", notation);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &operands[i]);
	}

	printf("%.2f\n", calculate(notation, operands));
}
