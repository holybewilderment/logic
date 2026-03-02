// Copyright holybewilderment, 2026, All rights reserved 
#include <stdio.h>
#include <raylib/raylib.h>

int main() {
    const int height = 576;
    const int width = 768;

    InitWindow(width, height, "Logic Game");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE); // TODO: Dark theme?
        DrawText("tigra tigra tigra tig", 6, 6, 20, BLACK);
        EndDrawing();
    }

    return 0;
}