#ifndef sorting_station_h
#define sorting_station_h

#include <stdbool.h>

#include "queue.h"
#include "types.h"
#include "token_stack.h"
#include "treeptr_stack.h"
#include "token_tree.h"

read_token_res read_token(token* tok, token_type prev_type);
read_exp_res read_expression(queue *q);
bool should_pop_out(char new_op, char stack_op);
ss_result sorting_station(queue* src, queue* dest);
build_tree_res build_tree(queue* polish, treeptr *tree);

#endif 
