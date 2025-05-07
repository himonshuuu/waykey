/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#ifndef DEVICES_H
#define DEVICES_H

#include <linux/input.h>
#include <linux/limits.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define INPUT_DIR "/dev/input"
#define INPUT_EVENT_PREFIX "event"

typedef struct
{
    char path[PATH_MAX];
    char name[256];
    int is_keyboard;
} InputDevice;

int find_keyboard_devices(InputDevice *devices, int max_devices);
void print_device_list(InputDevice *devices, int count);
char *prompt_device_selection(InputDevice *devices, int count);
int is_device_keyboard(const char *path);

#endif // DEVICES_H