/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#ifndef KEYSTATE_TYPES_H
#define KEYSTATE_TYPES_H

/* common definition of KeyState*/
#define MAX_KEYS 256

typedef struct
{
    char name[32];
    char state[16];
} KeyState;

#endif // KEYSTATE_TYPES_H