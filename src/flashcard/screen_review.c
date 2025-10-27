#include "flashcard/screen_review.h"
#include "flashcard/text.h"

/*
 *
    DrawTextBoxed(
        context->font
        , "DASDF AS ASDF ASDFASDF AS DFA SDF ASDA FSDF ASF ASDF ASF ASD FA SDFAS DFASDFASD AS DF AS "
        , (Rectangle) {100, 100, 200,200}
        , FONT_SIZE, 4.0f, true, GRAY);
 *
 */

#include <stddef.h>

typedef struct {
    size_t question_length;
    char * question;

    size_t answare_length;
    char * answare;
} Card;


static void draw_card(Font font, float x, float y, float width, float height, Card card) {
    char * question = TextSubtext(card.question, 0, card.question_length);

    DrawTextBoxed(
        font
        , question
        , (Rectangle) {x+20, y+20, width-40, height/2 - 20}
        , FONT_SIZE, 3.0f, true, DARKGRAY);

    char * answare = TextSubtext(card.answare, 0, card.answare_length);

    DrawTextBoxed(
        font
        , answare
        , (Rectangle) {x+20, y+40 + height / 2, width-40, height/2-40}
        , FONT_SIZE, 3.0f, true, DARKGRAY);
}


static void draw_review(float x, float y, float width, float height) {
    DrawRectangleRounded(
            (Rectangle) {x, y, width, height}
            , 0.1
            , 16
            , RAYWHITE);
}

static State * state_screen_review_draw_callback(
        State_ScreenReview * self, ScreenManager_Context * context) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    draw_review((screen_width - 600 ) / 2, 100, 600, 350);
    object_draw(OBJECT(&self->btn_back), ((Vector2) {(screen_width - self->btn_back.size.x) /2, screen_height - 150}));
    
    object_draw(OBJECT(&self->btn_again), ((Vector2) {(screen_width - 600) /2, 350 +150}));
    object_draw(OBJECT(&self->btn_hard), ((Vector2) {(screen_width - 600) / 2 + 166, 350 + 150}));
    object_draw(OBJECT(&self->btn_good), ((Vector2) {(screen_width - 600) / 2 + 333, 350 + 150}));
    object_draw(OBJECT(&self->btn_easy), ((Vector2) {(screen_width - 600)/2 + 498, 350 + 150}));

    self->btn_back.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {screen_width/2-100, screen_height - 150, self->btn_back.size.x, self->btn_back.size.y});
    self->btn_again.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) /2, 350 + 150, self->btn_again.size.x, self->btn_again.size.y});
    self->btn_hard.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) / 2 + 170, 350 + 150, self->btn_hard.size.x, self->btn_hard.size.y});
    self->btn_good.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) / 2 + 340, 350 + 150, self->btn_good.size.x, self->btn_good.size.y});
    self->btn_easy.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600)/2 + 500, 350 + 150, self->btn_easy.size.x, self->btn_easy.size.y});

    draw_card(font, (screen_width - 600 ) / 2, 100, 600, 350, (Card) {.question_length = 11, .question = "Hello World", .answare_length = 3, .answare = "yes"});


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
            && self->btn_back.hover == true) {
        return context->state_stack[State_ID_ScreenMain];
    } else {
        return context->state_stack[State_ID_ScreenFlashCard];
    }
} 


State_ScreenReview state_screen_review(void) {
    return (State_ScreenReview) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_review_draw_callback)
        }
        , .btn_back = button(font, "Hlavní Obrazovka", (Vector2) {250, 50})
        , .btn_again = button(font, "Znovu", (Vector2) {100, 50})
        , .btn_hard = button(font, "Těžké", (Vector2) {100, 50})
        , .btn_good = button(font, "Dobré", (Vector2) {100, 50})
        , .btn_easy = button(font, "Snadné", (Vector2) {100, 50})
    };
}


