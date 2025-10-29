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
    size_t text_length;
    char * text;

    Texture2D texture;
} Card;


static void draw_card(
        Font font, Vector2 position, float width, float height, size_t text_length, char * text, Texture2D texture) {
    const char * subtext = TextSubtext(text, 0, text_length);
    DrawTextBoxed(
        font
        , subtext
        , (Rectangle) {position.x, position.y, width, height/2}
        , FONT_SIZE, 3.0f, true, DARKGRAY);

    if(texture.id != 0) {
        DrawTexturePro(
                texture
                , (Rectangle) {0, 0, texture.width, texture.height}
                , (Rectangle) {position.x, position.y + height/2, width, height/2}
                , (Vector2) {0, 0}
                , 0
                , WHITE);
    }
}


static void draw_review(float x, float y, float width, float height) {
    DrawRectangleRounded(
            (Rectangle) {x, y, width, height}
            , 0.1
            , 16
            , RAYWHITE);
}


#include <stdio.h>


static State * state_screen_review_draw_callback(
        State_ScreenReview * self, ScreenManager_Context * context) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    draw_review((screen_width - 600 ) / 2, 100, 600, 350);
    object_draw(OBJECT(&self->btn_back), ((Vector2) {(screen_width - self->btn_back.size.x) /2, screen_height - 150}));
    self->btn_back.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {screen_width/2-100, screen_height - 150, self->btn_back.size.x, self->btn_back.size.y});

    //TODO: meke stack widget which show only one widget at the time and layout widget for positioning of all widgets
    if(self->review.ID == ReviewID_Question == true) {
        object_draw(OBJECT(&self->btn_show), ((Vector2) {(screen_width - self->btn_show.size.x) /2, 350 + 150}));
        self->btn_show.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - self->btn_show.size.x) / 2, 350 + 150, self->btn_show.size.x, self->btn_show.size.y});

        self->btn_again.hover = false;
        self->btn_hard.hover = false;
        self->btn_good.hover = false;
        self->btn_easy.hover = false;
    } else {
        self->btn_show.hover = false;

        self->btn_again.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) /2, 350 + 150, self->btn_again.size.x, self->btn_again.size.y});
        self->btn_hard.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) / 2 + 170, 350 + 150, self->btn_hard.size.x, self->btn_hard.size.y});
        self->btn_good.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600) / 2 + 340, 350 + 150, self->btn_good.size.x, self->btn_good.size.y});
        self->btn_easy.hover = CheckCollisionPointRec(GetMousePosition(), (Rectangle) {(screen_width - 600)/2 + 500, 350 + 150, self->btn_easy.size.x, self->btn_easy.size.y});

        object_draw(OBJECT(&self->btn_again), ((Vector2) {(screen_width - 600) /2, 350 +150}));
        object_draw(OBJECT(&self->btn_hard), ((Vector2) {(screen_width - 600) / 2 + 166, 350 + 150}));
        object_draw(OBJECT(&self->btn_good), ((Vector2) {(screen_width - 600) / 2 + 333, 350 + 150}));
        object_draw(OBJECT(&self->btn_easy), ((Vector2) {(screen_width - 600)/2 + 498, 350 + 150}));
    }
    
    draw_card(font, (Vector2) {(screen_width - 600 ) / 2, 100}, 600, 350, 11, "Hello World", (Texture2D) {0});

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if(self->btn_again.hover == true || self->btn_hard.hover == true 
                || self->btn_good.hover == true || self->btn_easy.hover == true) {
            self->review.ID = ReviewID_Question;
        } else if(self->btn_show.hover == true) {
            self->review.ID = ReviewID_Answare;
        }
    }

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
        , .btn_show = button(font, "Zobrazit odpověď", (Vector2) {250, 50})
        , .btn_again = button(font, "Znovu", (Vector2) {100, 50})
        , .btn_hard = button(font, "Těžké", (Vector2) {100, 50})
        , .btn_good = button(font, "Dobré", (Vector2) {100, 50})
        , .btn_easy = button(font, "Snadné", (Vector2) {100, 50})
    };
}


