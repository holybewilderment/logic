// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <stdio.h>
#include <unistd.h>
#include <logic/base.h>
#include <logic/player.h>

int main(int argc, char *argv[]) {
   /* int opt;
    int cheight;
    int cwidth;
    bool fullscreen;*/

    // ресайзить нельзя (мне впадлу это делать щас)
    const int wheight = 576;
    const int wwidth = 768;

    InitWindow(wwidth, wheight, "Logic Game");
    PlayerBase player = {0};
    player.position = (Vector2){400, 200};
    player.speed = 0;

    EnvBase env[] = {
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };
    
    int envItemLength = sizeof(env)/sizeof(env[0]);

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){wwidth / 2.0f, wheight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float DeltaTime = GetFrameTime();
        PlayerUpdate(&player, env, envItemLength, DeltaTime);

        BeginDrawing(); 
            ClearBackground(LIGHTGRAY); // TODO: Dark theme?
            BeginMode2D(camera);
                for (int i = 0; i < envItemLength; i++) DrawRectangleRec(env[i].rect, env[i].color);
                Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
                DrawRectangleRec(playerRect, BLACK);
            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}