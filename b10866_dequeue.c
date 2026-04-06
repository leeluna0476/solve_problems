#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Element;

typedef struct node {
	Element data;
	struct node *prev;
	struct node *next;
} node_t;

node_t *create_node(Element data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->prev = NULL;
	n->next = NULL;
	return n;
}

Element delete_node(node_t *n) {
	Element data = n->data;
	free(n);
	return data;
}

typedef struct dequeue {
	node_t *front;
	node_t *rear;
	int size;
} dequeue_t;

void init_dq(dequeue_t *dq) {
	dq->front = NULL;
	dq->rear = NULL;
	dq->size = 0;
}

int is_empty_dq(dequeue_t *dq) {
	return !dq->front && !dq->rear;
}

void add_front(dequeue_t *dq, Element data) {
	node_t *n = create_node(data);
	if (is_empty_dq(dq)) {
		dq->front = dq->rear = n;
	}
	else {
		n->next = dq->front;
		dq->front->prev = n;
		dq->front = n;
	}
	++dq->size;
}

void add_rear(dequeue_t *dq, Element data) {
	node_t *n = create_node(data);
	if (is_empty_dq(dq)) {
		dq->front = dq->rear = n;
	}
	else {
		n->prev = dq->rear;
		dq->rear->next = n;
		dq->rear = n;
	}
	++dq->size;
}

Element delete_front(dequeue_t *dq) {
	if (is_empty_dq(dq)) {
		return -1;
	}
	else {
		node_t *n = dq->front;
		if (dq->front == dq->rear) {
			dq->front = dq->rear = NULL;
		}
		else {
			n->next->prev = NULL;
			dq->front = n->next;
		}
		--dq->size;
		return delete_node(n);
	}
}

Element delete_rear(dequeue_t *dq) {
	if (is_empty_dq(dq)) {
		return -1;
	}
	else {
		node_t *n = dq->rear;
		if (dq->front == dq->rear) {
			dq->front = dq->rear = NULL;
		}
		else {
			n->prev->next = NULL;
			dq->rear = n->prev;
		}
		--dq->size;
		return delete_node(n);
	}
}

Element get_front(dequeue_t *dq) {
	if (is_empty_dq(dq)) {
		return -1;
	}
	else {
		return dq->front->data;
	}
}

Element get_rear(dequeue_t *dq) {
	if (is_empty_dq(dq)) {
		return -1;
	}
	else {
		return dq->rear->data;
	}
}

int size_dq(dequeue_t *dq) {
	return dq->size;
}

int main(void) {
	int n;
	scanf("%d", &n);

	dequeue_t dq;
	init_dq(&dq);
	char op[11];
	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		if (!strcmp(op, "push_front")) {
			int x;
			scanf("%d", &x);
			add_front(&dq, x);
		}
		else if (!strcmp(op, "push_back")) {
			int x;
			scanf("%d", &x);
			add_rear(&dq, x);
		}
		else if (!strcmp(op, "pop_front")) {
			printf("%d\n", delete_front(&dq));
		}
		else if (!strcmp(op, "pop_back")) {
			printf("%d\n", delete_rear(&dq));
		}
		else if (!strcmp(op, "size")) {
			printf("%d\n", size_dq(&dq));
		}
		else if (!strcmp(op, "empty")) {
			printf("%d\n", is_empty_dq(&dq));
		}
		else if (!strcmp(op, "front")) {
			printf("%d\n", get_front(&dq));
		}
		else {
			printf("%d\n", get_rear(&dq));
		}
	}

	while (!is_empty_dq(&dq)) {
		delete_rear(&dq);
	}
}
