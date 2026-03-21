// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

//#include <logic/base.h>
#include <logic/levels.h>

#define G 400
#define PLAYER_SPEED 300.0f
#define PLAYER_SPEED_JMP 280.0f

typedef struct PlayerBase {
    Vector2 position;
    bool onground;
    bool ismoving;
    bool iscolliding;
    bool canjump;
    float speed;
} PlayerBase;

void PlayerUpdate(PlayerBase *player, EnvBase *envItems, int envItemLength, float delta); // движение в целом
