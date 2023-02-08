#ifndef treeptr_stack_h
#define treeptr_stack_h

#include <stdbool.h>
#include "token_tree.h"

typedef struct treeptr_stack treeptr_stack;
typedef struct treeptr_stack_el treeptr_stack_el;

struct treeptr_stack_el{
	treeptr val;
	treeptr_stack_el* next;
};

struct treeptr_stack{
	treeptr_stack_el* head;
};

void treeptr_s_init(treeptr_stack* s);
void treeptr_s_destroy(treeptr_stack* s);
bool treeptr_s_is_empty(treeptr_stack* s);
treeptr treeptr_s_pop(treeptr_stack* s);
bool treeptr_s_push(treeptr_stack* s, treeptr val);

#endif
