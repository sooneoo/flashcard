#include "flashcard/vector.h"

#include <string.h>


Vector vector(Alloc * alloc) {
    return (Vector) {
        .alloc = alloc
    };
}


static inline void vector_resize(Vector * self) {
    self->capacity = (self->capacity + 1) * 2;
    self->front = resize(self->alloc, self->front, sizeof(void*) * self->capacity);
}


void vector_push_back(Vector * self, void * value) {
    if(self->size >= self->capacity) {
        vector_resize(self);
    }

    self->front[self->size++] = value;
}


void vector_push_front(Vector * self, void * value) {
    if(self->size >= self->capacity) {
        vector_resize(self);
    }

    memmove(&self->front[1], self->front, sizeof(void*) * self->size);
    self->front[0] = value;
    self->size++;
}


void * vector_back(Vector * self) {
    return self->front[self->size - 1];
}


void * vector_front(Vector * self) {
    return self->front[0];
}


void vector_delete(Vector * self, size_t index) {
    if(index < self->size) {
        memmove(&self->front[index], &self->front[index+1], sizeof(void*) * (self->size - 1));
        self->size--;
    }
}


void vector_delete_front(Vector * self) {
    memmove(self->front, &self->front[1], sizeof(void*) * (self->size - 1));
    self->size--;
}


void vector_delete_back(Vector * self) {
    self->size--;
}


void vector_finalize(Vector * self) {
    if(self->alloc != NULL && self->front != NULL) {
        delete(self->alloc, self->front);
    }
}


