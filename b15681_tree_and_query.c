#include <stdio.h>

#define MAX_N 100000
#define MAX_M 199998

int head[MAX_N];
int to[MAX_M];
int next[MAX_M];
int edge_no = 1;

int answer[MAX_N];

void add_edge(int a, int b) {
	to[edge_no - 1] = b;
	next[edge_no - 1] = head[a];
	head[a] = edge_no;
	++edge_no;
}

void dfs(int root) {
	answer[root] = 1;
	int edge = head[root];
	while (edge) {
		int node = to[edge - 1];
		if (!answer[node]) {
			dfs(node);
			answer[root] += answer[node];
		}
		edge = next[edge - 1];
	}
}

int main(void) {
	int n, r, q;
	scanf("%d %d %d", &n, &r, &q);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		add_edge(u, v);
		add_edge(v, u);
	}

	dfs(r - 1);
	for (int i = 0; i < q; ++i) {
		int u;
		scanf("%d", &u);
		printf("%d\n", answer[u - 1]);
	}
}
