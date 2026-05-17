// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/base.h>

typedef struct EnvBase {
    Rectangle rect;
    int blocking;
    Color color;
    int type;

    Vector2 startpos;
    Vector2 endpos;
    float speed;
    Vector2 currentpos;
} EnvBase;

