#include QMK_KEYBOARD_H

/*void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_mouse=true;
}*/

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#    define CARRETM KC_NO
#endif // !POINTING_DEVICE_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

enum tap_dance_keymap {
    TD_SLSHS,
    TD_QOUT_KC_GRV,
    TD_LBRC_KC_MINS,
    TD_RBRC_KC_EQL,
    TD_DOT_COMM,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for /?, twice for \|
    [TD_SLSHS] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_BACKSLASH),
    // Tap once for '", twice for `~
    [TD_QOUT_KC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRV),
    // Tap once for [{, twice for -_
    [TD_LBRC_KC_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_MINS),
    // Tap once for }], twice for =+
    [TD_RBRC_KC_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_EQL),
    // Tap once for .>, twice for ,<
    [TD_DOT_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMM),
};

enum custom_keycodes {
    SCRN_SHT = SAFE_RANGE,
    CAST_SHT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCRN_SHT:
            if (record->event.pressed) {
                // when keycode SCRN_SHT is pressed
                SEND_STRING(SS_LGUI(SS_LSFT("4")));
            } else {
                // when keycode SCRN_SHT is released
            }
            break;
        case CAST_SHT:
            if (record->event.pressed) {
                // when keycode SCRN_SHT is pressed
                SEND_STRING(SS_LGUI(SS_LSFT("5")));
            } else {
                // when keycode SCRN_SHT is released
            }
            break;
    }
    return true;
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
/*#define PT_Z LT(LAYER_POINTER, KC_Z)*/
/*#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)*/
#define POINT MO(LAYER_POINTER)
#define SLSHS TD(TD_SLSHS)
#define QOU_GRV TD(TD_QOUT_KC_GRV)
#define LBR_MIN TD(TD_LBRC_KC_MINS)
#define RBR_EQL TD(TD_RBRC_KC_EQL)
#define DOT_COM TD(TD_DOT_COMM)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, LBR_MIN,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         RAISE,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, QOU_GRV,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         LOWER,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT,   SLSHS, RBR_EQL,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_LALT, KC_LGUI, KC_LSFT,    KC_RSFT,  KC_SPC,
                                           KC_LCTL,   POINT,     KC_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX,SCRN_SHT,CAST_SHT,   XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX,   KC_DEL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_KP_1, KC_KP_2, KC_KP_3, DOT_COM, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    KC_KP_0, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP, KC_HOME,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIU, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_END,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_VOLD,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       CARRETM, XXXXXXX, XXXXXXX, XXXXXXX, S_D_MOD, DPI_MOD,    DPI_MOD, S_D_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       DRGSCRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       SNIPING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}
