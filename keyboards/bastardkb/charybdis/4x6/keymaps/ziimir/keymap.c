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
    TD_MIN_EQL,
    TD_DOT_COMM,
    TD_TRIPL_GRV
};

void triple_grave(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            SEND_STRING(SS_TAP(X_GRAVE));
            break;
        case 2:
            SEND_STRING("```");
            break;
        case 3:
            SEND_STRING("```\n\n```"SS_TAP(X_UP));
    }

    reset_tap_dance(state);
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for -_, twice for =+
    [TD_MIN_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),

    // Tap once for ., twice for ,
    [TD_DOT_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_PDOT, KC_COMM),

    // Tap once for `~, twice for ``` thrice for ```<CR>```
    [TD_TRIPL_GRV] = ACTION_TAP_DANCE_FN(triple_grave),
};

enum custom_keycodes {
    SCRN_SHT = SAFE_RANGE,
    SCRN_CST,
    CHG_LNG,
    SRH_SPT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCRN_SHT:
            if (record->event.pressed) {
                // when keycode SCRN_SHT is pressed; else clause - when keycode is released
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
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
            }
            break;
        case SRH_SPT:
            if (record->event.pressed) {
                // CMD + ALT + N - open small arc browser
                if (get_mods() & MOD_MASK_GUI) {
                    // No need to register GUI (CMD) because it's already active
                    SEND_STRING(SS_LALT("n"));
                } else {
                    SEND_STRING(SS_LCTL(SS_TAP(X_SPACE)));
                }
            }
            break;
    }
    return true;
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define POINT MO(LAYER_POINTER)
/*#define PT_SCLN LT(LAYER_POINTER, KC_SCLN)*/

#define A_LSFT MT(MOD_LSFT, KC_A)
#define S_LCTL MT(MOD_LCTL, KC_S)
#define D_LALT MT(MOD_LALT, KC_D)
#define F_LGUI MT(MOD_LGUI, KC_F)

#define SCL_SFT MT(MOD_RSFT, KC_SCLN)
#define L_RCTL MT(MOD_RCTL, KC_L)
#define K_RALT MT(MOD_RALT, KC_K)
#define J_RGUI MT(MOD_RGUI, KC_J)

#define MIN_EQL TD(TD_MIN_EQL)
#define DOT_COM TD(TD_DOT_COMM)
#define TRI_GRV TD(TD_TRIPL_GRV)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, MIN_EQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_BSLS,  A_LSFT,  S_LCTL,  D_LALT,  F_LGUI,    KC_G,       KC_H,  J_RGUI,  K_RALT,  L_RCTL, SCL_SFT, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       TRI_GRV,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    POINT, SRH_SPT,  KC_ENT,    KC_BSPC,  KC_SPC,
                                           CHG_LNG,   LOWER,      RAISE
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX,SCRN_SHT,SCRN_CST,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PSLS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, DOT_COM, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    _______, _______,
                                           XXXXXXX, XXXXXXX,    KC_PEQL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIU, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BRID, KC_VOLD,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,     KC_DEL, XXXXXXX,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    DPI_MOD, S_D_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,    XXXXXXX, KC_BTN1, KC_BTN2, CARRETM, DRGSCRL, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                           SNIPING, XXXXXXX,    XXXXXXX
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
