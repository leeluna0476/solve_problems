#include <stdio.h>

#define HMAX 131071
typedef struct heap {
	int storage[HMAX];
	int size;
} heap_t;

#define PARENT(i) ((i - 1) >> 1)
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)

void init_heap(heap_t *ht) {
	ht->size = 0;
}

char is_empty_heap(heap_t *ht) {
	return !ht->size;
}

char is_full_heap(heap_t *ht) {
	return ht->size == HMAX;
}

void push_minheap(heap_t *ht, int val) {
	if (is_full_heap(ht)) {
		return;
	}
	ht->storage[ht->size] = val;
	int i = ht->size++;
	while (i) {
		int parent = PARENT(i);
		if (ht->storage[parent] <= ht->storage[i]) {
			break;
		}
		int tmp = ht->storage[i];
		ht->storage[i] = ht->storage[parent];
		ht->storage[parent] = tmp;
		i = parent;
	}
}

int pop_minheap(heap_t *ht) {
	if (is_empty_heap(ht)) {
		return 0;
	}
	int ret = ht->storage[0];
	ht->storage[0] = ht->storage[--ht->size];
	int i = 0;
	while (LEFT(i) < ht->size) {
		int child = RIGHT(i) == ht->size ? LEFT(i) : (ht->storage[LEFT(i)] <= ht->storage[RIGHT(i)] ? LEFT(i) : RIGHT(i));
		if (ht->storage[i] <= ht->storage[child]) {
			break;
		}
		int tmp = ht->storage[i];
		ht->storage[i] = ht->storage[child];
		ht->storage[child] = tmp;
		i = child;
	}
	return ret;
}

int main(void) {
	int n;
	scanf("%d", &n);
	heap_t ht;
	init_heap(&ht);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		if (!x) {
			printf("%d\n", pop_minheap(&ht));
		}
		else {
			push_minheap(&ht, x);
		}
	}
}
