#include <stdio.h>

typedef struct lec {
	int a;
	int b;
	int c;
} lec_t;

#define MAXN 100001
int N;

typedef struct heap {
	lec_t storage[MAXN];
	int size;
} heap_t;

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
heap_t H1, H2;

int is_empty_heap(heap_t *h) {
	return !h->size;
}

int is_full_heap(heap_t *h) {
	return h->size + 1 == MAXN;
}

void swap(lec_t *a, lec_t *b) {
	lec_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void push_minheap(heap_t *h, lec_t val, int (*compar)(lec_t, lec_t)) {
	if (is_full_heap(h)) {
		return;
	}
	h->storage[++h->size] = val;
	int i = h->size;
	while (i > 1) {
		int p = PARENT(i);
		if (compar(h->storage[p], h->storage[i]) <= 0) {
			break;
		}
		swap(&h->storage[p], &h->storage[i]);
		i = p;
	}
}

lec_t pop_minheap(heap_t *h, int (*compar)(lec_t, lec_t)) {
	lec_t ret = { -1, -1, -1 };
	if (is_empty_heap(h)) {
		return ret;
	}
	ret = h->storage[1];
	h->storage[1] = h->storage[h->size--];
	int i = 1;
	while (LEFT(i) <= h->size) {
		int l = LEFT(i);
		int r = RIGHT(i);
		int child = l == h->size ? l : compar(h->storage[l], h->storage[r]) < 0 ? l : r;
		if (compar(h->storage[i], h->storage[child]) <= 0) {
			break;
		}
		swap(&h->storage[i], &h->storage[child]);
		i = child;
	}
	return ret;
}

lec_t peek_heap(heap_t *h) {
	lec_t ret = { -1, -1, -1 };
	if (!is_empty_heap(h)) {
		ret = h->storage[1];
	}
	return ret;
}

int cnt;

int compar_b(lec_t a, lec_t b) {
	return a.b - b.b;
}

int compar_c(lec_t a, lec_t b) {
	return a.c - b.c;
}

void count_classroom(void) {
	while (!is_empty_heap(&H1)) {
		lec_t l = pop_minheap(&H1, compar_b);
		if (!is_empty_heap(&H2) && l.b >= peek_heap(&H2).c) {
			pop_minheap(&H2, compar_c);
		}
		push_minheap(&H2, l, compar_c);
	}
	cnt = H2.size;
}

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		lec_t l;
		scanf("%d %d %d", &l.a, &l.b, &l.c);
		push_minheap(&H1, l, compar_b);
	}

	count_classroom();
	printf("%d\n", cnt);
}
