#ifndef _SCREEN_CONTEXT_H_
#define _SCREEN_CONTEXT_H_


#define VIRTUAL_SCREEN_WIDTH 1280
#define VIRTUAL_SCREEN_HEIGHT 720


#define FONT_SIZE 30
#define FONT "assets/fonts/"


#define WINDOW_TITLE "FlashCard"



typedef enum {
    State_ID_ScreenMain
    , State_ID_ScreenFlashCard
} State_ID;


typedef struct State State;


#include <raylib.h>


typedef struct {
    State ** state_stack;
    float frame_time;

    Font font;
} ScreenManager_Context;


ScreenManager_Context flash_card_context(State ** state_stack, Font font);


struct State {
    struct State * (*callback) (struct State*, ScreenManager_Context *);
};


#define STATE_CALLBACK(T) ((State*(*)(State*, ScreenManager_Context*)) (T))


#endif


