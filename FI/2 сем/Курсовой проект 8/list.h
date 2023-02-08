#include "stdio.h"
#include "stdbool.h"

typedef struct list_el{
    int val;
    size_t next;
}list_el;

typedef struct list{
    list_el *buf;
    size_t cap;
    size_t size;
    size_t first;
    size_t last;
    size_t empty;
}list;

typedef list *listptr;

typedef struct list_iter{
	listptr l;
	size_t prev;
}list_iter;


bool list_init(listptr *l);
void list_deinit(listptr *l);
bool list_push_back(listptr l, int val);
bool list_push_front(listptr l, int val);
bool list_is_empty(listptr l);
list_iter list_begin(listptr l);
list_iter list_end(listptr l);
int list_iter_get_val(list_iter this);
size_t list_get_size(listptr l);
void list_iter_set_val(list_iter this, int val);
void list_iter_next(list_iter* this);
bool list_iter_is_equals(list_iter first, list_iter second);
bool list_iter_insert_before(list_iter* this, int val);
bool list_iter_remove(list_iter* this);