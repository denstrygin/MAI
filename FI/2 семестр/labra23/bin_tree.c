#include "bin_tree.h"
#include <stdlib.h>
#include <stdio.h>

bool tree_add(treeptr* t, words v) {
    if (*t == NULL) {
        *t = (treeptr)malloc(sizeof(tree));
        if (*t == NULL) {
            return false;
        }

        (*t)->val = v;
        (*t)->l = NULL;
        (*t)->r = NULL;
        return true;
    }

    if (v < (*t)->val) {
        return tree_add(&(*t)->l, v);
    }
    else if (v > (*t)->val) {
        return tree_add(&(*t)->r, v);
    }
    else {
        return false;
    }
}

void remove_node(treeptr* t) {
    treeptr tofree = *t;
    treeptr l = (*t)->l;
    treeptr r = (*t)->r;

    if (r == NULL) {
        *t = l;
    }
    else if (l == NULL) {
        *t = r;
    }
    else {
        treeptr* new_tree = &(*t)->l;
        while ((*new_tree)->r != NULL) {
            new_tree = &(*new_tree)->r;
        }

        treeptr l_max = *new_tree;
        treeptr check = l_max->l;
        *new_tree = (*new_tree)->l;
        if (l_max == l)
            l_max->l = check;
        else
            l_max->l = l;
        l_max->r = r;
        *t = l_max;
    }

    free(tofree);
}

void delete_tree(treeptr* t) {
    while (*t != NULL) {
        remove_node(t);
    }
}

void _print_tree(treeptr t, char* names[], int level) {
    if (t == NULL) {
        return;
    }

    _print_tree(t->r, names, level + 1);

    for (int i = 0; i < level; i++)
        printf("\t");
    printf("%s\n", names[t->val]);

    _print_tree(t->l, names, level + 1);
}

void print_tree(treeptr root, char* names[]) {
    _print_tree(root, names, 0);
}

treeptr* find_node(treeptr* t, words val) {
    //знаем значение, вернуть указатель
    if (t == NULL || *t == NULL || (*t)->val == val) {
        return t;
    }

    if ((*t)->val < val) {
        return find_node(&(*t)->r, val);
    }
    else {
        return find_node(&(*t)->l, val);
    }
}
