#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>

#include "flashcard/screen_context.h"
#include "flashcard/screen_manager.h"
#include "flashcard/screen_main.h"
#include "flashcard/screen_review.h"


static State_ScreenMain screen_main;
static State_ScreenReview screen_review;

static State * state_mem_buff[] = {
    &screen_main.super
    , &screen_review.super
};

static ScreenManager_Context context;
static ScreenManager manager;

const int CZECH_CUSTOM_CODEPOINTS[] = {
    // ----------------------------------------------------
    // Všechny české znaky s diakritikou (malé i velké)
    // Fungující:
    201, 205, 211, 218, 221, 225, 233, 237, 243, 250, 253, // ÁÉÍÓÚÝáéíóúý
    217, 249, // Ůů
    // Nefungující:
    268, 269, // Čč
    270, 271, // Ďď (pokud je potřeba)
    282, 283, // Ěě
    352, 353, // Šš <--- Tyto jsou klíčové
    344, 345, // Řř <--- Tyto jsou klíčové
    381, 382, // Žž <--- Tyto jsou klíčové
    366, // Ů
    367  // ů
    // ----------------------------------------------------
    // Přidáme další potřebné znaky jako tečky, čárky atd.
};

#define NUM_CZECH_CODEPOINTS (sizeof(CZECH_CUSTOM_CODEPOINTS) / sizeof(CZECH_CUSTOM_CODEPOINTS[0]))
int codepoints[95 + NUM_CZECH_CODEPOINTS];


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

// 1. Zjistíme, kolik znaků chceme načíst (základní ASCII 95 + naše custom)
    const int ASCII_COUNT = 95; 
    
    // 2. Naplníme ho základním ASCII (32 až 126)
    for (size_t i = 0; i < ASCII_COUNT; i++) {
        codepoints[i] = 32 + i;
    }
    
    // 3. Přidáme custom české znaky
    for (size_t i = 0; i < NUM_CZECH_CODEPOINTS; i++) {
        codepoints[ASCII_COUNT + i] = CZECH_CUSTOM_CODEPOINTS[i];
    }

    font = LoadFontEx(FONT "font.ttf", FONT_SIZE, codepoints, NUM_CZECH_CODEPOINTS + 95);
    
    font_bold = LoadFontEx(FONT "font_bold.ttf", FONT_BOLD_SIZE, codepoints, NUM_CZECH_CODEPOINTS +95);

    screen_main = state_screen_main();
    screen_review = state_screen_review();

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


