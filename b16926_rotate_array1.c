#include <stdio.h>

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main() {
	int n, m, r, a[300][300];
	scanf("%d %d %d", &n, &m, &r);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}

	for (int k = 0; k < r; ++k) {
		int top = 0, bottom = n - 1, left = 0, right = m - 1;
		while (top < bottom && left < right) {
			int i = top, j = left;
			int t = a[top][left];
			while (i + 1 <= bottom) {
				++i;
				swap(&t, &a[i][j]);
			}
			while (j + 1 <= right) {
				++j;
				swap(&t, &a[i][j]);
			}
			while (i - 1 >= top) {
				--i;
				swap(&t, &a[i][j]);
			}
			while (j - 1 >= left) {
				--j;
				swap(&t, &a[i][j]);
			}
			++top;
			--bottom;
			++left;
			--right;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
