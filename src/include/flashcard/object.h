#ifndef _OBJECT_H_
#define _OBJECT_H_


#include <raylib.h>


typedef struct Object {
    void (*draw)(struct Object *, Vector2);
    Vector2 (*size)(struct Object *);
} Object;


#define OBJECT(T) ((Object*) (T))


#define object_draw(T, p) (T)->draw((T), (p))


#define object_size(T) (T)->size((T))


#define object_position(T) (T)->position((T))


#endif


