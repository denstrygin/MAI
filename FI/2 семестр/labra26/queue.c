#include <stdlib.h>
#include "queue.h"

void q_init(queue *q){
	q->first = NULL;
	q->last = NULL;
}

void q_destroy(queue *q){
	while(!q_is_empty(q)){
	    q_pop_front(q);
	}
}

bool q_is_empty(queue *q){
	return q->first== NULL;
}

bool q_push_back(queue *q, double val){
	queue_el* element = (queue_el*)malloc(sizeof(queue_el));
	if (element == NULL){
		return false;
	}
	
	element->next = NULL;
	element->val = val;
	
	if (q->last == NULL){
		q->first = element;
	}
	else{
		q->last->next = element;
	}
	q->last = element;
	return true;
}

double q_pop_front(queue* q){
	queue_el* element = q->first;
	double v = element->val;
	q->first = element->next;
	free(element);
	
	if (q->first == NULL){
		q->last = NULL;
	}	
	return v;
}