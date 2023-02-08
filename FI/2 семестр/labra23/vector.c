#include "vector.h"
#include <stdlib.h>
#define MIN_CAP 4

void v_init(vector* v) {
	v->buf = NULL;
	v->size = 0;
	v->capacity = 0;
}

void v_destroy(vector* v) {
	free(v->buf);
	v->size = 0;
	v->buf = NULL;
	v->capacity = 0;
}

double v_get(vector* v, size_t i) {
	return v->buf[i];
}

void v_set(vector* v, size_t i, double val) {
	v->buf[i] = val;
}

size_t v_get_size(vector* v) {
	return v->size;
}

bool v_set_size(vector* v, size_t s) {
	if (s > v->capacity) {
		size_t new_c = v->capacity * 3 / 2;
		if (s > new_c) {
			new_c = s;
		}
		if (new_c < MIN_CAP) {
			new_c = MIN_CAP;
		}

		double* new_buf = realloc(v->buf, new_c * sizeof(double));
		if (new_buf == NULL) {
			return false;
		}
		v->buf = new_buf;
		v->capacity = new_c;

		for (size_t i = v->size; i < s; i++) {
			v->buf[i] = 0;
		}
	}
	else if (s <= v->capacity * 2 / 3) {
		//9/4 если меньше 
		size_t new_c = v->capacity * 2 / 3;

		if (new_c < MIN_CAP) {
			new_c = MIN_CAP;
		}

		v->buf = realloc(v->buf, new_c * sizeof(double));
		v->capacity = new_c;
	}

	v->size = s;
	return true;
}

/*реализация вектора с семенара
bool v_set_size (vector *v, size_t size){
	double *newbuf = realloc(v->buf, sizeof(double) * size);
	if (newbuf == NULL && size != 0) {
		return false;
	}

	for (size_t i = v->size; i < size; i++){
		newbuf[i]=0;
	}//зануляем новую память

	v->buf = newbuf;
	v->size = size;
}
*/

bool v_push_back(vector* v, double val) {
	if (!v_set_size(v, v->size + 1)) {
		return false;
	}
	v_set(v, v->size - 1, val);
	return true;
}

double v_pop_back(vector* v) {
	double res = v_get(v, v_get_size(v) - 1);
	v_set_size(v, v_get_size(v) - 1);
	return res;
}
