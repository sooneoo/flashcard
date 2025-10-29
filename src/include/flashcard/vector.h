#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <alloc/alloc.h>


typedef struct {
    Alloc * alloc;
    size_t capacity;
    size_t size;
    void ** front;
} Vector;


Vector vector(Alloc * alloc);


void vector_push_back(Vector * self, void * value);


void vector_push_front(Vector * self, void * value);


void * vector_back(Vector * self);


void * vector_front(Vector * self);


void vector_delete(Vector * self, size_t index);


void vector_delete_front(Vector * self);


void vector_delete_back(Vector * self);


void vector_finalize(Vector * self);


#endif


