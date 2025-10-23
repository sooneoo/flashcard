#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>


#define VIRTUAL_SCREEN_WIDTH 1280
#define VIRTUAL_SCREEN_HEIGHT 720

#include "version.h"

#define WINDOW_TITLE "FlashCard"


int main(void) {
    FlashCard_Version version = flashcard_version();
    char window_title[32];
    snprintf(window_title, 32, "%s v%d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

    InitWindow(VIRTUAL_SCREEN_WIDTH, VIRTUAL_SCREEN_HEIGHT, window_title);
    SetTargetFPS(30);
    SetConfigFlags(FLAG_VSYNC_HINT);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}


