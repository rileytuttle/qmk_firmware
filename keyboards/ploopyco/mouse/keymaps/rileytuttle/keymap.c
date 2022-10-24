/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "timer.h"

// safe range starts at `PLOOPY_SAFE_RANGE` instead.

enum ploopy_layers {
    _BASE,
    _LAYER_SELECTION,
    _GAMING,
};

enum my_ploopy_keycodes {
  LAYER_KEY = PLOOPY_SAFE_RANGE,
  GESTURE_KEY,
};

/* LAYOUTS are as follows
 *         | BTN_0 | BTN_1 | BTN_3 | BTN_4 |
 * | BTN_5 |           | BTN_2 |
 * | BTN_6 |           | BTN_7 |
 */

#define LAYOUT_PLOOPY_MOUSE(k0, k1, k2, k3, k4, k5, k6, k7) LAYOUT(k0, k1, k5, k2, k3, k4, k6, k7)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
     *         |CTRL_C |LFTCLK |RGHTCLK|CTRL_V |
     * |FORWARD|           |SCRLCLK|
     * | BACK  |           |LYERSEL|
     */
    [_BASE] = LAYOUT_PLOOPY_MOUSE(
                GESTURE_KEY, KC_BTN1, KC_BTN2, C(KC_V),
        KC_BTN4,             KC_BTN3,
        KC_BTN5,             LT(_LAYER_SELECTION, KC_BTN6)
    ),

    [_LAYER_SELECTION] = LAYOUT_PLOOPY_MOUSE(
                _______, DF(_BASE), DF(_GAMING), _______,
        _______,             _______,
        _______,             _______
    ),

    /* GAMING
     *         |CTRL_C |LFTCLK |RGHTCLK|CTRL_V |
     * |FORWARD|           |SCRLCLK|
     * | BACK  |           |DPICONF|
     */
    [_GAMING] = LAYOUT_PLOOPY_MOUSE(
                C(KC_C), KC_BTN1, KC_BTN2, C(KC_V),
        KC_BTN4,             KC_BTN3,
        KC_BTN5,             LT(_LAYER_SELECTION, KC_BTN5)
    ),
             
};

static bool s_gesture_key_pressed = false;
static bool s_sent_gesture = false;
static uint16_t s_sent_gesture_timestamp = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GESTURE_KEY:
            s_gesture_key_pressed = record->event.pressed;
            break;
    }
    return true;
}

enum GestureType
{
    GESTURE_TYPE_NONE,
    GESTURE_TYPE_VERTICAL,
    GESTURE_TYPE_HORIZONTAL,
};

enum GestureDirection
{
    GESTURE_DIRECTION_NONE,
    GESTURE_DIRECTION_UP,
    GESTURE_DIRECTION_DOWN,
    GESTURE_DIRECTION_LEFT,
    GESTURE_DIRECTION_RIGHT
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report)
{
    // going to need a way to limit this to sending once per mouse stroke (something like mark the direction and then only use it once it goes back to zero)
    // or ignore everything after the first one until we reset to zero
    if (timer_elapsed(s_sent_gesture_timestamp) > 1000)
    {
        s_sent_gesture = false;
    }
    if (s_gesture_key_pressed)
    {
        int gesture_type = GESTURE_TYPE_NONE;
        int gesture_dir = GESTURE_DIRECTION_NONE;
        // interpret the mouse as key actions
        if (mouse_report.x != 0 && mouse_report.y != 0)
        {
            if (abs(mouse_report.x) >= abs(mouse_report.y)) { gesture_type = GESTURE_TYPE_VERTICAL; }
            else { gesture_type = GESTURE_TYPE_HORIZONTAL; }
        }
        else if (mouse_report.x != 0)
        {
            gesture_type = GESTURE_TYPE_VERTICAL;
        }
        else if (mouse_report.y != 0)
        {
            gesture_type = GESTURE_TYPE_HORIZONTAL;
        }
        switch (gesture_type)
        {
            case GESTURE_TYPE_VERTICAL:
                if (mouse_report.y > 0) { gesture_dir = GESTURE_DIRECTION_LEFT; }
                else if (mouse_report.y < 0) { gesture_dir = GESTURE_DIRECTION_RIGHT; }
                break;
            case GESTURE_TYPE_HORIZONTAL:
                if (mouse_report.x > 0) { gesture_dir = GESTURE_DIRECTION_DOWN; }
                else if (mouse_report.x < 0) { gesture_dir = GESTURE_DIRECTION_UP; }
                break;
            case GESTURE_TYPE_NONE:
                gesture_dir = GESTURE_DIRECTION_NONE;
                break;
        }
        switch (gesture_dir)
        {
            case GESTURE_DIRECTION_UP:
                if (!s_sent_gesture)
                {
                    SEND_STRING(SS_LGUI(SS_TAP(X_UP)));
                    s_sent_gesture_timestamp = timer_read();
                    s_sent_gesture = true;
                }
                break;
            case GESTURE_DIRECTION_DOWN:
                if (!s_sent_gesture)
                {
                    SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
                    s_sent_gesture_timestamp = timer_read();
                    s_sent_gesture = true;
                }
                break;
            case GESTURE_DIRECTION_LEFT:
                if (!s_sent_gesture)
                {
                    SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
                    s_sent_gesture_timestamp = timer_read();
                    s_sent_gesture = true;
                }
                break;
            case GESTURE_DIRECTION_RIGHT:
                if (!s_sent_gesture)
                {
                    SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
                    s_sent_gesture_timestamp = timer_read();
                    s_sent_gesture = true;
                }
                break;
            case GESTURE_DIRECTION_NONE:
                // placeholder
                break;
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    else
    {
        s_sent_gesture = false;
    }
    return mouse_report;
}

void keyboard_post_init_user(void)
{
    debug_enable  = true;
    debug_matrix  = true;
    debug_mouse   = true;
}
