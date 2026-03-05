#include <stdio.h>

#define MAX 10000

int A[MAX];
int N;
int K;
int cnt;

void quick_sort(int left, int right);

int main(void) {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}

	quick_sort(0, N - 1);

	if (cnt < K) {
		printf("%d\n", -1);
	}
	else {
		for (int i = 0; i < N; ++i) {
			printf("%d ", A[i]);
		}
		printf("\n");
	}
}

int swap(int *a, int *b) {
	++cnt;
	int t = *a;
	*a = *b;
	*b = t;
	if (cnt == K) {
		return 1;
	}
	return 0;
}

int partition(int left, int right) {
	int pivot = A[right];
	int i = left;
	for (int j = left; j < right; ++j) {
		if (A[j] <= pivot && swap(&A[i++], &A[j])) {
			return i;
		}
	}
	if (i < right) {
		swap(&A[i], &A[right]);
	}
	return i;
}

void quick_sort(int left, int right) {
	if (left < right) {
		int q = partition(left, right);
		if (cnt < K) {
			quick_sort(left, q - 1);
		}
		if (cnt < K) {
			quick_sort(q + 1, right);
		}
	}
}
