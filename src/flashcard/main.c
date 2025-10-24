#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>

#include "flashcard/screen_context.h"
#include "flashcard/screen_manager.h"
#include "flashcard/screen_main.h"
#include "flashcard/screen_flashcard.h"


static State_ScreenMain screen_main;
static State_ScreenFlashCard screen_flash_card;

static State * state_mem_buff[] = {
    &screen_main.super
    , &screen_flash_card.super
};

static ScreenManager_Context context;
static ScreenManager manager;


#define NUM_CHARS 256
int codepoints[NUM_CHARS] = { 0 };


#include "version.h"


int main(void) {
    FlashCard_Version version = flashcard_version();
    char window_title[32];
    snprintf(window_title, 32, "%s v%d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

    SetTraceLogLevel(LOG_NONE);
    InitWindow(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, window_title);
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT);

    SetWindowMinSize(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();

    for (int i = 0; i < 256; i++) {
        codepoints[i] = 32 + i;
    }

    font = LoadFontEx(FONT "font.ttf", FONT_SIZE, codepoints, NUM_CHARS);
    font_bold = LoadFontEx(FONT "font_bold.ttf", FONT_BOLD_SIZE, codepoints, NUM_CHARS);

    screen_main = state_screen_main();
    screen_flash_card = state_screen_flash_card();

    context = flash_card_context(state_mem_buff);
    manager = flash_card(&screen_main.super, &context);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(GRAY);
        flash_card_execute(&manager);
        EndDrawing();
    }

    UnloadFont(font);
    UnloadFont(font_bold);
    CloseWindow();

    return EXIT_SUCCESS;
}


