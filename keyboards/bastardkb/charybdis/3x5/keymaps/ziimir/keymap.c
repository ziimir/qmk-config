/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUM,
    LAYER_SIGN,
    LAYER_MOVE,
    LAYER_FN,
    LAYER_POINTER,
};

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// SIGNS
#define G_SNG LT(LAYER_SIGN, KC_G)
#define H_SNG LT(LAYER_SIGN, KC_H)

// ARROWS
#define ESC_MV LT(LAYER_MOVE, KC_ESC)

// NUMS
#define TAB_NM LT(LAYER_NUM, KC_TAB)

// FN
#define FN MO(LAYER_FN)

// POINTER
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define PT_Z LT(LAYER_POINTER, KC_Z)

// TAP DANCE
enum tap_dance_keymap {
    TD_TRIPL_GRV
};

void triple_grave(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING(SS_TAP(X_GRAVE));
            break;
        case 2:
            SEND_STRING("``"SS_TAP(X_LEFT));
            break;
        case 3:
            SEND_STRING("```\n\n```"SS_TAP(X_UP));
    }

    reset_tap_dance(state);
}

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for `~, twice for ``` thrice for ```<CR>```
    [TD_TRIPL_GRV] = ACTION_TAP_DANCE_FN(triple_grave),
};

#define TRI_GRV TD(TD_TRIPL_GRV)

// MACRO
enum custom_keycodes {
    SCRN_SHT = SAFE_RANGE,
    SCRN_CST,
    CHG_LNG, // пока не используется
    MAC_MCS,
    WORD_LF,
    WORD_RT,
    LINE_LF,
    LINE_RT,
    BROW_PR,
    BROW_NX,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCRN_SHT:
            // when keycode SCRN_SHT is pressed; else clause - when keycode is released
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("4")));
            }
            break;
        case SCRN_CST:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("5")));
            }
            break;
        case CHG_LNG:
            if (record->event.pressed) {
                // CMD + SPACE - change language
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
            }
            break;
        case MAC_MCS:
            if (record->event.pressed) {
                // CMD + ALT + N - open small arc browser
                SEND_STRING(SS_LGUI(SS_LALT("n")));
            }
            break;
        case WORD_LF:
            if (record->event.pressed) {
                // ALT + Left: move one word to the left
                SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
            }
            break;
        case WORD_RT:
            if (record->event.pressed) {
                // ALT + Right: move one word to the right
                SEND_STRING(SS_LALT(SS_TAP(X_RIGHT)));
            }
            break;
        case LINE_LF:
            if (record->event.pressed) {
                // CMD + Left: move one word to the left
                SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
            }
            break;
        case LINE_RT:
            if (record->event.pressed) {
                // CMD + Right: move one word to the right
                SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
            }
            break;
        case BROW_PR:
            if (record->event.pressed) {
                // CMD + [: go previos in browser history
                SEND_STRING(SS_LGUI("["));
            }
            break;
        case BROW_NX:
            if (record->event.pressed) {
                // CMD + ]: go previos in browser history
                SEND_STRING(SS_LGUI("]"));
            }
            break;
    }
    return true;
};

// KEY OVERRIDES
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t volume_up_key_override = ko_make_basic(MOD_MASK_CTRL, KC_VOLU, KC_BRIU);
const key_override_t volume_down_key_override = ko_make_basic(MOD_MASK_CTRL, KC_VOLD, KC_BRID);

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &volume_up_key_override,
    &volume_down_key_override,
    NULL
};


// MOD TAP
// shift, ctrl, alt, gui left side
#define A_LSFT MT(MOD_LSFT, KC_A)
#define S_LCTL MT(MOD_LCTL, KC_S)
#define D_LALT MT(MOD_LALT, KC_D)
#define F_LGUI MT(MOD_LGUI, KC_F)

// shift, ctrl, alt, gui right side
#define SCL_SFT MT(MOD_RSFT, KC_SCLN)
#define L_RCTL MT(MOD_RCTL, KC_L)
#define K_RALT MT(MOD_RALT, KC_K)
#define J_RGUI MT(MOD_RGUI, KC_J)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        A_LSFT,  S_LCTL,  D_LALT,  F_LGUI,   G_SNG,      H_SNG,  J_RGUI,  K_RALT,  L_RCTL, SCL_SFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          ESC_MV,  TAB_NM,  KC_ENT,    KC_BSPC,  KC_SPC
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUM] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,    XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, _______, XXXXXXX,    KC_BSPC, KC_KP_0
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SIGN] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       TRI_GRV, KC_LCBR, KC_RCBR,   KC_AT, KC_BSLS,    KC_QUOT, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_PEQL,  KC_DLR, KC_HASH, KC_EXLM, KC_UNDS,    KC_PMNS, KC_AMPR, KC_ASTR, KC_PERC, KC_PLUS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_LBRC, KC_RBRC, KC_PIPE, XXXXXXX,    XXXXXXX, KC_DQUO, KC_LABK, KC_RABK, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_LGUI, KC_LCTL, KC_LSFT,    KC_QUES, KC_COLN
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_MOVE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       MAC_MCS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    LINE_LF, WORD_LF, WORD_RT, LINE_RT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_HOME, KC_MUTE, XXXXXXX,  KC_END, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______,      FN, XXXXXXX,    KC_VOLD, KC_VOLU
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_FN] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,    XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, XXXXXXX,   SCRN_CST,SCRN_SHT
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       RGB_TOG,  EE_CLR, QK_BOOT, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, QK_BOOT,  EE_CLR, RGB_TOG,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_BTN3,    KC_BTN3, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, DRGSCRL, SNIPING, BROW_NX, BROW_PR,    BROW_PR, BROW_NX, SNIPING, DRGSCRL, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_ESC, KC_BTN2, KC_BTN1,    KC_BTN2, KC_BTN1
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
