// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/base.h>

struct Player {
    int ypos;
    int xpos;
    bool onground;
};


void PlayerSpawn(int x, int y); // спавним игрока на определенных координатах

void PlayerJump(); // там короче прыжок такой оп
void PlayerMoveRight(); // тут мы вправо едем (консервы)
void PlayerMoveLeft(); // тут влево (комуняги)

