#ifndef _SCREEN_MANAGER_H_
#define _SCREEN_MANAGER_H_

#include "screen_context.h"


typedef struct {
    ScreenManager_Context * context;
    State * state;
} ScreenManager;


void flash_card_execute(ScreenManager * self);


ScreenManager flash_card(State * init_state, ScreenManager_Context * context);


#endif


