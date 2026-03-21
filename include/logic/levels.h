// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <logic/base.h>

#define LEVEL_COUNT 4

typedef enum {
    LEVEL_UNKNOWN = 0,
    LEVEL_ONE = 1,
    LEVEL_TWO = 2,
    LEVEL_THREE = 3,
    LEVEL_FOUR = 4
} GameLevel;

typedef enum {
    LEVEL_UNFINISHED = 0,
    LEVEL_FINISHED = 1
} LevelState;

typedef struct EnvBase {
    Rectangle rect;
    int blocking;
    Color color;
} EnvBase;

GameLevel LevelUpdate(int level);
bool LevelFinished();