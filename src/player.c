// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/player.h>

void PlayerSpawn(int x, int y) {
    DrawRectangle(x, y, 20, 20, BLACK);
}

void PlayerJump() {
    // игрок поднимается на определенные координаты, и потом падает
    if(Player.onground) 
        return;


}

void PlayerHandleControl() {
    Player.ismoving = false;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        Player.ismoving = true;
        Player.direction = 1;
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        Player.ismoving = true;
        Player.direction = -1;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        PlayerJump();
    }
}