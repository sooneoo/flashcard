#ifndef _TEXT_H_
#define _TEXT_H_


#include <raylib.h>


void DrawTextBoxed(
        Font font, const char *text, Rectangle rec, float fontSize
        , float spacing, bool wordWrap, Color tint);


#endif


