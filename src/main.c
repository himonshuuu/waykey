/*
 * waykey - Linux keyboard monitoring tool
 * Copyright (C) 2025 Himangshu Saikia
 * Licensed under GNU GPL-3.0
 */


#include "../include/waykey.h"
#include "../include/devices.h"
#include "../include/keystate.h"
#include "../include/config.h"

static KeyCaptureConfig config = {0};
static KeyState key_states[MAX_KEYS];
static pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;

static void signal_handler(int signal)
{
    (void)signal;
    config.running = 0;
}

static void print_usage(const char *program_name)
{
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("Options:\n");
    printf("  -d, --device PATH    Specify input device path (if not specified, will auto-detect)\n");
    printf("  -p, --pipe PATH      Specify named pipe path (default: %s)\n", DEFAULT_PIPE_PATH);
    printf("  -s, --state PATH     Specify state file path (default: %s)\n", DEFAULT_STATE_FILE);
    printf("  -l, --list           List available keyboard devices and exit\n");
    printf("  -h, --help           Display this help message\n");
}

int main(int argc, char *argv[])
{
    struct libinput *li = NULL;
    int opt;
    int list_only = 0;

    config.device_path = NULL;
    config.pipe_path = DEFAULT_PIPE_PATH;
    config.state_path = DEFAULT_STATE_FILE;
    config.pipe_fd = -1;
    config.running = 1;

    // Load configuration from file
    Config *file_config = load_config();
    if (file_config) {
        if (file_config->device_path) {
            config.device_path = strdup(file_config->device_path);
        }
        if (file_config->pipe_path) {
            config.pipe_path = strdup(file_config->pipe_path);
        }
        if (file_config->state_path) {
            config.state_path = strdup(file_config->state_path);
        }
        free_config(file_config);
    }

    init_key_states(key_states);
    init_key_names();

    static struct option long_options[] = {
        {"device", required_argument, 0, 'd'},
        {"pipe", required_argument, 0, 'p'},
        {"state", required_argument, 0, 's'},
        {"list", no_argument, 0, 'l'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "d:p:s:lh", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'd':
            config.device_path = optarg;
            break;
        case 'p':
            config.pipe_path = optarg;
            break;
        case 's':
            config.state_path = optarg;
            break;
        case 'l':
            list_only = 1;
            break;
        case 'h':
            print_usage(argv[0]);
            return 0;
        default:
            print_usage(argv[0]);
            return 1;
        }
    }

    InputDevice devices[MAX_DEVICES];
    int device_count = find_keyboard_devices(devices, MAX_DEVICES);

    if (list_only)
    {
        print_device_list(devices, device_count);
        return 0;
    }

    if (!config.device_path)
    {
        if (device_count == 0)
        {
            fprintf(stderr, "error: No keyboard devices found\n");
            return 1;
        }

        config.device_path = prompt_device_selection(devices, device_count);

        if (!config.device_path)
        {
            fprintf(stderr, "error: No device selected\n");
            return 1;
        }
    }
    else
    {
        if (!is_device_keyboard(config.device_path))
        {
            fprintf(stderr, "warning: The specified device may not be a keyboard.\n");
            printf("Do you want to continue? (y/n): ");

            char response;
            scanf("%c", &response);
            if (response != 'y' && response != 'Y')
            {
                return 1;
            }
        }
    }

    printf("info: using keyboard device: %s\n", config.device_path);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (access(config.pipe_path, F_OK) != 0)
    {
        if (mkfifo(config.pipe_path, 0666) != 0)
        {
            fprintf(stderr, "error creating named pipe: %s\n", strerror(errno));
            return 1;
        }
    }

    config.pipe_fd = open(config.pipe_path, O_WRONLY | O_NONBLOCK);
    if (config.pipe_fd < 0 && errno == ENXIO)
    {
        fprintf(stderr, "info: no process is reading from the pipe yet. will continue updating the state file.\n");
        fprintf(stderr, "info: no connect to the pipe: 'cat %s' in another terminal.\n", config.pipe_path);
    }
    else if (config.pipe_fd < 0)
    {
        fprintf(stderr, "warning: could not open named pipe for writing: %s\n", strerror(errno));
    }

    li = init_libinput(config.device_path);
    if (!li)
    {
        fprintf(stderr, "failed to initialize libinput\n");
        if (config.pipe_fd >= 0)
            close(config.pipe_fd);
        free(config.device_path);
        return 1;
    }

    run_capture_loop(&config, li, key_states, &state_mutex);

    cleanup_resources(&config, li);
    if (config.device_path && !argv[1])
    {
        free(config.device_path);
    }

    return 0;
}