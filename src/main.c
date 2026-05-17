// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/player.h>
#include <tinyfiledialogs.h>

void RespawnPlayer(PlayerBase *player, Vector2 pos) {
    player->position = pos;
    player->speed = 0;
    player->isdead = false;
}


int main(int argc, char *argv[]) {
   /* int opt;
    int cheight;
    int cwidth;
    bool fullscreen;*/

    // ресайзить нельзя (мне впадлу это делать щас)
    const int wwidth = 800;
    const int wheight = 600;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(wwidth, wheight, "Logic Game");
    PlayerBase player = {0};
    Vector2 pos1 = (Vector2){-269, 563};
    player.position = pos1;
    player.iscompleted = false;

    EnvBase lvl1[] = {
        {{ 370, 85, 40, 40 }, 0, WHITE, 1, {0}, {0}, 0, {0} }, 
        {{ -575, 570, 700, 30 }, 1, BLACK, 0, {0}, {0}, 0, {0} },
        {{ 150, 570, 100, 20 }, 1, BLUE, 3, {150, 570}, {350, 570}, 0.5f, {150, 570}},
        {{ 380, 490, 80, 20 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ 480, 490, 80, 20 }, 1, BLUE, 3, {480, 490}, {480, 380}, 0.6f, {480, 490}},
        {{ 701, 380, 100, 30 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ 820, 380, 100, 20 }, 1, BLUE, 3, {820, 380}, {980, 300}, 0.5f, {820, 380}},
        {{ 1000, 300, 80, 20}, 1, ORANGE, 2, {0}, {0}, 0, {0}},

        {{ 950, 100, 150, 30 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ 800, 100, 120, 20 }, 1, BLUE, 3, {800, 100}, {500, 100}, 0.5f, {800, 100}}, 
        {{ 300, 100, 180, 30 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ 370, 60, 40, 40 }, 0, GRAY, 1, {0}, {0}, 0, {0} },   
        {{ 150, 100, 100, 20 }, 1, BLUE, 3, {150, 100}, {0, 100}, 0.6f, {150, 100}}, 
        {{ -150, 100, 100, 20 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ -140, 80, 80, 20 }, 1, ORANGE, 2, {0}, {0}, 0, {0} },

        {{ -250, -39, 150, 30 }, 1, BLACK, 0, {0}, {0}, 0, {0} }, 
        {{ -200, -89, 30, 50 }, 0, GOLD, 4, {0}, {0}, 0, {0} } 
    };

    // {x, y, width, height}, blocking (коллизия), color

    Camera2D camera = {0};
    camera.target = (Vector2){500, 100};
    camera.offset = (Vector2){wwidth / 2.0f, wheight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    Texture2D txbrick = LoadTexture("resources/kirpich_texture.png");
    Texture2D txplayer = LoadTexture("resources/player_texture.png");
    Texture2D txforeground = LoadTexture("resources/foreground.png");
    Texture2D txsaw = LoadTexture("resources/saw_texture.png");

    float frgscroll = 0.0f;
    float sawspin = 0.0f;
    int envItemLength = 0;

    while(!WindowShouldClose()) {
        envItemLength = sizeof(lvl1) / sizeof(lvl1[0]);

        float DeltaTime = GetFrameTime();

        sawspin += 150.0f * DeltaTime;

        for (int i = 0; i < envItemLength; i++) {
            if (lvl1[i].type == 3) {
                float timefactor = GetTime() * lvl1[i].speed;
                float pingpong = fabsf(fmodf(timefactor, 2.0f) - 1.0f);
                
                Vector2 newPos = Vector2Lerp(lvl1[i].startpos, lvl1[i].endpos, pingpong);
                
                lvl1[i].currentpos = newPos;
                lvl1[i].rect.x = newPos.x;
                lvl1[i].rect.y = newPos.y;
            }
        }
        
        PlayerUpdate(&player, lvl1, envItemLength, DeltaTime);

        if (player.position.y >= 1000.0f || player.position.x <= -900.0f || IsKeyPressed(KEY_R) || player.isdead) { 
            RespawnPlayer(&player, pos1);
        }

        if (IsKeyPressed(KEY_P)) {
            TakeScreenshot("logic_screenshot.png");
        }

        frgscroll -= 1.0f;
        if (frgscroll <= -txforeground.width*2) frgscroll = 0;

        BeginDrawing(); 
            ClearBackground(RAYWHITE);

            DrawTextureEx(txforeground, (Vector2){frgscroll, -(txforeground.height - wheight + 50)}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(txforeground, (Vector2){txforeground.width * 2 + frgscroll, -(txforeground.height - wheight + 50)}, 0.0f, 2.0f, WHITE);

            DrawText("ESC - Quit", 5, 5, 10, BLACK);
            DrawText(TextFormat("x: %.2f, y: %.2f", player.position.x, player.position.y), 5, 15, 10, BLACK);
            DrawText(TextFormat("Time elapsed: %.3fs", GetTime()), 5, 25, 10, BLACK);
            DrawText(TextFormat("FPS: %i", GetFPS()), 5, 35, 10, BLACK);

            BeginMode2D(camera);
                for (int i = 0; i < envItemLength; i++) {
                    if (lvl1[i].type == 1) { // пила
                        // крутится...
                        Rectangle source = {0, 0, (float)txsaw.width, (float)txsaw.height};
                        Rectangle dest = {lvl1[i].rect.x + lvl1[i].rect.width / 2.0f, lvl1[i].rect.y + lvl1[i].rect.height / 2.0f, lvl1[i].rect.width, lvl1[i].rect.height};
                        Vector2 origin = {lvl1[i].rect.width / 2.0f, lvl1[i].rect.height / 2.0f};
                        DrawTexturePro(txsaw, source, dest, origin, sawspin, WHITE);
                    } 
                    else if (lvl1[i].type == 2) { // джампад
                        DrawRectangleRec(lvl1[i].rect, lvl1[i].color);
                    } 
                    else { // наша обычная платформа
                        DrawRectangleRec(lvl1[i].rect, lvl1[i].color);
                    }
                }
                DrawTextureRec(txplayer, (Rectangle){0, 0, 40.0f, 40.0f}, (Vector2){player.position.x - 20, player.position.y - 40}, RAYWHITE);
                if(player.iscompleted == true) {
                    tinyfd_messageBox("Logic Game", "Game completed!", "ok", "info", 1);
                    UnloadTexture(txbrick);
                    UnloadTexture(txforeground);
                    UnloadTexture(txplayer);
                    UnloadTexture(txsaw);
                    printf("LOGIC: Game completed\n");
                    printf("LOGIC: Time elapsed: %f s\n", GetTime());

                    CloseWindow();
                    return 0;
                }
            EndMode2D();
        EndDrawing();
    }

    UnloadTexture(txbrick);
    UnloadTexture(txforeground);
    UnloadTexture(txplayer);
    UnloadTexture(txsaw);
    printf("LOGIC: Game uncompleted\n");
    printf("LOGIC: Time elapsed: %f s\n", GetTime());

    CloseWindow();

    return 0;
}
