#!/usr/bin/env python3

import json
import time

STATE_FILE_PATH = "/tmp/waykey_state.json"

MODIFIER_KEYS = {"ctrl", "alt", "shift", "super"}

def get_pressed_keys():
    """
    Reads the JSON file and returns a list of currently pressed keys.
    """
    try:
        with open(STATE_FILE_PATH, "r") as file:
            data = json.load(file)
        
        pressed_keys = [
            key["name"].lower() for key in data.get("keys", [])
            if key.get("state") == "pressed"
        ]
        
        return pressed_keys
    except FileNotFoundError:
        return []
    except json.JSONDecodeError:
        return []

def format_key_combination(pressed_keys):
    """
    Formats the pressed keys into a human-readable combination string.
    """
    modifiers = [key for key in pressed_keys if key in MODIFIER_KEYS]
    regular_keys = [key for key in pressed_keys if key not in MODIFIER_KEYS]
    
    if modifiers or regular_keys:
        return " + ".join(modifiers + regular_keys)
    else:
        return ""

def generate_waybar_output(combination, is_pressed):
    """
    Generates a JSON object compatible with Waybar.
    """
    return json.dumps({
        "text": combination or "",
        "class": "key-monitor" + (" pressed" if is_pressed else " released"),
    })

def main():
    """
    Monitors the state file for changes and outputs JSON for Waybar.
    """
    print("Monitoring pressed keys for Waybar... Press Ctrl+C to exit.")
    last_combination = None 

    try:
        while True:
            pressed_keys = get_pressed_keys()
            
            combination = format_key_combination(pressed_keys)
            
            is_pressed = bool(pressed_keys)
            
            if combination != last_combination:
                print(generate_waybar_output(combination, is_pressed), flush=True)
                last_combination = combination
            
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nExiting...")

if __name__ == "__main__":
    main()