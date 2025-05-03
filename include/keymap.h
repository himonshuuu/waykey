#ifndef KEYMAP_H
#define KEYMAP_H

#include <linux/input-event-codes.h>

#define MAX_KEYS 256

extern const char *key_names[MAX_KEYS];

void init_key_names(void);

#endif // KEYMAP_H
