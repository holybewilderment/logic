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
    const int wheight = 600;
    const int wwidth = 800;

    InitWindow(wwidth, wheight, "Logic Game");
    PlayerBase player = {0};
    player.position = (Vector2){5, 10};
    player.speed = 0;

    // {x, y, width, height}, blocking (коллизия), color
    EnvBase env[] = {
        {{ 20, 10, 400, 10 }, 1, BLACK },
        {{ 50, 240, 100, 10 }, 1, BLACK },
        {{ 650, 300, 100, 10 }, 1, BLACK }
    };
    
    int envItemLength = sizeof(env)/sizeof(env[0]);

    Camera2D camera = {0};
    camera.target = (Vector2){500, 100};
    camera.offset = (Vector2){wwidth / 2.0f, wheight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;


    Texture2D txbrick = LoadTexture("resources/kirpich_texture.png");
    Texture2D txplayer = LoadTexture("resources/player_texture.png");
    Texture2D txforeground = LoadTexture("resources/foreground.png");

    float frgscroll = 0.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        float DeltaTime = GetFrameTime();
        PlayerUpdate(&player, env, envItemLength, DeltaTime);

        if (IsKeyPressed(KEY_P)) {
            TakeScreenshot("logic_screenshot.png");
        }

        frgscroll = frgscroll - 0.4f;
        if (frgscroll <= -txforeground.width*2) frgscroll = 0;

     //   printf("envItemLength: %i", envItemLength);

        BeginDrawing(); 
            ClearBackground(RAYWHITE);

           // DrawTextureEx(txforeground, (Vector2){frgscroll, 0}, 0.0f, 1.5f, WHITE);
           // DrawTextureEx(txforeground, (Vector2){txforeground.width * 2 + frgscroll, 0}, 0.0f, 1.5f, WHITE);

            DrawTextureEx(txforeground, (Vector2){frgscroll, -(txforeground.height - wheight + 20)}, 0.0f, 1.5f, WHITE);
            DrawTextureEx(txforeground, (Vector2){txforeground.width * 2 + frgscroll, -(txforeground.height - wheight + 20)}, 0.0f, 1.5f, WHITE);

            DrawText("ESC - Quit", 5, 5, 10, BLACK);
            DrawText(TextFormat("x: %.2f, y: %.2f", player.position.x, player.position.y), 5, 15, 10, BLACK);
            DrawText(TextFormat("Time elapsed: %.3fs", GetTime()), 5, 25, 10, BLACK);
            DrawText(TextFormat("FPS: %i", GetFPS()), 5, 35, 10, BLACK);

            BeginMode2D(camera);
                for (int i = 0; i < envItemLength; i++) DrawRectangleRec(env[i].rect, env[i].color);
               // Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
                DrawTextureRec(txplayer, (Rectangle){0, 0, 40.0f, 40.0f}, (Vector2){player.position.x - 20, player.position.y - 40}, RAYWHITE);
               // DrawRectangleRec(playerRect, WHITE);
                if (player.position.y >= 1000.0f) {player.position = (Vector2){46, 10};} // помоему это вообще глупо но оно работает поэтому допустим
            EndMode2D();

        EndDrawing();
    }

    UnloadTexture(txbrick);
    UnloadTexture(txforeground);
    UnloadTexture(txplayer);
    printf("[logic] Time elapsed: %f s\n", GetTime());

    CloseWindow();

    return 0;
}