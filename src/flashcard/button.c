#include "flashcard/button.h"


static void button_draw(Button * self, Vector2 position) {  
    DrawRectangleRounded(
            (Rectangle) {position.x, position.y, self->size.x, self->size.y}
            , 0.3
            , 16
            , self->hover ? YELLOW : RAYWHITE);
    DrawTextEx(
            self->font
            , self->text
            , (Vector2) {position.x + (self->size.x - MeasureTextEx(self->font, self->text, 23, 3).x) / 2, position.y + (self->size.y - 23) / 2}
            , 23
            , 3.0f
            , BLACK);
}


static Vector2 button_size(Button * self) {
    return self->size;
}


Button button(Font font, const char * text, Vector2 size) {
    return (Button) {
        .super = {
            .draw = (void(*)(Object*, Vector2)) button_draw
            , .size = (Vector2(*)(Object*)) button_size
        }
        , .font = font
        , .text = text
        , .size = size
    };
}


