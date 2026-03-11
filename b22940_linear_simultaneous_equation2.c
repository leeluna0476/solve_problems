#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 6

void move_row(float (*A)[MAX_N + 1], int rownum, int n) {
	static float tmp[MAX_N + 1];
	memcpy(tmp, A[rownum], sizeof(float) * (n + 1));
	memcpy(A[rownum], A[rownum + 1], sizeof(float) * (n + 1));
	memcpy(A[rownum + 1], tmp, sizeof(float) * (n + 1));
}

void convert_to_UTM(float (*A)[MAX_N + 1], int n) {
	for (int k = 0; k < n - 1; ++k) { // pivot row
		if (!A[k][k]) {
			move_row(A, k, n);
		}
		for (int i = k + 1; i < n; ++i) { // elim x_k
			// R2(old) - R1 * a_ik / a_kk
			float m = A[i][k] / A[k][k];
			for (int j = k; j <= n; ++j) {
				A[i][j] = A[i][j] - A[k][j] * m;
			}
		}
	}
}

void backward_substitution(float (*A)[MAX_N + 1], int n) {
	int x[MAX_N];
	for (int i = n - 1; i >= 0; --i) {
		float b = A[i][n];
		float a = 0;
		for (int j = i + 1; j < n; ++j) {
			a += A[i][j];
		}
		x[i] = (int)round((b - a) / A[i][i]);
		for (int j = 0; j < n; ++j) {
			A[j][i] *= x[i];
		}
	}

	for (int i = 0; i < n; ++i) {
		printf("%d ", x[i]);
	}
	printf("\n");
}

void solve_lseq(float (*A)[MAX_N + 1], int n) {
	convert_to_UTM(A, n);
	backward_substitution(A, n);
}

int main(void) {
	int n;
	scanf("%d", &n);

	float A[MAX_N][MAX_N + 1];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j) {
			scanf("%f", &A[i][j]);
		}
	}

	solve_lseq(A, n);
}
