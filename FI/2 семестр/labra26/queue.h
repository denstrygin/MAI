#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct queue queue;
typedef struct queue_el queue_el;

struct queue_el{
	double val;
	queue_el *next;
};

struct queue{
	queue_el *first;
	queue_el *last;
};

void q_init(queue *q);
void q_destroy(queue *q);
bool q_is_empty(queue *q);
bool q_push_back(queue *q, double val);
double q_pop_front(queue *q);
