#include <stdio.h>

#define MAX 500000

int A[MAX]; // 2MB
int N;
int K;
int cnt;
int ans;

int merge_sort(int left, int right);

int main(void) {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	merge_sort(0, N - 1);
	printf("%d\n", ans ? ans : -1);
}

int count(int val) {
	++cnt;
	if (cnt == K) {
		ans = val;
		return 1;
	}
	return 0;
}

int merge(int left, int mid, int right) {
	static int marr[MAX]; // 2MB
	int i = left;
	int j = mid + 1;
	int k = left;
	int ret = 0;
	while (!ret && i <= mid && j <= right) {
		if (A[i] < A[j]) {
			marr[k] = A[i];
			++i;
		}
		else {
			marr[k] = A[j];
			++j;
		}
		ret = count(marr[k]);
		++k;
	}
	while (!ret && i <= mid) {
		marr[k] = A[i];
		ret = count(marr[k]);
		++k;
		++i;
	}
	while (!ret && j <= right) {
		marr[k] = A[j];
		ret = count(marr[k]);
		++k;
		++j;
	}
	for (i = left; !ret && i <= right; ++i) {
		A[i] = marr[i];
	}
	return ret;
}

int merge_sort(int left, int right) {
	int ret = 0;
	if (left < right) {
		int mid = (left + right) / 2;
		if (merge_sort(left, mid) || merge_sort(mid + 1, right)) {
			return 1;
		}
		ret = merge(left, mid, right);
	}
	return ret;
}
