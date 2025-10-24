#include "flashcard/screen_context.h"


// TODO: refactor, make it clean
Font font;
Font font_bold;


ScreenManager_Context flash_card_context(State ** state_stack) {
    return (ScreenManager_Context) {
        .state_stack = state_stack
    };
}


