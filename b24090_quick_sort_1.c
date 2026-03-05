#include <stdio.h>

#define MAX 10000

int A[MAX];
int N;
int K;
int cnt;
int ans1;
int ans2;

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
		printf("%d %d\n", ans1, ans2);
	}
}

int swap(int *a, int *b) {
	++cnt;
	int t = *a;
	*a = *b;
	*b = t;
	if (cnt == K) {
		ans1 = *a;
		ans2 = *b;
		return 1;
	}
	return 0;
}

int partition(int left, int right) {
	int pivot = A[right];
	int i = left;
	for (int j = left; j < right; ++j) {
		if (A[j] <= pivot && swap(&A[i++], &A[j])) {
			return -1;
		}
	}
	if (i < right && swap(&A[i], &A[right])) {
		return -1;
	}
	return i;
}

void quick_sort(int left, int right) {
	if (left < right) {
		int q = partition(left, right);
		if (q == -1) {
			return;
		}
		quick_sort(left, q - 1);
		quick_sort(q + 1, right);
	}
}
