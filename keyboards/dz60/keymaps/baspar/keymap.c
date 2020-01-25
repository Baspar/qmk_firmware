#include <stdio.h>
#include QMK_KEYBOARD_H

typedef union {
  uint32_t raw;
  struct {
    bool use_mac :1;
  };
} user_config_t;
user_config_t user_config;

// Layers
#define _DEFAULT 0
#define _DEFAULT_MAC 1
#define _FUNCTION 2
#define _FUNCTION_MAC 3

// Custom keycodes
#define ______ KC_TRNS
enum custom_keycodes {
  CHANGE_OS,
  A_ALT,
  E_ALT,
  I_ALT,
  O_ALT,
  U_ALT,
  C_ALT,
};

void go_to_mode(void) {
  if (user_config.use_mac) {
    set_unicode_input_mode(UC_OSX);
    rgblight_sethsv_noeeprom_magenta();
  } else {
    set_unicode_input_mode(UC_LNX);
    rgblight_sethsv_noeeprom_cyan();
  }
}

// Init
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  rgblight_enable();
  rgblight_mode(1);
  go_to_mode();
}

char* ALT_LETTER = NULL;
int* ALT_MOD = NULL;

/* send_unicode_hex_string("00E9"); */

void check_accent(void) {
  if (ALT_LETTER != NULL && ALT_MOD != NULL) {
  }
}
void change_OS (void) {
  user_config.use_mac = !user_config.use_mac;
  set_single_persistent_default_layer(user_config.use_mac);
  go_to_mode();
  eeconfig_update_user(user_config.raw);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CHANGE_OS:
      if (!record->event.pressed) {
        change_OS();
      }
      return false;
    default:
      return true;
  }
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
   * |    Shift        |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |  Del  |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |   Ctrl  |   GUI   |   Alt   |                     Space                       |  Fn   |   L   |   D   |   U   |   R   |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_DEFAULT] = LAYOUT_60_split_rshift_5x1u(
      KC_GRAVE         , KC_1   , KC_2   , KC_3   , KC_4         , KC_5   , KC_6   , KC_7 , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL  , KC_BSPC,
      KC_TAB           , KC_Q   , KC_W   , KC_E   , KC_R         , KC_T   , KC_Y   , KC_U , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC , KC_BSLS,
      LCTL_T(KC_ESCAPE), KC_A   , KC_S   , KC_D   , KC_F         , KC_G   , KC_H   , KC_J , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT  ,
      KC_LSFT          , KC_Z   , KC_X   , KC_C   , KC_V         , KC_B   , KC_N   , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_DEL  ,
      KC_LCTL          , KC_LGUI, KC_LALT, KC_SPC , MO(_FUNCTION), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
      ),

  /* Default Mac
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   -   |   =   |     Bkspc     |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |   Tab     |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   [   |   ]   |     \     |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |     Esc     |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Enter      |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |    Shift        |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |    Shift    |  Del  |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |   Ctrl  |  Option |   Cmd   |                     Space                       |  Fn   |   L   |   D   |   U   |   R   |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_DEFAULT_MAC] = LAYOUT_60_split_rshift_5x1u(
      KC_GRAVE         , KC_1   , KC_2   , KC_3   , KC_4             , KC_5   , KC_6   , KC_7 , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL  , KC_BSPC,
      KC_TAB           , KC_Q   , KC_W   , KC_E   , KC_R             , KC_T   , KC_Y   , KC_U , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC , KC_BSLS,
      LCTL_T(KC_ESCAPE), KC_A   , KC_S   , KC_D   , KC_F             , KC_G   , KC_H   , KC_J , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT  ,
      KC_LSFT          , KC_Z   , KC_X   , KC_C   , KC_V             , KC_B   , KC_N   , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_DEL  ,
      KC_LCTL          , KC_LALT, KC_LGUI, KC_SPC , MO(_FUNCTION_MAC), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
      ),

  /* Function
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |    Reset      |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       |       |       |       |       |       |       |       |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             |       |       |       |       |       |       |       |       |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |       |       |       |       |       |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |CHANGE_OS|         |                    VOL_TOGGLE                   |       |       | VOL_D | VOL_U |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_FUNCTION] = LAYOUT_60_split_rshift_5x1u(
      ______ , KC_F1     , KC_F2  , KC_F3         , KC_F4  , KC_F5  , KC_F6            , KC_F7          , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , RESET  ,
      ______ , ______    , ______ , E_ALT         , ______ , ______ , ______           , U_ALT          , I_ALT  , O_ALT  , ______ , ______ , ______ , ______ ,
      ______ , A_ALT     , ______ , ______        , ______ , ______ , ______           , ______         , ______ , ______ , ______ , ______ , ______ ,
      ______ , ______    , ______ , C_ALT         , ______ , ______ , ______           , ______         , ______ , ______ , ______ , ______ , ______ ,
      ______ , CHANGE_OS , ______ , KC_AUDIO_MUTE , ______ , ______ , KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, ______
      ),

  /* Function Mac
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |    Reset      |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       | E_ALT |       |       |       | U_ALT | I_ALT | O_ALT |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             | A_ALT |       |       |       |       |       |       |       |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       | C_ALT |       |       |       |       |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |CHANGE_OS|         |                    VOL_TOGGLE                   |       |       | VOL_D | VOL_U |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_FUNCTION_MAC] = LAYOUT_60_split_rshift_5x1u(
      ______ , KC_F1     , KC_F2  , KC_F3    , KC_F4  , KC_F5  , KC_F6      , KC_F7    , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , RESET  ,
      ______ , ______    , ______ , E_ALT    , ______ , ______ , ______     , U_ALT    , I_ALT  , O_ALT  , ______ , ______ , ______ , ______ ,
      ______ , A_ALT     , ______ , ______   , ______ , ______ , ______     , ______   , ______ , ______ , ______ , ______ , ______ ,
      ______ , ______    , ______ , C_ALT    , ______ , ______ , ______     , ______   , ______ , ______ , ______ , ______ , ______ ,
      ______ , CHANGE_OS , ______ , KC__MUTE , ______ , ______ , KC__VOLDOWN, KC__VOLUP, ______
      )
};
