// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

//#include <logic/base.h>
#include <logic/levels.h>

#define G 600
#define PLAYER_SPEED 300.0f
#define PLAYER_SPEED_JMP 400.0f
#define PLAYER_SPEED_JUMP_PAD 550.0f

typedef struct PlayerBase {
    Vector2 position;
    bool onground;
    bool ismoving;
    bool canjump;
    float speed;
    int isdead;
    int iscompleted;
} PlayerBase;

void PlayerUpdate(PlayerBase *player, EnvBase *envItems, int envItemLength, float delta); // движение в целом