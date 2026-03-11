#include <stdio.h>

void hanoi(int n, char from, char tmp, char to) {
	if (!n) {
		return;
	}
	hanoi(n - 1, from, to, tmp);
	printf("%c %c\n", from, to);
	hanoi(n - 1, tmp, from, to);
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", (1 << n) - 1);
	hanoi(n, '1', '2', '3');
}
