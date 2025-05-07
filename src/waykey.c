/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#include "../include/waykey.h"
#include "../include/keystate.h"

static int open_restricted(const char *path, int flags, void *user_data)
{
    (void)user_data;
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void *user_data)
{
    (void)user_data;
    close(fd);
}

const struct libinput_interface interface = {
    .open_restricted = open_restricted,
    .close_restricted = close_restricted,
};

struct libinput *init_libinput(const char *device_path)
{
    struct libinput *li;
    struct libinput_device *dev;

    li = libinput_path_create_context(&interface, NULL);
    if (!li)
    {
        fprintf(stderr, "Failed to create libinput context\n");
        return NULL;
    }

    if (device_path)
    {
        dev = libinput_path_add_device(li, device_path);
        if (!dev)
        {
            fprintf(stderr, "Failed to add device: %s\n", strerror(errno));
            libinput_unref(li);
            return NULL;
        }

        if (!libinput_device_has_capability(dev, LIBINPUT_DEVICE_CAP_KEYBOARD))
        {
            fprintf(stderr, "Device is not a keyboard\n");
            libinput_unref(li);
            return NULL;
        }
    }
    else
    {
        fprintf(stderr, "No device path specified\n");
        libinput_unref(li);
        return NULL;
    }

    return li;
}

void run_capture_loop(KeyCaptureConfig *config, struct libinput *li, KeyState *key_states, pthread_mutex_t *state_mutex)
{
    while (config->running)
    {
        struct libinput_event *event;

        libinput_dispatch(li);

        while ((event = libinput_get_event(li)) != NULL)
        {
            struct libinput_event_keyboard *keyboard_event;
            uint32_t key, state;

            if (libinput_event_get_type(event) == LIBINPUT_EVENT_KEYBOARD_KEY)
            {
                keyboard_event = libinput_event_get_keyboard_event(event);
                key = libinput_event_keyboard_get_key(keyboard_event);
                state = libinput_event_keyboard_get_key_state(keyboard_event);

                update_key_state(key_states, key, state, state_mutex);

                update_state_file(config->state_path, key_states, state_mutex);
                send_pipe_update(config->pipe_fd, key_states, state_mutex);
            }

            libinput_event_destroy(event);
        }

        usleep(10000); // 10ms
    }
}

void cleanup_resources(KeyCaptureConfig *config, struct libinput *li)
{
    if (config->pipe_fd >= 0)
    {
        close(config->pipe_fd);
    }

    if (li)
    {
        libinput_unref(li);
    }

    printf("Exiting gracefully...\n");
}
