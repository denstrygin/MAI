#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "queue.h"

void q_init(queue *q){
	q->first = NULL;
	q->last = NULL;
}

void q_destroy(queue *q){
	while(!q_is_empty(q)){
	    q_pop(q);
	}
}

bool q_is_empty(queue *q){
	return q->first== NULL;
}

bool q_push(queue *q, token val){
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

token q_pop(queue* q){
	queue_el* element = q->first;
	token v = element->val;
	q->first = element->next;
	free(element);
	
	if (q->first == NULL){
		q->last = NULL;
	}
	
	return v;
}

void q_print(queue* q){
    queue_el* curr = q->first;
    if (curr == NULL){
        return;
    }

    while (curr != NULL){
        if (curr->val.type == TOK_CONST){
            printf("%lf ", curr->val.constval);
        }
        else if (curr->val.type == TOK_OP){
            printf("%c ", curr->val.op);
        }
        else{
            printf("%s ", curr->val.varname);
        }

        curr = curr->next;
    }
    printf("\n");
}