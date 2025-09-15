#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main() {
	int N;
	int k;
	scanf("%d%d", &N, &k);

	int A[200000], B[200000];
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}

	for (int i = 0; i < k; ++i) {
		int tmp[200000];
		int cnt = 0;
		for (int j = i; j < N; j += k) {
			tmp[cnt++] = A[j];
		}
		qsort(tmp, cnt, sizeof(int), cmp);
		for (int j = i, cnt = 0; j < N; j += k, ++cnt) {
			B[j] = tmp[cnt];
		}
	}

	int sorted = 1;
	for (int i = 0; i < N - 1; ++i) {
		if (B[i] > B[i + 1]) {
			sorted = 0;
			break;
		}
	}

	if (sorted) {
		printf("Yes\n");
	}
	else {
		printf("No\n");
	}
}
