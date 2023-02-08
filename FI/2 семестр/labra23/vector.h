#ifndef vector_h
#define vector_h
#include <stdbool.h>
#include <stddef.h>

typedef struct{
	double *buf;
	size_t size;
	size_t capacity;
} vector;

void v_init (vector *v);
void v_destroy (vector *v);
size_t v_get_size (vector* v);
bool v_set_size (vector *v, size_t s);
void v_set (vector *v, size_t i, double val);
double v_get (vector *v, size_t i);

bool v_push_back(vector *v, double val);
double v_pop_back(vector *v);

#endif
