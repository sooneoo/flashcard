#include "flashcard/screen_context.h"


ScreenManager_Context flash_card_context(State ** state_stack, Font font) {
    return (ScreenManager_Context) {
        .state_stack = state_stack
        , .font = font
    };
}


