#include "flashcard/screen_flashcard.h"


/*
 *
    DrawTextBoxed(
        context->font
        , "DASDF AS ASDF ASDFASDF AS DFA SDF ASDA FSDF ASF ASDF ASF ASD FA SDFAS DFASDFASD AS DF AS "
        , (Rectangle) {100, 100, 200,200}
        , FONT_SIZE, 4.0f, true, GRAY);
 *
 */

static State * state_screen_flash_card_callback(State_ScreenFlashCard * self, ScreenManager_Context * context) {
    return context->state_stack[State_ID_ScreenFlashCard];
} 


State_ScreenFlashCard state_screen_flash_card(void) {
    return (State_ScreenFlashCard) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_flash_card_callback)
        }
    };
}


