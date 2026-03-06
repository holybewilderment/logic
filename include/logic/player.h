// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/base.h>

struct PlayerBase {
    float posx;
    float posy;
    int direction;
    bool onground;
    bool ismoving;
    bool iscolliding;
    const float speed = 1.1f;
};

struct PlayerBase Player;

void PlayerSpawn(int x, int y); // спавним игрока на определенных координатах
void PlayerHandleControl(void); // движение в целом
