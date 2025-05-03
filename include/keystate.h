#ifndef KEYSTATE_H
#define KEYSTATE_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <libinput.h>
#include <json-c/json.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../include/keystate_type.h"

#define MAX_KEYS 256

void init_key_states(KeyState *key_states);
void update_state_file(const char *state_path, KeyState *key_states, pthread_mutex_t *state_mutex);
void send_pipe_update(int pipe_fd, KeyState *key_states, pthread_mutex_t *state_mutex);
void update_key_state(KeyState *key_states, uint32_t key, uint32_t state, pthread_mutex_t *state_mutex);

extern const char *key_names[MAX_KEYS];
void init_key_names(void);

#endif // KEYSTATE_H