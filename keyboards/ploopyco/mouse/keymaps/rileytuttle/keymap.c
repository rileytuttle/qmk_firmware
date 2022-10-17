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
    _LAYER_2,
};

enum my_ploopy_keycodes {
  LAYER_KEY = PLOOPY_SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(/* Base */
        C(KC_C), KC_BTN1, KC_BTN3, KC_BTN2, C(KC_V), KC_BTN4, KC_BTN5, DPI_CONFIG),
    [_LAYER_2] = LAYOUT(/* LAYER 2 */
        C(KC_C), KC_BTN1, KC_BTN3, KC_BTN2, C(KC_V), KC_BTN4, KC_BTN5, DPI_CONFIG),
             
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LAYER_KEY:
//             if 
