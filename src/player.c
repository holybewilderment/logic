// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/player.h>

void PlayerUpdate(PlayerBase *player, float delta) {
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
}