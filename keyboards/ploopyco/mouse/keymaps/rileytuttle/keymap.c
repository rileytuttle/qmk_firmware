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

// safe range starts at `PLOOPY_SAFE_RANGE` instead.

enum ploopy_layers {
    _BASE,
    _LAYER_SELECTION,
    _GAMING,
};

enum my_ploopy_keycodes {
  LAYER_KEY = PLOOPY_SAFE_RANGE,
};

/* LAYOUTS are as follows
 *         | BTN_0 | BTN_1 | BTN_3 | BTN_4 |
 * | BTN_5 |           | BTN_2 |
 * | BTN_6 |           | BTN_7 |
 */

#define LAYOUT_PLOOPY_MOUSE(k0, k1, k2, k3, k4, k5, k6, k7) LAYOUT(k0, k1, k3, k4, k5, k2, k6, k7)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
     *         |CTRL_C |LFTCLK |RGHTCLK|CTRL_V |
     * |FORWARD|           |SCRLCLK|
     * | BACK  |           |LYERSEL|
     */
    [_BASE] = LAYOUT_PLOOPY_MOUSE(
                C(KC_C), KC_BTN1, KC_BTN2, C(KC_V),
        KC_BTN4,             KC_BTN3,
        KC_BTN5,             LT(_LAYER_SELECTION, KC_BTN5)
    ),

    [_LAYER_SELECTION] = LAYOUT_PLOOPY_MOUSE(
                C(KC_C), KC_BTN1, KC_BTN2, C(KC_V),
        KC_BTN4,             KC_BTN3,
        KC_BTN5,             LT(_LAYER_SELECTION, KC_BTN5)
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

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LAYER_KEY:
//             if 
