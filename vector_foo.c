#include <stdio.h>
#include <stdlib.h>
#include "vector.c"

void vector_init(vector* this){
    this->data = NULL;
    this->size = 0;
    this->capacity = 0;
}

void vector_init_size(vector* this, size_t n){
    this->data = malloc(n * sizeof(int));
    this->size = n;
    this->capacity = n;
}

void vector_init_fill(vector* this, size_t n, int value){
	this->size = n;
	this->capacity = n;
	this->data = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++) this->data[i] = value;
}

void vector_destroy(vector* this){
	free(this->data);
	this->data = NULL;
	this->size = 0;
	this->capacity = 0;
}

void vector_copy(vector* this, const vector* other){
	this->size = other->size;
	this->capacity = other->capacity;
	this->data = malloc(this->size);
	for(int i =  0; i < this->size; i++) this->data[i] = other->data[i];
}

//2. Assignment Operators

vector* vector_assign(vector* dest, const vector* src){
	if(!(dest->data)) vector_destroy(dest);
	vector_copy(dest, src);
	return dest;
}

//3. Element Access

int* vector_at(vector* v, size_t index){
	if(index >= v->size) return NULL;
	return (v->data) + index;
}

int* vector_front(vector* v){
	if(!(v->size)) return NULL;
	return v->data;
}

int* vector_back(vector* v){
	if(!(v->size)) return NULL;
	return (v->data) + (v->size - 1);
}

//4. Capacity

int vector_empty(const vector* v){
	if(v->size) return 0;
	return 1;
}

size_t vector_size(const vector* v){
    return v->size;
}

size_t vector_capacity(const vector* v){
    return v->capacity;
}

void vector_reserve(vector* v, size_t new_cap){
    if(v->capacity < new_cap){
        v->cap = new_cap;
        v->data = realloc(v->data, new_cap);
    }
}

//5.Modifiers


void vector_clear(vector* v){
    for(int i = 0; i < v->size; i++) v->data[i] = 0;
    v->size = 0;
}

void vector_push_back(vector* v, int value){
    if(v->size == v->capacity){
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity);
    }
    v->data[size] = value;
    ++(v->size);
}

void vector_pop_back(vector* v){
    if(!(v->size)) return;
    --(v->size);
}

void vector_insert(vector* v, size_t pos, int value){
    if(v->size == v->capacity){
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity);
    }
    ++(v->size);
    int tmp = value;
    for(int i = size - 1; i > pos; i--){
        v->data[i] = v->data[i - 1];
    }
    v->data[pos] = value;
}

void vector_erase(vector* v, size_t pos){
	if(pos >  v->size) return;
	for(int i = pos; i < (v->size - 1); i++) v->data[i] = v->data[i + 1];
	(v->size)--;
}

void vector_resize(vector* v, size_t count){
	if(count > v->capacity) vector_reserve(v, count);
	v->size = count;
}

void swap(vector* v1, vector* v2){
	int* tmp = v1->data;
	v1->data = v2->data;
	v2->data = tmp;
	size_t tmp1 = v1->size;
	v1->size = v2->size;
	v2->size = tmp1;
	tmp1 = v1->capacity;
	v1->capacity = v2->capacity;
	v2->capacity = tmp1;
}
