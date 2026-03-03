#include <stdio.h>

#define MAX 1500
#define HMAX 2250001
#define ERR -1000000000

typedef struct heap {
	int storage[HMAX];
	int size;
} heap_t;

heap_t hp;

// 1-based
#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
#define KEY(i) (hp->storage[i])

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void init_heap(heap_t *hp) {
	hp->size = 0;
}

char is_empty_heap(heap_t *hp) {
	return !hp->size;
}

char is_full_heap(heap_t *hp) {
	return hp->size == HMAX;
}

void push_maxheap(heap_t *hp, int val) {
	if (is_full_heap(hp)) {
		return;
	}
	KEY(++hp->size) = val;
	int i = hp->size;
	while (i > 1) {
		int parent = PARENT(i);
		if (KEY(parent) >= KEY(i)) {
			break;
		}
		swap(&KEY(parent), &KEY(i));
		i = parent;
	}
}

int pop_maxheap(heap_t *hp) {
	if (is_empty_heap(hp)) {
		return ERR;
	}
	int ret = KEY(1);
	KEY(1) = KEY(hp->size--);
	int i = 1;
	while (LEFT(i) <= hp->size) {
		int l = LEFT(i);
		int r = RIGHT(i);
		int child = l == hp->size ? l : (KEY(l) >= KEY(r) ? l : r);
		if (KEY(i) >= KEY(child)) {
			break;
		}
		swap(&KEY(i), &KEY(child));
		i = child;
	}
	return ret;
}

int main(void) {
	int n;
	scanf("%d", &n);
	init_heap(&hp);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			scanf("%d", &x);
			push_maxheap(&hp, x);
		}
	}

	int ans;
	for (int i = 0; i < n; ++i) {
		ans = pop_maxheap(&hp);
	}
	printf("%d\n", ans);
}
