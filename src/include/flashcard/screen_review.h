#ifndef _SCREEN_FLASHCARD_H_
#define _SCREEN_FLASHCARD_H_


#include "screen_context.h"
#include "button.h"

typedef enum {
    ReviewID_Question
    , ReviewID_Answare
} ReviewID;


typedef struct {
    ReviewID ID;
    
    const char * text;
    Texture2D card_texture; 
} Review;


typedef struct {
    State super;

    Review review;

    Button btn_show;
    Button btn_again;
    Button btn_hard;
    Button btn_good;
    Button btn_easy;

    Button btn_back;
} State_ScreenReview;


State_ScreenReview state_screen_review(void);


#endif


