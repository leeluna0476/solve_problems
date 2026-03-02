#include <stdio.h>

#define MAX_NODES 10001
#define MAX_EDGES 100001
#define INF 1000001

int head[MAX_NODES];
int to[MAX_EDGES * 2];
int next[MAX_EDGES * 2];
int distance[MAX_EDGES * 2];
int edge_no = 1;
int v, e;

void add_edge(int node1, int node2, int dist) {
	to[edge_no] = node2;
	next[edge_no] = head[node1];
	head[node1] = edge_no;
	distance[edge_no] = dist;
	++edge_no;
}

void init_prim_dist(int *dist) {
	dist[1] = 0;
	for (int i = 2; i <= v; ++i) {
		dist[i] = INF;
	}
}

int dist_per_edge(int a, int b) {
	int edge = head[a];
	while (edge) {
		if (to[edge] == b) {
			return distance[edge];
		}
		edge = next[edge];
	}
	return INF;
}

void Prim_MST(int *dist, int *selected, int node, int *ans) {
	int min = v + 1;
	for (int i = 1; i <= v; ++i) {
		int d = dist_per_edge(node, i);
		if (!selected[i]) {
			if (d < dist[i]) {
				dist[i] = d;
			}
			if (min == v + 1 || dist[i] < dist[min]) {
				min = i;
			}
		}
	}

	if (min != v + 1) {
		selected[min] = 1;
		*ans += dist[min];
		Prim_MST(dist, selected, min, ans);
	}
}

int MST(void) {
	int dist[MAX_NODES];
	init_prim_dist(dist);
	int selected[MAX_NODES] = { 0 };
	selected[1] = 1;
	int mst_dist = 0;
	Prim_MST(dist, selected, 1, &mst_dist);
	return mst_dist;
}

int main(void) {
	scanf("%d %d", &v, &e);
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		add_edge(a, b, c);
		add_edge(b, a, c);
	}
	printf("%d\n", MST());
}
