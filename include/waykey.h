#ifndef WAYKEY_H
#define WAYKEY_H

#include <pthread.h>
#include <libinput.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <sys/stat.h>

#include "../include/keystate_type.h"

#define DEFAULT_PIPE_PATH "/tmp/waykey_pipe"
#define DEFAULT_STATE_FILE "/tmp/waykey_state.json"
#define MAX_KEYS 256
#define MAX_DEVICES 16
#define INPUT_DIR "/dev/input"
#define INPUT_EVENT_PREFIX "event"

typedef struct
{
    char *device_path;
    char *pipe_path;
    char *state_path;
    int pipe_fd;
    int running;
} KeyCaptureConfig;

extern const struct libinput_interface interface;
struct libinput *init_libinput(const char *device_path);
void run_capture_loop(KeyCaptureConfig *config, struct libinput *li, KeyState *key_states, pthread_mutex_t *state_mutex);
void cleanup_resources(KeyCaptureConfig *config, struct libinput *li);

#endif // WAYKEY_H
