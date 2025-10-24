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

static Font custom_font;

#include "version.h"


int main(void) {
    FlashCard_Version version = flashcard_version();
    char window_title[32];
    snprintf(window_title, 32, "%s v%d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

    SetTraceLogLevel(LOG_NONE);
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


