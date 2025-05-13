/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#define CONFIG_FILE_NAME "config.yml"
#define CONFIG_DIR_NAME ".config/waykey"

typedef struct {
    char *device_path;
    char *pipe_path;
    char *state_path;
} Config;

Config *load_config(void);
void free_config(Config *config);
char *get_config_path(void);

#endif // CONFIG_H 