#include <stdio.h>
#include <math.h>

int	main() {
	int	n;
	scanf("%d", &n);
	float A[6][7];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j) {
			scanf("%f", &A[i][j]);
		}
	}

	int	pivot_idx = 0;

	while (pivot_idx < n - 1) {
		for (int t = pivot_idx + 1; t < n; ++t) {
			float	multiplier = 0 - A[t][pivot_idx] / A[pivot_idx][pivot_idx];
			for (int i = pivot_idx; i <= n; ++i) {
				A[t][i] += A[pivot_idx][i] * multiplier;
			}
		}

		int	t;
		for (t = pivot_idx + 1; t < n - 1; ++t) {
			int	zero_row = 1;
			for (int i = 0; i < n; ++i) {
				if (A[t][i]) {
					zero_row = 0;
					break;
				}
			}
			if (!zero_row) {
				break;
			}

			for (int k = t; k < n - 1; ++k) {
				for (int i = 0; i <= n; ++i) {
					A[t][i] = A[t + 1][i];
				}
			}
			for (int i = 0; i <= n; ++i) {
				A[n - 1][i] = 0;
			}
		}


		pivot_idx = t;
	}

	float	solutions[6];
	for (int i = n - 1; i >= 0; --i) {
		solutions[i] = A[i][n] / A[i][i];
		for (int j = i - 1; j >= 0; --j) {
			A[j][n] -= A[j][i] * solutions[i];
		}
	}

	for (int i = 0; i < n; ++i) {
		printf("%f ", solutions[i]);
	}
	printf("\n");

//	for (int i = 0; i < n - 1; ++i) {
//		printf("%ld ", lroundf(solutions[i]));
//	}
//	printf("%ld\n", lroundf(solutions[n - 1]));
}
