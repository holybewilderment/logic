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

void PlayerMoveRight() {
    // игрок идет вправо (вау)
}

void PlayerMoveLeft() {
    // игрок идет влево (ноу вей)
}