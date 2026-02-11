#include <stdio.h>

#define MAX 10

void print_children(short *tree, short n, short k, short l, short *rec) {
	if (l + 1 == k) {
		return;
	}
	short diff = n - (n >> 1);
	short *p = rec + (1 << l);
	for (short i = 0; i < (1 << l); ++i) {
		short a = rec[i] - diff;
		short b = rec[i] + diff;
		printf("%hd %hd ", tree[a], tree[b]);
		*(p++) = a;
		*(p++) = b;
	}
	printf("\n");
	print_children(tree, n >> 1, k, l + 1, rec + (1 << l));
}

void print_binary_tree(short *tree, short n, short k) {
	short rec[(1 << MAX) - 1];
	short root = n >> 1;
	rec[0] = root;
	printf("%hd\n", tree[root]);
	print_children(tree, n >> 1, k, 0, rec);
}

int main(void) {
	short k;
	scanf("%hd", &k);
	short n = (1 << k) - 1;
	short tree[(1 << MAX) - 1];
	for (short i = 0; i < n; ++i) {
		scanf("%hd", &tree[i]);
	}

	print_binary_tree(tree, n, k);
}
