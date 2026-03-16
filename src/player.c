// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/player.h>

void PlayerUpdate(PlayerBase *player, EnvBase *envItems, int envItemLength, float delta) {
    player->ismoving = false;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        player->ismoving = true;
        player->position.x = player->position.x + PLAYER_SPEED * delta;
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        player->ismoving = true;
        player->position.x = player->position.x - PLAYER_SPEED * delta;
    }

    if (IsKeyPressed(KEY_SPACE) && player->canjump) {
        player->speed = -PLAYER_SPEED_JMP;
        player->canjump = false;
    }

    bool hitObstacle = false;
    for (int i = 0; i < envItemLength; i++)
    {
        EnvBase *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y <= p->y + player->speed*delta)
        {
            hitObstacle = true;
            player->speed = 0.0f;
            p->y = ei->rect.y;
            break;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canjump = false;
    }
    else player->canjump = true;
}