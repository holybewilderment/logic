// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <stdio.h>
#include <logic/base.h>
#include <logic/player.h>

int main() {
    // ресайзить нельзя (мне впадлу это делать щас)
    const int sheight = 576;
    const int swidth = 768;

    InitWindow(swidth, sheight, "Logic Game");
    PlayerBase player = {0};
    player.position = (Vector2){400, 200};
    player.speed = 0;

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){swidth / 2.0f, sheight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float DeltaTime = GetFrameTime();
        PlayerUpdate(&player, DeltaTime);

        BeginDrawing(); 
            ClearBackground(LIGHTGRAY); // TODO: Dark theme?
            BeginMode2D(camera);
                Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
                DrawRectangleRec(playerRect, BLACK);
            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}