#ifndef _SCREEN_MAIN_H_
#define _SCREEN_MAIN_H_

#include "screen_context.h"
#include "button.h"


typedef struct {
    State super;

    Button btn_study;
    Button btn_practice;
} State_ScreenMain;


State_ScreenMain state_screen_main(void);


#endif


