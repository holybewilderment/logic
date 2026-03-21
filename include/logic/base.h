// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2026, holybewilderment 

#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

static inline void DebuggerBreak() {
    #if defined(_MSC_VER)
    __debugbreak();
    #else
        #if defined(__i386__) || defined(__x86_64__)
            asm("int3");
        #elif defined(__aarch64__)
            asm("brk #0");
        #elif defined(__arm__)
            asm("bkpt #0");
        #else
            #error Ради бога не собирайте этот ужас на квантовом компьютере
        #endif
    #endif 
}