#include <stdio.h>

#define MAX 10000

int A[MAX];
int B[MAX];
int diff[MAX];
int dsize;
int N;
int cnt;

void quick_sort(int left, int right);
int push_all_diff(void);

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	for (int i = 0; i < N; ++i) {
		scanf("%d", &B[i]);
		if (A[i] != B[i]) {
			diff[i] = 1;
			++dsize;
		}
	}

	if (dsize) {
		quick_sort(0, N - 1);
	}

	printf("%d\n", !dsize);
}

void remove_if_equal(int x) {
	if (diff[x] && A[x] == B[x]) {
		diff[x] = 0;
		--dsize;
	}
	else if (!diff[x] && A[x] != B[x]) {
		diff[x] = 1;
		++dsize;
	}
}

int check_equal(int a, int b) {
	remove_if_equal(a);
	remove_if_equal(b);
	return !dsize;
}

int swap(int a, int b) {
	++cnt;
	int t = A[a];
	A[a] = A[b];
	A[b] = t;
	return check_equal(a, b);
}

int partition(int left, int right) {
	int pivot = A[right];
	int i = left;
	for (int j = left; j < right; ++j) {
		if (A[j] <= pivot && swap(i++, j)) {
			return i;
		}
	}
	if (i < right) {
		swap(i, right);
	}
	return i;
}

void quick_sort(int left, int right) {
	if (left < right) {
		int q = partition(left, right);
		if (!cnt || dsize) {
			quick_sort(left, q - 1);
		}
		if (!cnt || dsize) {
			quick_sort(q + 1, right);
		}
	}
}
