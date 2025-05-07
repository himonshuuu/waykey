/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#include "../include/keystate.h"

void init_key_states(KeyState *key_states)
{
    memset(key_states, 0, sizeof(KeyState) * MAX_KEYS);
}

void update_state_file(const char *state_path, KeyState *key_states, pthread_mutex_t *state_mutex)
{
    json_object *root = json_object_new_object();
    json_object *keys_array = json_object_new_array();

    pthread_mutex_lock(state_mutex);

    for (int i = 0; i < MAX_KEYS; i++)
    {
        if (key_states[i].name[0] != '\0')
        {
            json_object *key_obj = json_object_new_object();

            json_object_object_add(key_obj, "name", json_object_new_string(key_states[i].name));
            json_object_object_add(key_obj, "state", json_object_new_string(key_states[i].state));

            json_object_array_add(keys_array, key_obj);
        }
    }

    pthread_mutex_unlock(state_mutex);

    json_object_object_add(root, "keys", keys_array);

    const char *json_str = json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);

    FILE *file = fopen(state_path, "w");
    if (file)
    {
        fprintf(file, "%s\n", json_str);
        fclose(file);
    }
    else
    {
        fprintf(stderr, "Error writing to state file: %s\n", strerror(errno));
    }

    json_object_put(root);
}

void send_pipe_update(int pipe_fd, KeyState *key_states, pthread_mutex_t *state_mutex)
{
    static struct timespec last_retry = {0, 0};
    struct timespec now;

    if (pipe_fd < 0)
    {
        clock_gettime(CLOCK_MONOTONIC, &now);
        if (last_retry.tv_sec == 0 ||
            (now.tv_sec - last_retry.tv_sec) > 5)
        {

            last_retry = now;
            return;
        }
        return;
    }

    json_object *root = json_object_new_object();
    json_object *keys_array = json_object_new_array();

    pthread_mutex_lock(state_mutex);

    for (int i = 0; i < MAX_KEYS; i++)
    {
        if (key_states[i].name[0] != '\0')
        {
            json_object *key_obj = json_object_new_object();

            json_object_object_add(key_obj, "name", json_object_new_string(key_states[i].name));
            json_object_object_add(key_obj, "state", json_object_new_string(key_states[i].state));

            json_object_array_add(keys_array, key_obj);
        }
    }

    pthread_mutex_unlock(state_mutex);

    json_object_object_add(root, "keys", keys_array);

    const char *json_str = json_object_to_json_string(root);

    size_t len = strlen(json_str);
    ssize_t written = write(pipe_fd, json_str, len);
    if (written != (ssize_t)len)
    {
        fprintf(stderr, "Error writing to pipe: %s\n", strerror(errno));
    }

    if (write(pipe_fd, "\n", 1) != 1)
    {
        fprintf(stderr, "Error writing to pipe: %s\n", strerror(errno));
    }

    json_object_put(root);
}

void update_key_state(KeyState *key_states, uint32_t key, uint32_t state, pthread_mutex_t *state_mutex)
{
    pthread_mutex_lock(state_mutex);

    if (key < MAX_KEYS)
    {
        if (key_names[key] != NULL)
        {
            strncpy(key_states[key].name, key_names[key], sizeof(key_states[key].name) - 1);
            key_states[key].name[sizeof(key_states[key].name) - 1] = '\0';

            if (state == LIBINPUT_KEY_STATE_PRESSED)
            {
                strncpy(key_states[key].state, "pressed", sizeof(key_states[key].state) - 1);
            }
            else
            {
                strncpy(key_states[key].state, "released", sizeof(key_states[key].state) - 1);
            }
            key_states[key].state[sizeof(key_states[key].state) - 1] = '\0';
        }
        else
        {
            snprintf(key_states[key].name, sizeof(key_states[key].name), "key%d", key);
            key_states[key].name[sizeof(key_states[key].name) - 1] = '\0';

            if (state == LIBINPUT_KEY_STATE_PRESSED)
            {
                strncpy(key_states[key].state, "pressed", sizeof(key_states[key].state) - 1);
            }
            else
            {
                strncpy(key_states[key].state, "released", sizeof(key_states[key].state) - 1);
            }
            key_states[key].state[sizeof(key_states[key].state) - 1] = '\0';
        }
    }

    pthread_mutex_unlock(state_mutex);
}