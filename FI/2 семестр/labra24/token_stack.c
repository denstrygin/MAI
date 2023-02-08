#include <stddef.h>
#include <stdlib.h>

#include "token_stack.h"

void token_s_init(token_stack* s){
	s->head = NULL;
}

void token_s_destroy(token_stack* s){
	while(!token_s_is_empty(s)){
		token_s_pop(s);
	}
}

bool token_s_is_empty(token_stack* s){
	return s->head == NULL;
}

bool token_s_push(token_stack* s, token val){
	token_stack_el *element = (token_stack_el*)malloc(sizeof(token_stack_el));
	if (element == NULL){
		return false;
	}
	
	element->next = s->head;
	element->val = val;
	s->head = element;
	return true;
}

token token_s_pop(token_stack* s){
	token_stack_el* e = s->head;
	token v = e->val;
	s->head = e->next;
	free(e);
	return v;
}