/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "security.h"
#include "toggler.h"

enum preonic_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _MOUSE,
  _TMUX,
  _RGB,
  _ADJUST,
  _LALT,
  _PWORD,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  GAMING,
  LOWER,
  RAISE,
  MOUSE,
  TMUX,
  RGBKEY,
  EXTRKTO, // extrakto macro
  ESCSHEL, // escape shell macro
  PWORD,   // PWORD layer key
  WORKP,   // work password
  HOMEP,   // personal password
  SSHP,    // ssh passphrase
  NAME,    // type out full name
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | MOUSE|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |RGBKEY| Alt  | GUI  | Lower| TMUX | Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  MOUSE,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LCTL, RGBKEY,  KC_LALT, KC_LGUI, LOWER,   TMUX,    KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
),

/* GAMING
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CAPSLK|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  `   | Alt  | GUI  | Space| LOWER| Space| RAISE| Home |PageDn|PageUp|QWERTY|
 * `-----------------------------------------------------------------------------------'
 */
 
[_GAMING] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,  \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  KC_LCTL, KC_GRV,  KC_LALT, KC_LGUI, KC_SPC,  LOWER,   KC_SPC,  RAISE,   KC_MNXT, KC_VOLD, KC_VOLU, DF(_QWERTY) \
),

/* LALT
 * holds some common alt key combos
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |  F4  |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | S-tab|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LALT] = LAYOUT_preonic_grid( \
  KC_GRV,  _______, _______, KC_F4,   _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  S(KC_TAB),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* LOWER
 * ,-----------------------------------------------------------------------------------.
 * | Del  |      |      |      |      |      |      |      |      |   [  |   ]  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |      |      |      |PrtScn|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ENTER| Left | Down | Right|      |      | Left | Down |  Up  | Right|   '  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgUp | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
 
[_LOWER] = LAYOUT_preonic_grid( \
  KC_DEL,  _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_DEL,  \
  _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, \
  KC_ENT,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_QUOT, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* RAISE
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |   7  |   8  |   9  |   -  |   =  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |      |   4  |   5  |   6  |   +  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |      |   1  |   2  |   3  |   *  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | RCTL |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_GRV,  _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_MINS, KC_EQL,  \
  _______, _______, KC_UP,   _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_BSPC, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_ASTR, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
  KC_RCTL, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* MOUSE
 * for mouse and scroll
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |scrlUp|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |scrlLt|scrlDn|scrlRt|      |      |      |MsLeft|MsDown| MsUp |MsRght|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |LftClk|RhtClk|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______, _______  \
),

/* TMUX
 * used for tmux control
 * ,-----------------------------------------------------------------------------------.
 * |ESCSHL|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |XTRKTO|      |      |      |      |      |      |      |      |      | C-A-]| C-A-\|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |C-left|C-down| C-up |C-rght|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LALT |      |      |      |      |      |      |      |S-left|S-down| S-up |S-rght|
 * `-----------------------------------------------------------------------------------'
 */
[_TMUX] = LAYOUT_preonic_grid( \
  ESCSHEL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  EXTRKTO, _______, _______, _______, _______, _______, _______, _______, _______, _______, C(A(KC_RBRC)),C(A(KC_BSLS)), \
  _______, _______, _______, _______, _______, _______, C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),_______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_LALT, _______, _______, _______, _______, _______, _______, _______, S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT) \
),

/* RGB
 * controls the backlight
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |TOGGLE|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | MOD- | BRTUP| BRTDN| MOD+ |
 * `-----------------------------------------------------------------------------------'
 */
[_RGB] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, RGB_RMOD,RGB_VAD, RGB_VAI, RGB_MOD  \
),

