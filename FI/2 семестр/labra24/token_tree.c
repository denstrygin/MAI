#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_tree.h"

bool insert_before(treeptr *pos, token val){
	if (*pos != NULL){
        return false;
	}

    treeptr new_node = malloc(sizeof(tree));
    if (new_node == NULL){
        return false;
    }

    new_node->val = val;
    new_node->l = NULL;
    new_node->r = NULL;
    *pos = new_node;
    return true;
}

void remove_node(treeptr *pos){
	if (*pos == NULL){
        return;
	}
    treeptr tofree = *pos;
    treeptr l = (*pos)->l;
    treeptr r = (*pos)->r;
    
    if (r == NULL){
        *pos = l;
    }
    else if (l == NULL){
        *pos = r;
    }
    else{
        *pos = l;
    }
    free(tofree);
}

void print_tree(treeptr t, int level){
	if (t == NULL){
        return;
	}

    print_tree(t->l, level + 1);

    for (int i = 0; i < level; ++i){
        printf("\t");
    }
    if (t->val.type == TOK_OP){     
        printf("%c\n", t->val.op);
    }
    else if (t->val.type == TOK_CONST){
        printf("%lf\n", t->val.constval);
    }
    else{
        printf("%s\n", t->val.varname);
    }

    print_tree(t->r, level + 1);
}

void _print_infix_form(treeptr t, token prev, bool is_start){
    if (t == NULL){
        return;
    }

    if (!is_start && t->val.type == TOK_OP){
        if (prev.type == TOK_OP){
            if ((prev.op == '*' || prev.op == '/') && (t->val.op  == '+' || t->val.op == '-')){
                printf("(");
            }
            else if (prev.op == '^' && t->val.op != '~'){
                printf("(");
            }
            else if (prev.op == '~'){
                printf("(");
            }
        }
    }

    _print_infix_form(t->l, t->val, false);

    if (t->val.type == TOK_CONST){
        printf("%lf", t->val.constval);
    }
    else if (t->val.type == TOK_OP){
        if (t->val.op != '~'){
            printf(" %c ", t->val.op);
        }
        else{
            printf(" - ");
        }
    }
    else{
        printf("%s", t->val.varname);
    }

    _print_infix_form(t->r, t->val, false);

    if (t->val.type == TOK_OP && !is_start){
        if (prev.type == TOK_OP){
            if ((prev.op == '*' || prev.op == '/') && (t->val.op  == '+' || t->val.op == '-')){
                printf(")");
            }
            else if (prev.op == '^' && t->val.op != '~'){
                printf(")");
            }
            else if (prev.op == '~'){
                printf(")");
            }
        }
    }
}

void print_infix_form(treeptr root){
    _print_infix_form(root, root->val, true);
}

void delete_tree(treeptr* root){
	while(*root != NULL)
		remove_node(root);
}