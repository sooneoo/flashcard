#include "flashcard/screen_manager.h"


void flash_card_execute(ScreenManager * self) {
    self->context->frame_time = GetFrameTime();
    self->state = self->state->callback(self->state, self->context);
}


ScreenManager flash_card(State * init_state, ScreenManager_Context * context) {
    return (ScreenManager) {
        .context = context
        , .state = init_state
    };
}