/* ADJUST
 * (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      | PWORD|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Gaming|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |MidOff|ClkTog|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   _______, RGB_TOG, RGB_MOD, RGB_VAI, _______, _______, _______, _______, PWORD,   _______, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, DF(_QWERTY), DF(_GAMING), _______, _______, _______, \
  _______, _______, _______, _______, _______,  MI_ON,   MI_OFF,  CK_TOGG, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* PWORD
 * Password layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | work |      | name |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | sshp |      |      |      | home |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PWORD] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, WORKP,   _______, NAME,    _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, SSHP,    _______, _______, _______, HOMEP,   _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

};

static TogglerData raise_hold_toggler_data;
static TogglerData mouse_hold_toggler_data;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t prev_keycode = 0;
  bool ret_val = true;
  switch (keycode) {
        case KC_LALT:
          if (record->event.pressed) {
            layer_on(_LALT);
          } else {
            layer_off(_LALT);
          }
          // break and return true
          // this way alt is still handled
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          ret_val = false;
          break;
        case RAISE:
        {
          if (prev_keycode != RAISE) { toggle_reset(&raise_hold_toggler_data); }
          const bool layer_hold_toggle = toggle_update(&raise_hold_toggler_data, record->event.pressed);

          if (record->event.pressed)
          {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          else
          {
            if (!layer_hold_toggle)
            {
              // if the key is not pressed and we aren't holding the layer
              // turn the layer off
              layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          ret_val = false;
          break;
        }
        case MOUSE:
        {
          if (prev_keycode != MOUSE) { toggle_reset(&mouse_hold_toggler_data); }
          const bool layer_hold_toggle = toggle_update(&mouse_hold_toggler_data, record->event.pressed);
          // this is necessary because this function would normally ret_val = false
          // but in order for music to work we need this to return true along with the
          // music_mask(keycode) -> process_music() function.
          // added this is_music_on condition but I don't know
          // what will happen if music is disabled. might not compile correctly
          // leaving like this for now until I figure out a more correct way to fix it
          if (!is_music_on())
          {
              if (record->event.pressed)
              {
                layer_on(_MOUSE);
              }
              else if (!layer_hold_toggle)
              {
                layer_off(_MOUSE);
              }
              ret_val = false;
          }
          break;
        }
        case TMUX:
          if (record->event.pressed) {
            layer_on(_TMUX);
          } else {
            layer_off(_TMUX);
          }
          ret_val = false;
          break;
        case RGBKEY:
          if (record->event.pressed) {
            layer_on(_RGB);
          } else {
            layer_off(_RGB);
          }
          ret_val = false;
          break;
        case EXTRKTO:
          if (record->event.pressed) {
            SEND_STRING(SS_LCTL("t")SS_TAP(X_TAB));
          }
          ret_val = false;
          break;
        case ESCSHEL:
          if (record->event.pressed) {
            SEND_STRING("~."SS_TAP(X_ENTER));
          }
          ret_val = false;
          break;
        case PWORD:
          if (record->event.pressed) {
            layer_on(_PWORD);
          } else {
            layer_off(_PWORD);
          }
          ret_val = false;
          break;
        case WORKP:
          if (record->event.pressed) {
            SEND_STRING(WORK_PWORD);
          }
          ret_val = false;
          break;
        case SSHP:
          if (record->event.pressed) {
            SEND_STRING(SSH_PPHRASE);
          }
          ret_val = false;
          break;
        case HOMEP:
          if (record->event.pressed) {
            SEND_STRING(PERSONAL_PWORD);
          }
          ret_val = false;
          break;
        case NAME:
          if (record->event.pressed) {
            SEND_STRING(FULL_NAME_NO_SPACE);
          }
          ret_val = false;
          break;
    }
    prev_keycode = keycode;
    return ret_val;
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_gaming[][2]     = SONG(COLEMAK_SOUND);
#endif

layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch(state) {
        case 1U << _QWERTY:
            #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_qwerty);
            #endif
            break;
        case 1U << _GAMING:
            #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_gaming);
            #endif
            break;
    }
    return state;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    case MOUSE:
    default:
      return true;
  }
}

// void keyboard_post_init_user(void) {
//   debug_enable=true;
//   debug_matrix=true;
// }
