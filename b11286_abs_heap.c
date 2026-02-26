#include <stdio.h>

#define HMAX 100000
typedef struct heap {
	int storage[HMAX];
	int size;
} heap_t;

#define PARENT(i) ((i - 1) >> 1)
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)
#define ABS(x) (x < 0 ? -x : x)

void swap(int *a, int *b) {
	int t = *a;
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
	return ht->size == HMAX;
}

char lesser(int a, int b) {
	int abs_a = ABS(a);
	int abs_b = ABS(b);
	return abs_a < abs_b || (abs_a == abs_b && a <= b);
}

void push_minheap(heap_t *ht, int val) {
	if (is_full_heap(ht)) {
		return;
	}
	ht->storage[ht->size] = val;
	int i = ht->size++;
	while (i) {
		int parent = PARENT(i);
		if (lesser(ht->storage[parent], ht->storage[i])) {
			break;
		}
		swap(&ht->storage[i], &ht->storage[parent]);
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
		int left = LEFT(i), right = RIGHT(i);
		int child = right == ht->size ? left : (lesser(ht->storage[left], ht->storage[right]) ? left : right);
		if (lesser(ht->storage[i], ht->storage[child])) {
			break;
		}
		swap(&ht->storage[i], &ht->storage[child]);
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
