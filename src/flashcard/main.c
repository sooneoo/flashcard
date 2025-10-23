#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>


#define FONT_SIZE 30
#define FONT "assets/fonts/"


#define VIRTUAL_SCREEN_WIDTH 1280
#define VIRTUAL_SCREEN_HEIGHT 720


// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(
        Font font, const char *text, Rectangle rec, float fontSize, float spacing
        , bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint) {
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++) {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) {
            codepointByteCount = 1;
        }

        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        
        if (codepoint != '\n') {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
            if (i + 1 < length) {
                glyphWidth = glyphWidth + spacing;
            }
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container)
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container
        if (state == MEASURE_STATE) {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) {
                endLine = i;
            }

            if ((textOffsetX + glyphWidth) > rec.width) {
                endLine = (endLine < 1)? i : endLine;

                if (i == endLine) {
                    endLine -= codepointByteCount;
                }

                if ((startLine + codepointByteCount) == endLine){
                    endLine = (i - codepointByteCount);
                }

                state = !state;
            } else if ((i + 1) == length) {
                endLine = i;
                state = !state;
            } else if (codepoint == '\n'){
                state = !state;
            }

            if (state == DRAW_STATE) {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        } else {
            if (codepoint == '\n') {
                if (!wordWrap) {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            } else {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width)) {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) {
                    break;
                }

                // Draw selection background
                bool isGlyphSelected = false;
                
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength))) {
                    DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t')) {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine)) {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) {
            textOffsetX += glyphWidth;  // avoid leading spaces
        }
    }
}


// Draw text using font inside rectangle limits
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint) {
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}


typedef enum {
    State_ID_ScreenMain
    , State_ID_ScreenFlashCard
} State_ID;


typedef struct State State;


typedef struct {
    State ** state_stack;
    float frame_time;

    Font font;
} FlashCard_Context;


FlashCard_Context flash_card_context(State ** state_stack, Font font) {
    return (FlashCard_Context) {
        .state_stack = state_stack
        , .font = font
    };
}


struct State {
    struct State * (*callback) (struct State*, FlashCard_Context *);
};


#define STATE_CALLBACK(T) ((State*(*)(State*, FlashCard_Context*)) (T))


typedef struct {
    FlashCard_Context * context;
    State * state;
} FlashCard;


void flash_card_execute(FlashCard * self) {
    self->context->frame_time = GetFrameTime();
    self->state = self->state->callback(self->state, self->context);
}


FlashCard flash_card(State * init_state, FlashCard_Context * context) {
    return (FlashCard) {
        .context = context
        , .state = init_state
    };
}


typedef struct {
    State super;
} State_ScreenMain;


static State * state_screen_main_callback(State_ScreenMain * self, FlashCard_Context * context) {
    DrawTextEx(context->font, "hello world", (Vector2){ 400, 300 }, FONT_SIZE, 4.0f, GRAY);

    DrawTextBoxed(
        context->font
        , "DASDF AS ASDF ASDFASDF AS DFA SDF ASDA FSDF ASF ASDF ASF ASD FA SDFAS DFASDFASD AS DF AS "
        , (Rectangle) {100, 100, 200,200}
        , FONT_SIZE, 4.0f, true, GRAY);
    return context->state_stack[State_ID_ScreenMain];
}


State_ScreenMain state_screen_main(void) {
    return (State_ScreenMain) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_main_callback)
        }   
    };
}


typedef struct {
    State super;
} State_ScreenFlashCard;


static State * state_screen_flash_card_callback(State_ScreenFlashCard * self, FlashCard_Context * context) {
    return context->state_stack[State_ID_ScreenFlashCard];
} 


State_ScreenFlashCard state_screen_flash_card(void) {
    return (State_ScreenFlashCard) {
        .super = {
            .callback = STATE_CALLBACK(state_screen_flash_card_callback)
        }
    };
}


static State_ScreenMain screen_main;
static State_ScreenFlashCard screen_flash_card;

static State * state_mem_buff[] = {
    &screen_main.super
    , &screen_flash_card.super
};

static FlashCard_Context context;
static FlashCard manager;

static Font custom_font;

#include "version.h"

#define WINDOW_TITLE "FlashCard"


int main(void) {
    FlashCard_Version version = flashcard_version();
    char window_title[32];
    snprintf(window_title, 32, "%s v%d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

    InitWindow(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, window_title);
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT);

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();

    custom_font = LoadFontEx(FONT "font.otf", FONT_SIZE, NULL, 0);
    assert(custom_font.texture.id != 0);

    screen_main = state_screen_main();
    screen_flash_card = state_screen_flash_card();

    context = flash_card_context(state_mem_buff, custom_font);
    manager = flash_card(&screen_main.super, &context);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        flash_card_execute(&manager);
        EndDrawing();
    }

    UnloadFont(custom_font);
    CloseWindow();

    return EXIT_SUCCESS;
}


