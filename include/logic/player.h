// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/base.h>

#define G 2
#define PLAYER_SPEED 1.1f
#define PLAYER_SPEED_JMP 1.925f

typedef struct PlayerBase {
    Vector2 position;
    bool onground;
    bool ismoving;
    bool iscolliding;
    bool canjump;
    float speed;
} PlayerBase;

typedef struct EnvBase {
    Rectangle rect;
    int blocking;
    Color color;
} EnvBase;

void PlayerUpdate(PlayerBase *player, float delta); // движение в целом
