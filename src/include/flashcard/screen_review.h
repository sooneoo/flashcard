#ifndef _SCREEN_FLASHCARD_H_
#define _SCREEN_FLASHCARD_H_


#include "screen_context.h"
#include "button.h"


typedef struct {
    State super;

    Button btn_again;
    Button btn_hard;
    Button btn_good;
    Button btn_easy;

    Button btn_back;
} State_ScreenReview;


State_ScreenReview state_screen_review(void);


#endif


