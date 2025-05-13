/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */

#include "../include/config.h"

char *get_config_path(void) {
    const char *home = getenv("HOME");
    if (!home) {
        struct passwd *pw = getpwuid(getuid());
        if (!pw) return NULL;
        home = pw->pw_dir;
    }

    static char config_path[256];
    snprintf(config_path, sizeof(config_path), "%s/%s/%s", home, CONFIG_DIR_NAME, CONFIG_FILE_NAME);
    return config_path;
}

Config *load_config(void) {
    Config *config = calloc(1, sizeof(Config));
    if (!config) return NULL;

    char *config_path = get_config_path();
    if (!config_path) {
        free(config);
        return NULL;
    }

    FILE *file = fopen(config_path, "r");
    if (!file) {
        free(config);
        return NULL;
    }

    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    char *current_key = NULL;
    char *current_value = NULL;

    if (!yaml_parser_initialize(&parser)) {
        fclose(file);
        free(config);
        return NULL;
    }

    yaml_parser_set_input_file(&parser, file);

    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            break;
        }

        switch (event.type) {
            case YAML_SCALAR_EVENT:
                if (!current_key) {
                    current_key = strdup((char *)event.data.scalar.value);
                } else {
                    current_value = strdup((char *)event.data.scalar.value);
                    
                    if (strcmp(current_key, "device_path") == 0) {
                        config->device_path = strdup(current_value);
                    } else if (strcmp(current_key, "pipe_path") == 0) {
                        config->pipe_path = strdup(current_value);
                    } else if (strcmp(current_key, "state_path") == 0) {
                        config->state_path = strdup(current_value);
                    }
                    
                    free(current_key);
                    free(current_value);
                    current_key = NULL;
                    current_value = NULL;
                }
                break;

            case YAML_STREAM_END_EVENT:
                done = 1;
                break;

            default:
                break;
        }

        yaml_event_delete(&event);
    }

    yaml_parser_delete(&parser);
    fclose(file);

    return config;
}

void free_config(Config *config) {
    if (!config) return;
    
    free(config->device_path);
    free(config->pipe_path);
    free(config->state_path);
    free(config);
} 