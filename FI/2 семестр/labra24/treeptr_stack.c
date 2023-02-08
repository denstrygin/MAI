#include <stddef.h>
#include <stdlib.h>

#include "treeptr_stack.h"

void treeptr_s_init(treeptr_stack* s){
	s->head = NULL;
}

void treeptr_s_destroy(treeptr_stack* s){
	while(!treeptr_s_is_empty(s)){
		treeptr_s_pop(s);
	}
}

bool treeptr_s_is_empty(treeptr_stack* s){
	return s->head == NULL;
}

bool treeptr_s_push(treeptr_stack* s, treeptr val){
	treeptr_stack_el *element = (treeptr_stack_el*)malloc(sizeof(treeptr_stack_el));
	if (element == NULL){
		return false;
	}
	
	element->next = s->head;
	element->val = val;
	s->head = element;
	return true;
}

treeptr treeptr_s_pop(treeptr_stack* s){
	treeptr_stack_el* e = s->head;
	treeptr v = e->val;
	s->head = e->next;
	free(e);
	return v;
}
