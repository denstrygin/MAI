#ifndef bin_tree_h
#define bin_tree_h

#include <stdbool.h>

typedef enum words words;
enum words{
	NONE = -1,
	HNG, //0
	BRUH,
	SMH,
	OK,
	SLAPP,
	LMAO,
	KEK,
	LOL,
	OMG, //8
};

typedef struct tree tree;
typedef tree* treeptr;

struct tree{
 	words val;
	treeptr l;
	treeptr r;
}; 

bool tree_add(treeptr *t, words v);
void remove_node(treeptr *t);
void delete_tree(treeptr *root);
void print_tree(treeptr root, char *names[]);
treeptr * find_node(treeptr *root, words val);

#endif
