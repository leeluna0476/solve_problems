#include <stdio.h>

#define MAXV 50
#define MAX(a, b) (a > b ? a : b)

char G[MAXV][MAXV];
char S[MAXV][MAXV];
int F[MAXV];
int maj;
int vsize;

char is_friend(int i, int j, int k) {
	return G[i][j] == 'Y' || (G[i][k] == 'Y' && G[k][j] == 'Y');
}

void count_friends(void) {
	for (int k = 0; k < vsize; ++k) {
		for (int i = 0; i < vsize; ++i) {
			for (int j = 0; j < vsize; ++j) {
				if (i != j && !S[i][j] && is_friend(i, j, k)) {
					S[i][j] = 1;
					F[i] += 1;
					maj = MAX(maj, F[i]);
				}
			}
		}
	}
}

int main(void) {
	scanf("%d", &vsize);
	for (int i = 0; i < vsize; ++i) {
		for (int j = 0; j < vsize; ++j) {
			scanf(" %c", &G[i][j]);
		}
	}

	count_friends();

	printf("%d\n", maj);
}
