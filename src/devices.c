/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */

#include "../include/devices.h"

int is_device_keyboard(const char *path)
{
    int fd;
    unsigned long evbit = 0;
    int is_keyboard = 0;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        return 0;
    }

    if (ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit) >= 0)
    {
        if (evbit & (1 << EV_KEY))
        {
            unsigned long keybit[KEY_MAX / (sizeof(unsigned long) * 8) + 1] = {0};

            if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) >= 0)
            {
                if ((keybit[KEY_A / (sizeof(unsigned long) * 8)] &
                     (1UL << (KEY_A % (sizeof(unsigned long) * 8)))) &&
                    (keybit[KEY_Z / (sizeof(unsigned long) * 8)] &
                     (1UL << (KEY_Z % (sizeof(unsigned long) * 8)))))
                {
                    is_keyboard = 1;
                }
            }
        }
    }

    close(fd); 
    return is_keyboard;
}

static int get_device_name(const char *path, char *name, size_t name_size)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        snprintf(name, name_size, "Unknown Device");
        return -1;
    }

    if (ioctl(fd, EVIOCGNAME(name_size), name) < 0)
    {
        snprintf(name, name_size, "Unknown Device");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int find_keyboard_devices(InputDevice *devices, int max_devices)
{
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    int count = 0;

    dir = opendir(INPUT_DIR);
    if (!dir)
    {
        fprintf(stderr, "Failed to open %s: %s\n", INPUT_DIR, strerror(errno));
        return 0;
    }

    while ((entry = readdir(dir)) != NULL && count < max_devices)
    {
        if (strncmp(entry->d_name, INPUT_EVENT_PREFIX, strlen(INPUT_EVENT_PREFIX)) == 0)
        {
            snprintf(path, sizeof(path), "%s/%s", INPUT_DIR, entry->d_name);

            if (is_device_keyboard(path))
            {
                snprintf(devices[count].path, sizeof(devices[count].path), "%s", path);

                get_device_name(path, devices[count].name, sizeof(devices[count].name));
                devices[count].is_keyboard = 1;

                count++;
            }
        }
    }

    closedir(dir);
    return count;
}

void print_device_list(InputDevice *devices, int count)
{
    printf("\nDetected keyboard devices:\n");
    printf("---------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%d] %s (%s)\n", i + 1, devices[i].name, devices[i].path);
    }

    printf("---------------------------\n");
}

char *prompt_device_selection(InputDevice *devices, int count)
{
    int selection;
    char input[16];

    if (count == 0)
    {
        fprintf(stderr, "No keyboard devices detected.\n");
        return NULL;
    }

    if (count == 1)
    {
        printf("info: found one keyboard device: %s (%s)\n", devices[0].name, devices[0].path);
        // fgets(input, sizeof(input), stdin);
        // printf("\n");
        // printf(devices[0].path);
        return strdup(devices[0].path);
    }

    print_device_list(devices, count);

    printf("Select keyboard device (1-%d): ", count);
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return NULL;
    }

    selection = atoi(input);
    if (selection < 1 || selection > count)
    {
        fprintf(stderr, "Invalid selection.\n");
        return NULL;
    }

    return strdup(devices[selection - 1].path);
}