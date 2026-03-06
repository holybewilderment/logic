// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <stdio.h>
#include <logic/base.h>
#include <logic/player.h>

int main() {
    // ресайзить нельзя (мне впадлу это делать щас)
    const int height = 576;
    const int width = 768;

    InitWindow(width, height, "Logic Game");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE); // TODO: Dark theme?
        PlayerSpawn(56, 68);

        EndDrawing();
    }

    return 0;
}