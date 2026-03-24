#include <stdio.h>

#define min(a, b) (a < b ? a : b)
void jump(int (*A)[2], int N, int i) {
	for (int j = A[i][0]; j >= 1; --j) {
		int ni = i + j;
		if (ni > N - 1) {
			ni = N - 1;
			j = ni - i;
		}
		if (!A[ni][1] || A[i][1] + 1 < A[ni][1]) {
			A[ni][1] = A[i][1] + 1;
			if (ni < N - 1) {
				jump(A, N, ni);
			}
		}
	}
}

int main(void) {
	int N;
	scanf("%d", &N);

	int A[1000][2] = { 0, };
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i][0]);
	}

	if (N > 1) {
		jump(A, N, 0);
		printf("%d\n", A[N - 1][1] ? A[N - 1][1] : -1);
	}
	else {
		printf("0\n");
	}
}
