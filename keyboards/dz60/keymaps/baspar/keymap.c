#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _FUNCTION 1

#define ______ KC_TRNS
enum custom_keycodes {
  A_ALT = SAFE_RANGE,
  E_ALT = SAFE_RANGE,
  I_ALT = SAFE_RANGE,
  O_ALT = SAFE_RANGE,
  U_ALT = SAFE_RANGE,
  C_ALT = SAFE_RANGE,
};

bool process_alt_key_in_progress = false;
/* uint16_t index = 0; */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(_FUNCTION):
            /* SEND_STRING(SS_TAP(RGB_TOG)); */
            if (!record->event.pressed) {
                process_alt_key_in_progress = false;
            } else {
                process_alt_key_in_progress = true;
            }
            break;
            /* case (E_ALT) { */
            /* } */
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Default
     * ,-----------------------------------------------------------------------------------------------------------------------.
     * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |     Bkspc     |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |   Tab     |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   |     \     |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |     Esc     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Enter      |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |    Shift        |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |  Fn   |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |   Ctrl  |   GUI   |   Alt   |                     Space                       |  Alt  |   L   |   D   |   U   |   R   |
     * `-----------------------------------------------------------------------------------------------------------------------'
     */

    [_DEFAULT] = LAYOUT_60_split_rshift_5x1u(
            KC_GRAVE         , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7 , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL        , KC_BSPC,
            KC_TAB           , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC       , KC_BSLS,
            LCTL_T(KC_ESCAPE), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT        ,
            KC_LSFT          , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, MO(_FUNCTION) ,
            KC_LCTL          , KC_LGUI, KC_LALT, KC_SPC , KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
            ),

    /* Function
     * ,-----------------------------------------------------------------------------------------------------------------------.
     * | Reset |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |               |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |           |       |       | E_ALT |       |       |       | U_ALT | I_ALT | O_ALT |       |       |       |           |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |             | A_ALT |       |       |       |       |       |       |       |       |       |       |                 |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |                 |       |       | C_ALT |       |       |       |       |       |       |       |             |       |
     * |-----------------------------------------------------------------------------------------------------------------------+
     * |         |         |         |                    VOL_TOGGLE                   |       |       | VOL_D | VOL_U |       |
     * `-----------------------------------------------------------------------------------------------------------------------'
     */

    [_FUNCTION] = LAYOUT_60_split_rshift_5x1u(
            RESET  , KC_F1  , KC_F2  , KC_F3         , KC_F4  , KC_F5  , KC_F6            , KC_F7          , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , ______ ,
            ______ , ______ , ______ , E_ALT         , ______ , ______ , ______           , U_ALT          , I_ALT  , O_ALT  , ______ , ______ , ______ , ______ ,
            ______ , A_ALT  , ______ , ______        , ______ , ______ , ______           , ______         , ______ , ______ , ______ , ______ , ______ ,
            ______ , ______ , ______ , C_ALT         , ______ , ______ , ______           , ______         , ______ , ______ , ______ , ______ , ______ ,
            ______ , ______ , ______ , KC_AUDIO_MUTE , ______ , ______ , KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, ______
            )
};
