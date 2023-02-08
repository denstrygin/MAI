#ifndef queue_h
#define queue_h

#include <stdbool.h>
#include "types.h"

typedef struct queue queue;
typedef struct queue_el queue_el;

struct queue_el{
	token val;
	queue_el *next;
};

struct queue{
	queue_el *first;
	queue_el *last;
};

void q_init(queue *q);
void q_destroy(queue *q);
bool q_is_empty(queue *q);
bool q_push(queue *q, token val);
token q_pop(queue *q);
void q_print(queue *q);

#endif
