#include "flashcard/screen_main.h"


static State * state_screen_main_callback(State_ScreenMain * self, ScreenManager_Context * context) {
    DrawTextEx(context->font, "hello world", (Vector2){ 400, 300 }, FONT_SIZE, 4.0f, GRAY);

    return context->state_stack[State_ID_ScreenMain];
}


State_ScreenMain state_screen_main(void) {
    return (State_ScreenMain) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_main_callback)
        }   
    };
}
