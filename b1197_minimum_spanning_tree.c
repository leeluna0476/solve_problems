#include <stdio.h>

#define MAX_V 10000
#define MAX_E 100000

typedef struct edge {
	int a;
	int b;
	int dist;
} edge_t;

edge_t edges[MAX_E];
int v;
int e;

/* HEAP */
typedef struct heap {
	edge_t storage[MAX_E + 1];
	int size;
} heap_t;

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
#define KEY(i) (ht->storage[i].dist)

void swap(edge_t *a, edge_t *b) {
	edge_t t = *a;
	*a = *b;
	*b = t;
}

void init_heap(heap_t *ht) {
	ht->size = 0;
}

char is_empty_heap(heap_t *ht) {
	return !ht->size;
}

char is_full_heap(heap_t *ht) {
	return ht->size == MAX_E;
}

void push_minheap(heap_t *ht, edge_t edge) {
	if (is_full_heap(ht)) {
		return;
	}
	ht->storage[++ht->size] = edge;
	int i = ht->size;
	while (i > 1) {
		int parent = PARENT(i);
		if (KEY(i) >= KEY(parent)) {
			return;
		}
		swap(&ht->storage[i], &ht->storage[parent]);
		i = parent;
	}
}

edge_t pop_minheap(heap_t *ht) {
	edge_t ret;
	if (!is_empty_heap(ht)) {
		ret = ht->storage[1];
		ht->storage[1] = ht->storage[ht->size--];
		int i = 1;
		while (LEFT(i) <= ht->size) {
			int l = LEFT(i);
			int r = RIGHT(i);
			int child = l == ht->size ? l : (KEY(l) <= KEY(r) ? l : r);
			if (KEY(i) <= KEY(child)) {
				break;
			}
			swap(&ht->storage[i], &ht->storage[child]);
			i = child;
		}
	}
	return ret;
}

void heap_sort(void) {
	heap_t ht;
	init_heap(&ht);
	for (int i = 0; i < e; ++i) {
		push_minheap(&ht, edges[i]);
	}
	for (int i = 0; i < e; ++i) {
		edges[i] = pop_minheap(&ht);
	}
}

/* STACK */
typedef struct pair {
	int a;
	int b;
} pair_t;

typedef struct stack {
	pair_t storage[MAX_V];
	int top;
} stk_t;

stk_t stk;

void init_stk(void) {
	stk.top = -1;
}

char is_empty_stk(void) {
	return stk.top == -1;
}

char is_full_stk(void) {
	return stk.top + 1 == MAX_V;
}

void push_stk(pair_t val) {
	if (is_full_stk()) {
		return;
	}
	stk.storage[++stk.top] = val;
}

pair_t pop_stk(void) {
	pair_t p;
	if (is_empty_stk()) {
		return p;
	}
	return stk.storage[stk.top--];
}

/* KRUSKAL */
int parent[MAX_V + 1];

void init_parent() {
	for (int i = 0; i <= v; ++i) {
		parent[i] = i;
	}
}

int get_parent(int x) {
	init_stk();
	int t = x;
	while (parent[t] != t) {
		pair_t p = { t, parent[t] };
		push_stk(p);
		t = parent[t];
	}
	while (!is_empty_stk()) {
		pair_t p = pop_stk();
		parent[p.a] = parent[p.b];
	}
	return parent[x];
}

char unify_parent(int e) {
	int pa = get_parent(edges[e].a);
	int pb = get_parent(edges[e].b);
	if (pa < pb) {
		parent[pb] = pa;
	}
	else if (pb < pa) {
		parent[pa] = pb;
	}
	else {
		return 0;
	}
	return 1;
}

int kruskal(void) {
	heap_sort();

	init_parent();

	int dist = 0;
	for (int i = 0, cnt = 0; i < e && cnt < v - 1; ++i) {
		if (unify_parent(i)) {
			dist += edges[i].dist;
			cnt += 1;
		}
	}
	return dist;
}

int main(void) {
	scanf("%d %d", &v, &e);
	for (int i = 0; i < e; ++i) {
		scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].dist);
	}

	printf("%d\n", kruskal());
}
