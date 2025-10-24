#ifndef _BUTTON_H_
#define _BUTTON_H_


#include "object.h"
#include <stdbool.h>


typedef struct {
    Object super;
    
    Font font;
    const char * text;
    Vector2 size;
    bool hover;
} Button;


Button button(Font font, const char * text, Vector2 size);


#endif


