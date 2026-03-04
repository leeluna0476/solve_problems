#include <stdio.h>
#include <limits.h>

#define MAXV 100
#define INF INT_MAX

int G[MAXV][MAXV];
int n;

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define CON(w) (w > 0 && w < INF)

int dist(int i, int j, int k) {
	int nd = G[i][k] == INF || G[k][j] == INF ? INF : G[i][k] + G[k][j];
	if (i == j && CON(G[i][k]) && CON(G[k][j])) {
		return MAX(G[i][j], nd);
	}
	else {
		return MIN(G[i][j], nd);
	}
}

void floyd(void) {
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				G[i][j] = dist(i, j, k);
			}
		}
	}
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &G[i][j]);
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j && !G[i][j]) {
				G[i][j] = INF;
			}
		}
	}

	floyd();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (G[i][j] >= INF) {
				printf("%d ", 0);
			}
			else {
				printf("%d ", !!G[i][j]);
			}
		}
		printf("\n");
	}
}
