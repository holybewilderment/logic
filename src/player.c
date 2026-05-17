// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/player.h>
#include <raylib/raymath.h>

void PlayerUpdate(PlayerBase *player, EnvBase *envItems, int envItemLength, float delta) {

    player->ismoving = false;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {}
        else {
            player->ismoving = true;
            player->position.x = player->position.x + PLAYER_SPEED * delta; 
        }
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {}
        else {
            player->ismoving = true;
            player->position.x = player->position.x - PLAYER_SPEED * delta;
        }
    }

    if ( (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && player->canjump) {
        player->speed = -PLAYER_SPEED_JMP;
        player->canjump = false;
    }

    bool hitObstacle = false;
    Vector2 displacement = {0.0f, 0.0f};

    Rectangle playerRect = { player->position.x - 20, player->position.y - 40, 40.0f, 40.0f };

    for (int i = 0; i < envItemLength; i++)
    {
        EnvBase *ei = envItems + i;
        Vector2 *p = &(player->position);

        // 1 - летальное
        if (ei->type == 1) {
            if (CheckCollisionRecs(playerRect, ei->rect)) {
                player->isdead = true;
                break;
            }
        }

        // 4 - ключ
        if (ei->type == 4) {
            if (CheckCollisionRecs(playerRect, ei->rect)) {
                player->iscompleted = true;
                break;
            }
        }
        
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y <= p->y + player->speed*delta)
        {
            // 2 - батут
            if (ei->type == 2) {
                player->speed = -PLAYER_SPEED_JUMP_PAD;
                hitObstacle = false;
            }
            else {
                hitObstacle = true;
                player->speed = 0.0f;
                p->y = ei->rect.y;

                // 3 - двигающаяся платформа
                if(ei->type == 3) {
                    float nexttime = GetTime() * ei->speed;
                    float pingpong = fabsf(fmodf(nexttime, 2.0f) - 1.0f);

                    Vector2 targetpos = Vector2Lerp(ei->startpos, ei->endpos, pingpong);
                    displacement.x = targetpos.x - ei->currentpos.x;
                    displacement.y = targetpos.y - ei->currentpos.y;
                    if(CheckCollisionRecs(playerRect, ei->rect)){
                        player->position.x = displacement.x;
                    }
                }
            }
            break;
        }
    }

    if (!hitObstacle) {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canjump = false;
    }
    else { 
        player->canjump = true;
        player->position.x += displacement.x;
        player->position.y += displacement.y;
    }
}