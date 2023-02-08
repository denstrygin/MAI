#include "stdio.h"
#include "stdbool.h"
#include "list.h"
#include <stdint.h>
#include <stdlib.h>

#ifndef MIN_CAP
#define MIN_CAP 4
#endif

bool list_init(listptr *l){
    *l = malloc(sizeof(list));
    if(*l == NULL)
        return false;
    (*l)->buf = NULL;
    (*l)->cap = 0;
    (*l)->size = 0;
    (*l)->first = SIZE_MAX;
    (*l)->last = SIZE_MAX;
    (*l)->empty = SIZE_MAX;
    return true;
}

void list_deinit(listptr *l){
    if(*l == NULL)
        return;
    free((*l)->buf);
    free(*l);
    *l = NULL;
}


static bool list_grow(listptr l){
    size_t new_cap = l->cap * 3 / 2;
    if(new_cap < MIN_CAP)
        new_cap = MIN_CAP;
    list_el *new_buf = realloc(l->buf, sizeof(list_el)*new_cap);
    if(new_buf == NULL){
        printf("ERROR: 0\n");
        return false;
    }
    l->buf = new_buf;
    for(size_t i = l->cap; i < new_cap; ++i){
        l->buf[i].next = l->empty;
        l->empty = i;
    }
    l->cap = new_cap;
    return true;
}

static size_t list_get_new_id(listptr l){
    size_t res = SIZE_MAX;
    if(l->empty == SIZE_MAX){
        if(list_grow(l) == false)
            return SIZE_MAX;
    }
    res = l->empty;
    l->empty = l->buf[l->empty].next;
    l->buf[res].next = SIZE_MAX;
    return res;
} 

bool list_push_front(listptr l, int val){
    size_t new_el = list_get_new_id(l);
    if(new_el == SIZE_MAX)
        return false;
    l->buf[new_el].next = l->first;
    l->buf[new_el].val  = val;
    
    l->first = new_el;
    if(l->size == 0)
        l->last = new_el;

    l->size++;
    return true;
}

bool list_push_back(listptr l, int val){
    size_t new_el = list_get_new_id(l);
    if(new_el == SIZE_MAX)
        return false;
    
    l->buf[new_el].next = SIZE_MAX;
    l->buf[new_el].val = val;

    if(l->last != SIZE_MAX){
        l->buf[l->last].next = new_el;
        l->last = new_el;
    }
    else{
        l->last = new_el;
        l->first = new_el;
    }
 
    l->size++;
    return true;
}

void list_remove_id(listptr l, size_t el){
    l->buf[el].next = l->empty;
    l->empty = el;
}

bool list_is_empty(listptr l){
    return  l->size == 0;
}

size_t list_get_size(listptr l){
    return l->size;
}

list_iter list_begin(listptr l){
    list_iter l_i = {l, SIZE_MAX};
    return l_i;
}

list_iter list_end(listptr l){
    list_iter l_i = {l, l->last};
    return l_i;
}


size_t list_iter_get_el(list_iter this){
    size_t el = SIZE_MAX;
    if(this.prev == SIZE_MAX){
        el = this.l->first;
    }else{
        el = this.l->buf[this.prev].next;
    }

    return el;
}

int list_iter_get_val(list_iter this){
    size_t el = list_iter_get_el(this);
    if(el == SIZE_MAX){
        printf("ERROR: 2\n");
        exit(1);
    }

    return this.l->buf[el].val;
}

void list_iter_set_val(list_iter this, int val){
    size_t el = list_iter_get_el(this);
    if(el == SIZE_MAX){
        printf("ERROR: 3\n");
        exit(1);
    }

    this.l->buf[el].val = val;
}

void list_iter_next(list_iter* this){
    if(this == NULL)
        return;

    this->prev = list_iter_get_el(*this);
}

bool list_iter_is_equals(list_iter first, list_iter second){
    return first.l == second.l && first.prev == second.prev;
}


bool list_iter_insert_before(list_iter* this, int val){
    if(this == NULL)
        return false;
    
    size_t new_el  = list_get_new_id(this->l);
    if(new_el == SIZE_MAX)
        return false;
    size_t el = list_iter_get_el(*this);
    
    if(this->prev == this->l->last){
        this->l->last = new_el;
    }

    if(this->prev == SIZE_MAX)
        this->l->first = new_el;
    else 
        this->l->buf[this->prev].next = new_el;

    this->l->buf[new_el].next  = el;
    this->prev = new_el;

    this->l->buf[new_el].val = val;
    this->l->size++;
    return true;
}

bool list_iter_remove(list_iter* this){
    if(this == NULL)
        return false;
    
    size_t el = list_iter_get_el(*this);
    if(el == SIZE_MAX)
        return false;
    
    if(el == this->l->last){
        this->l->last = this->prev;
    }

    if(this->prev == SIZE_MAX)
        this->l->first = this->l->buf[el].next;
    else
        this->l->buf[this->prev].next = this->l->buf[el].next;

    list_remove_id(this->l, el);
    this->l->size--;
    return true;
}