#include "flashcard/screen_main.h"
#include <stdio.h>


static void draw_record(
        float x, float y, float width, const char * name, size_t size, size_t learning) {
    char buff_size[32];
    char buff_learning[32];

    snprintf(buff_size, 32, "%lld", size);
    snprintf(buff_learning, 32, "%lld", learning);

    DrawTextEx(font, name, (Vector2){x + 30, y}, FONT_SIZE, 2.0f, BLACK);
    DrawTextEx(font, buff_size, (Vector2){x + width / 2 + 40, y}, FONT_SIZE, 2.0f, BLACK);

    if(learning > 0) {
        DrawTextEx(font, buff_learning, (Vector2){x + width - 100, y}, FONT_SIZE, 2.0f, RED);
    } else {
        DrawTextEx(font, buff_learning, (Vector2){x + width - 100, y}, FONT_SIZE, 2.0f, GREEN);
    }
}


static void draw_overview(float x, float y, float width, float height) {
    DrawRectangleRounded(
            (Rectangle) {x, y, width, height}
            , 0.1
            , 16
            , RAYWHITE);

    DrawLine(x + 20, y + 45, x + width - 20, y + 45, GRAY);
 
    DrawTextEx(font_bold, "Balíček", (Vector2){x + 30, y + 10}, FONT_BOLD_SIZE, 3.0f, BLACK);
    DrawTextEx(font_bold, "Celkem", (Vector2){x + width/2 + 40, y + 10}, FONT_BOLD_SIZE, 3.0f, BLACK);
    DrawTextEx(font_bold, "Učení", (Vector2){x + width - 100, y + 10}, FONT_BOLD_SIZE, 3.0f, BLACK);
}


static State * state_screen_main_callback(State_ScreenMain * self, ScreenManager_Context * context) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    draw_overview((screen_width - 600 ) /2, 100, 600, 350);

    draw_record((screen_width - 600 ) /2, 160, 600, "Matematika", 532, 30);
    draw_record((screen_width - 600 ) /2, 195, 600, "Počítačová grafika", 112, 0);

    //TODO: refactor, make it clean
    self->btn_study.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {screen_width/4, screen_height - 150, self->btn_study.size.x, self->btn_study.size.y});
    self->btn_practice.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {screen_width/4*3 - object_size(OBJECT(&self->btn_practice)).x, screen_height - 150, self->btn_practice.size.x, self->btn_practice.size.y});

    object_draw(OBJECT(&self->btn_study), ((Vector2) {screen_width/4, screen_height - 150}));
    object_draw(
            OBJECT(&self->btn_practice)
            , ((Vector2) {screen_width/4*3 - object_size(OBJECT(&self->btn_practice)).x, screen_height - 150}));

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
            && (self->btn_study.hover == true || self->btn_practice.hover == true )) {
        return context->state_stack[State_ID_ScreenFlashCard];
    } else {
        return context->state_stack[State_ID_ScreenMain];
    }
}


State_ScreenMain state_screen_main(void) {
    return (State_ScreenMain) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_main_callback)
        } 
        , .btn_study = button(font, "Studovat", (Vector2){200, 50})
        , .btn_practice = button(font, "Procvičovat", (Vector2) {200, 50})
    };
}


