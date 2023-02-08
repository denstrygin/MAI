#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void q_insert_with_order(queue *q, double val){
	bool is_inserted = false;
	queue new_q;
	q_init(&new_q);

	if (q_is_empty(q)){
		q_push_back(q, val);
		return;
	}
	double el;
	while(!q_is_empty(q)){
		el = q_pop_front(q);
		if (el > val && !is_inserted){
			q_push_back(&new_q, val);
			is_inserted = true;
		}
		q_push_back(&new_q, el);
	}
	if (!is_inserted){
		q_push_back(&new_q, val);
	}
	while(!q_is_empty(&new_q)){
		q_push_back(q, q_pop_front(&new_q));
	}
}

void q_sort(queue *q){
	queue sorted;
	q_init(&sorted);

	while(!q_is_empty(q)){
	    q_insert_with_order(&sorted, q_pop_front(q));
	}
	while (!q_is_empty(&sorted)){
		q_push_back(q, q_pop_front(&sorted));
	}
}

int main(int argc, char const *argv[]){
	queue q;
	q_init(&q);
	printf("Enter your queue:\n");
	double val;
	while (scanf("%lf", &val) == 1){
		q_push_back(&q, val);
	}
	printf("---\n");
	printf("Sorted:\n");
	q_sort(&q);
	int num = 1;
	while(!q_is_empty(&q)){
		printf("%d) %lf\n",num ,q_pop_front(&q));
		num++;
	}
	return 0;
}