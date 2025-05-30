/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#include "../include/keymap.h"

const char *key_names[MAX_KEYS] = {0};

void init_key_names(void)
{
    key_names[KEY_LEFTMETA] = "super";
    key_names[KEY_RIGHTMETA] = "super";

    key_names[KEY_ESC] = "esc";
    key_names[KEY_1] = "1";
    key_names[KEY_2] = "2";
    key_names[KEY_3] = "3";
    key_names[KEY_4] = "4";
    key_names[KEY_5] = "5";
    key_names[KEY_6] = "6";
    key_names[KEY_7] = "7";
    key_names[KEY_8] = "8";
    key_names[KEY_9] = "9";
    key_names[KEY_0] = "0";
    key_names[KEY_MINUS] = "minus";
    key_names[KEY_EQUAL] = "equal";
    key_names[KEY_BACKSPACE] = "backspace";
    key_names[KEY_TAB] = "tab";
    key_names[KEY_Q] = "q";
    key_names[KEY_W] = "w";
    key_names[KEY_E] = "e";
    key_names[KEY_R] = "r";
    key_names[KEY_T] = "t";
    key_names[KEY_Y] = "y";
    key_names[KEY_U] = "u";
    key_names[KEY_I] = "i";
    key_names[KEY_O] = "o";
    key_names[KEY_P] = "p";
    key_names[KEY_LEFTBRACE] = "leftbrace";
    key_names[KEY_RIGHTBRACE] = "rightbrace";
    key_names[KEY_ENTER] = "enter";
    key_names[KEY_LEFTCTRL] = "ctrl";
    key_names[KEY_RIGHTCTRL] = "ctrl";
    key_names[KEY_A] = "a";
    key_names[KEY_S] = "s";
    key_names[KEY_D] = "d";
    key_names[KEY_F] = "f";
    key_names[KEY_G] = "g";
    key_names[KEY_H] = "h";
    key_names[KEY_J] = "j";
    key_names[KEY_K] = "k";
    key_names[KEY_L] = "l";
    key_names[KEY_SEMICOLON] = "semicolon";
    key_names[KEY_APOSTROPHE] = "apostrophe";
    key_names[KEY_GRAVE] = "grave";
    key_names[KEY_LEFTSHIFT] = "shift";
    key_names[KEY_RIGHTSHIFT] = "shift";
    key_names[KEY_BACKSLASH] = "backslash";
    key_names[KEY_Z] = "z";
    key_names[KEY_X] = "x";
    key_names[KEY_C] = "c";
    key_names[KEY_V] = "v";
    key_names[KEY_B] = "b";
    key_names[KEY_N] = "n";
    key_names[KEY_M] = "m";
    key_names[KEY_COMMA] = "comma";
    key_names[KEY_DOT] = "dot";
    key_names[KEY_SLASH] = "slash";
    key_names[KEY_KPASTERISK] = "kpasterisk";
    key_names[KEY_LEFTALT] = "alt";
    key_names[KEY_RIGHTALT] = "alt";
    key_names[KEY_SPACE] = "space";
    key_names[KEY_CAPSLOCK] = "capslock";
    key_names[KEY_F1] = "f1";
    key_names[KEY_F2] = "f2";
    key_names[KEY_F3] = "f3";
    key_names[KEY_F4] = "f4";
    key_names[KEY_F5] = "f5";
    key_names[KEY_F6] = "f6";
    key_names[KEY_F7] = "f7";
    key_names[KEY_F8] = "f8";
    key_names[KEY_F9] = "f9";
    key_names[KEY_F10] = "f10";
    key_names[KEY_F11] = "f11";
    key_names[KEY_F12] = "f12";
    key_names[KEY_NUMLOCK] = "numlock";
    key_names[KEY_SCROLLLOCK] = "scrolllock";
    key_names[KEY_KP7] = "kp7";
    key_names[KEY_KP8] = "kp8";
    key_names[KEY_KP9] = "kp9";
    key_names[KEY_KPMINUS] = "kpminus";
    key_names[KEY_KP4] = "kp4";
    key_names[KEY_KP5] = "kp5";
    key_names[KEY_KP6] = "kp6";
    key_names[KEY_KPPLUS] = "kpplus";
    key_names[KEY_KP1] = "kp1";
    key_names[KEY_KP2] = "kp2";
    key_names[KEY_KP3] = "kp3";
    key_names[KEY_KP0] = "kp0";
    key_names[KEY_KPDOT] = "kpdot";
    key_names[KEY_KPENTER] = "kpenter";
    key_names[KEY_HOME] = "home";
    key_names[KEY_UP] = "up";
    key_names[KEY_PAGEUP] = "pageup";
    key_names[KEY_LEFT] = "left";
    key_names[KEY_RIGHT] = "right";
    key_names[KEY_END] = "end";
    key_names[KEY_DOWN] = "down";
    key_names[KEY_PAGEDOWN] = "pagedown";
    key_names[KEY_INSERT] = "insert";
    key_names[KEY_DELETE] = "delete";
    key_names[KEY_MUTE] = "mute";
    key_names[KEY_VOLUMEDOWN] = "volumedown";
    key_names[KEY_VOLUMEUP] = "volumeup";
    key_names[KEY_POWER] = "power";
    key_names[KEY_PAUSE] = "pause";
    key_names[KEY_PRINT] = "print";
    key_names[KEY_SYSRQ] = "sysrq";
    key_names[KEY_MENU] = "menu";
    key_names[KEY_PROPS] = "props";
    key_names[KEY_FRONT] = "front";
    key_names[KEY_STOP] = "stop";
    key_names[KEY_COPY] = "copy";
    key_names[KEY_OPEN] = "open";
    key_names[KEY_FIND] = "find";
    key_names[KEY_CUT] = "cut";
    key_names[KEY_HELP] = "help";
}
