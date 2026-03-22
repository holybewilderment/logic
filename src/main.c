// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <unistd.h>
#include <logic/player.h>

int main(int argc, char *argv[]) {
   /* int opt;
    int cheight;
    int cwidth;
    bool fullscreen;*/

    // ресайзить нельзя (мне впадлу это делать щас)
    const int wheight = 576;
    const int wwidth = 768;
    Texture2D txbrick = LoadTexture("resources/kirpich_texture.png");
    Texture2D txplayer = LoadTexture("resource/player_texture.png");

    InitWindow(wwidth, wheight, "Logic Game");
    PlayerBase player = {0};
    player.position = (Vector2){500, 100};
    player.speed = 0;

    EnvBase env[] = {
        {{ 300, 320, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };
    
    int envItemLength = sizeof(env)/sizeof(env[0]);

    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){wwidth / 2.0f, wheight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    while(!WindowShouldClose()) {
        float DeltaTime = GetFrameTime();
        PlayerUpdate(&player, env, envItemLength, DeltaTime);

     //   printf("envItemLength: %i", envItemLength);

        BeginDrawing(); 
            ClearBackground(DARKGRAY);
            DrawText("ESC - Quit", 5, 5, 10, BLACK);
            DrawText(TextFormat("x: %f, y: %f", player.position.x, player.position.y), 10, 15, 10, BLACK);
            DrawText(TextFormat("Time elapsed: %fs", GetTime()), 5, 25, 10, BLACK);
            BeginMode2D(camera);
                for (int i = 0; i < envItemLength; i++) DrawRectangleRec(env[i].rect, env[i].color);
                Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
                DrawTextureRec(txbrick, playerRect, player.position, RAYWHITE);
                //DrawRectangleRec(playerRect, WHITE);
                if (player.position.y >= 1000.0f) {player.position = (Vector2){500, 100};} // помоему это вообще глупо но оно работает поэтому допустим
            EndMode2D();
        EndDrawing();
    }

    printf("[logic] Time elapsed: %f s\n", GetTime());

    CloseWindow();

    return 0;
}