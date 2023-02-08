#ifndef tree_h
#define tree_h

#include <stdbool.h>
#include "types.h"

typedef struct tree tree;
typedef struct tree* treeptr;

struct tree{
    treeptr l;
    treeptr r;
    token val;
};

bool insert_before(treeptr *pos, token val);
void remove_node(treeptr *pos);
void print_tree(treeptr t, int level);
void print_infix_form(treeptr root);
void delete_tree(treeptr *root);

#endif
