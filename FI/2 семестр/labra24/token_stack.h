#ifndef token_stack_h
#define token_stack_h

#include <stdbool.h>
#include "types.h"

typedef struct token_stack token_stack;
typedef struct token_stack_el token_stack_el;

struct token_stack_el{
	token val;
	token_stack_el* next;
};

struct token_stack{
	token_stack_el* head;
};

void token_s_init(token_stack* s);
void token_s_destroy(token_stack* s);
bool token_s_is_empty(token_stack* s);
token token_s_pop(token_stack* s);
bool token_s_push(token_stack* s, token val);

#endif