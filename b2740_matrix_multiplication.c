#include <stdio.h>

void get_mat_input(int (*matrix)[100], int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

int main(void) {
	int n, m, k, A[100][100], B[100][100], C[100][100] = { 0, };
	scanf("%d %d", &n, &m);
	get_mat_input(A, n, m);
	scanf("%d %d", &m, &k);
	get_mat_input(B, m, k);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			for (int l = 0; l < m; ++l) {
				C[i][j] += A[i][l] * B[l][j];
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
}
