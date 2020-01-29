#include QMK_KEYBOARD_H

typedef union {
  uint32_t raw;
  struct {
    bool use_mac :1;
  };
} user_config_t;
user_config_t user_config;

// TapDance
enum {
  TAP_LAYER
};

// Layers
#define _DEFAULT 0
#define _DEFAULT_MAC 1
#define _FUNCTION 2
#define _ACCENT 3

// Custom keycodes
#define ______ KC_TRNS
enum custom_keycodes {
  CHANGE_OS = SAFE_RANGE,
  REG_A,
  REG_E,
  REG_I,
  REG_O,
  REG_U,
  REG_Y,
  REG_C,
  REG_N,
  REG_GRV,
  REG_ACU,
  REG_CED,
  REG_TRM,
  REG_CIR,
  REG_TIL,
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

char ALT_LETTER = '\0';
int ALT_MOD = -1;

void check_accent(void) {
  if (ALT_LETTER != '\0' && ALT_MOD != -1) {
    char name[6];
    name[0] = ALT_LETTER;
    name[1] = '\0';
    if (ALT_MOD == REG_GRV) {
      strcat(name, "_GRV");
    } else if (ALT_MOD == REG_ACU) {
      strcat(name, "_ACU");
    } else if (ALT_MOD == REG_CED) {
      strcat(name, "_CED");
    } else if (ALT_MOD == REG_TRM) {
      strcat(name, "_TRM");
    } else if (ALT_MOD == REG_CIR) {
      strcat(name, "_CIR");
    } else if (ALT_MOD == REG_TIL) {
      strcat(name, "_TIL");
    }

    // Lowercase
    if (strcmp(name, "a_GRV") == 0) { send_unicode_hex_string("00E0"); }
    else if (strcmp(name, "a_ACU") == 0) { send_unicode_hex_string("00E1"); }
    else if (strcmp(name, "a_CIR") == 0) { send_unicode_hex_string("00E2"); }
    else if (strcmp(name, "a_TIL") == 0) { send_unicode_hex_string("00E3"); }
    else if (strcmp(name, "a_TRM") == 0) { send_unicode_hex_string("00E4"); }
    else if (strcmp(name, "e_GRV") == 0) { send_unicode_hex_string("00E8"); }
    else if (strcmp(name, "e_ACU") == 0) { send_unicode_hex_string("00E9"); }
    else if (strcmp(name, "e_CIR") == 0) { send_unicode_hex_string("00EA"); }
    else if (strcmp(name, "e_TRM") == 0) { send_unicode_hex_string("00EB"); }
    else if (strcmp(name, "i_GRV") == 0) { send_unicode_hex_string("00EC"); }
    else if (strcmp(name, "i_ACU") == 0) { send_unicode_hex_string("00ED"); }
    else if (strcmp(name, "i_CIR") == 0) { send_unicode_hex_string("00EE"); }
    else if (strcmp(name, "i_TRM") == 0) { send_unicode_hex_string("00EF"); }
    else if (strcmp(name, "o_GRV") == 0) { send_unicode_hex_string("00F2"); }
    else if (strcmp(name, "o_ACU") == 0) { send_unicode_hex_string("00F3"); }
    else if (strcmp(name, "o_CIR") == 0) { send_unicode_hex_string("00F4"); }
    else if (strcmp(name, "o_TIL") == 0) { send_unicode_hex_string("00F5"); }
    else if (strcmp(name, "o_TRM") == 0) { send_unicode_hex_string("00F6"); }
    else if (strcmp(name, "u_GRV") == 0) { send_unicode_hex_string("00F9"); }
    else if (strcmp(name, "u_ACU") == 0) { send_unicode_hex_string("00FA"); }
    else if (strcmp(name, "u_CIR") == 0) { send_unicode_hex_string("00FB"); }
    else if (strcmp(name, "u_TRM") == 0) { send_unicode_hex_string("00FC"); }
    else if (strcmp(name, "y_ACU") == 0) { send_unicode_hex_string("00FD"); }
    else if (strcmp(name, "c_CED") == 0) { send_unicode_hex_string("00E7"); }
    else if (strcmp(name, "n_TIL") == 0) { send_unicode_hex_string("00F1"); }
    // Uppercase
    else if (strcmp(name, "A_GRV") == 0) { send_unicode_hex_string("00C0"); }
    else if (strcmp(name, "A_ACU") == 0) { send_unicode_hex_string("00C1"); }
    else if (strcmp(name, "A_CIR") == 0) { send_unicode_hex_string("00C2"); }
    else if (strcmp(name, "A_TIL") == 0) { send_unicode_hex_string("00C3"); }
    else if (strcmp(name, "A_TRM") == 0) { send_unicode_hex_string("00C4"); }
    else if (strcmp(name, "E_GRV") == 0) { send_unicode_hex_string("00C8"); }
    else if (strcmp(name, "E_ACU") == 0) { send_unicode_hex_string("00C9"); }
    else if (strcmp(name, "E_CIR") == 0) { send_unicode_hex_string("00CA"); }
    else if (strcmp(name, "E_TRM") == 0) { send_unicode_hex_string("00CB"); }
    else if (strcmp(name, "I_GRV") == 0) { send_unicode_hex_string("00CC"); }
    else if (strcmp(name, "I_ACU") == 0) { send_unicode_hex_string("00CD"); }
    else if (strcmp(name, "I_CIR") == 0) { send_unicode_hex_string("00CE"); }
    else if (strcmp(name, "I_TRM") == 0) { send_unicode_hex_string("00CF"); }
    else if (strcmp(name, "O_GRV") == 0) { send_unicode_hex_string("00D2"); }
    else if (strcmp(name, "O_ACU") == 0) { send_unicode_hex_string("00D3"); }
    else if (strcmp(name, "O_CIR") == 0) { send_unicode_hex_string("00D4"); }
    else if (strcmp(name, "O_TIL") == 0) { send_unicode_hex_string("00D5"); }
    else if (strcmp(name, "O_TRM") == 0) { send_unicode_hex_string("00D6"); }
    else if (strcmp(name, "U_GRV") == 0) { send_unicode_hex_string("00D9"); }
    else if (strcmp(name, "U_ACU") == 0) { send_unicode_hex_string("00DA"); }
    else if (strcmp(name, "U_CIR") == 0) { send_unicode_hex_string("00DB"); }
    else if (strcmp(name, "U_TRM") == 0) { send_unicode_hex_string("00DC"); }
    else if (strcmp(name, "Y_ACU") == 0) { send_unicode_hex_string("00DD"); }
    else if (strcmp(name, "C_CED") == 0) { send_unicode_hex_string("00E7"); }
    else if (strcmp(name, "N_TIL") == 0) { send_unicode_hex_string("00D1"); }

    ALT_LETTER = '\0';
    ALT_MOD = -1;
  }
}
void change_OS (void) {
  user_config.use_mac = !user_config.use_mac;
  set_single_persistent_default_layer(user_config.use_mac);
  go_to_mode();
  eeconfig_update_user(user_config.raw);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
  switch (keycode) {
    case REG_GRV:
      if(record->event.pressed) {
        ALT_MOD = shift_pressed ? REG_TIL : REG_GRV;
        check_accent();
      }
      return false;
    case REG_ACU:
      if(record->event.pressed) {
        ALT_MOD = REG_ACU;
        check_accent();
      }
      return false;
    case REG_CED:
      if(record->event.pressed) {
        ALT_MOD = shift_pressed ? REG_CIR : REG_CED;
        check_accent();
      }
      return false;
    case REG_TRM:
      if(record->event.pressed) {
        ALT_MOD = REG_TRM;
        check_accent();
      }
      return false;
    case REG_CIR:
      if(record->event.pressed) {
        ALT_MOD = REG_CIR;
        check_accent();
      }
      return false;
    case REG_TIL:
      if(record->event.pressed) {
        ALT_MOD = REG_TIL;
        check_accent();
      }
      return false;
    case REG_A:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'A' : 'a';
        check_accent();
      }
      return false;
    case REG_E:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'E' : 'e';
        check_accent();
      }
      return false;
    case REG_I:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'I' : 'i';
        check_accent();
      }
      return false;
    case REG_O:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'O' : 'o';
        check_accent();
      }
      return false;
    case REG_U:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'U' : 'u';
        check_accent();
      }
      return false;
    case REG_Y:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'Y' : 'y';
        check_accent();
      }
      return false;
    case REG_C:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'C' : 'c';
        check_accent();
      }
      return false;
    case REG_N:
      if (record->event.pressed) {
        ALT_LETTER = shift_pressed ? 'N' : 'n';
        check_accent();
      }
      return false;
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
        KC_GRAVE         ,KC_1   ,KC_2   ,KC_3  ,KC_4         ,KC_5   ,KC_6   ,KC_7 ,KC_8   ,KC_9  ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,
        KC_TAB           ,KC_Q   ,KC_W   ,KC_E  ,KC_R         ,KC_T   ,KC_Y   ,KC_U ,KC_I   ,KC_O  ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
        LCTL_T(KC_ESCAPE),KC_A   ,KC_S   ,KC_D  ,KC_F         ,KC_G   ,KC_H   ,KC_J ,KC_K   ,KC_L  ,KC_SCLN,KC_QUOT,KC_ENT ,
        KC_LSFT          ,KC_Z   ,KC_X   ,KC_C  ,KC_V         ,KC_B   ,KC_N   ,KC_M ,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL ,
        KC_LCTL          ,KC_LGUI,KC_LALT,KC_SPC,TD(TAP_LAYER),KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT
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
        KC_GRAVE         ,KC_1   ,KC_2   ,KC_3  ,KC_4         ,KC_5   ,KC_6   ,KC_7  ,KC_8   ,KC_9  ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,
        KC_TAB           ,KC_Q   ,KC_W   ,KC_E  ,KC_R         ,KC_T   ,KC_Y   ,KC_U  ,KC_I   ,KC_O  ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
        LCTL_T(KC_ESCAPE),KC_A   ,KC_S   ,KC_D  ,KC_F         ,KC_G   ,KC_H   ,KC_J  ,KC_K   ,KC_L  ,KC_SCLN,KC_QUOT,KC_ENT ,
        KC_LSFT          ,KC_Z   ,KC_X   ,KC_C  ,KC_V         ,KC_B   ,KC_N   ,KC_M  ,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL ,
        KC_LCTL          ,KC_LALT,KC_LGUI,KC_SPC,TD(TAP_LAYER),KC_LEFT,KC_DOWN,KC_UP ,KC_RIGHT
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
        ______ ,KC_F1    ,KC_F2 ,KC_F3   ,KC_F4 ,KC_F5 ,KC_F6      ,KC_F7    ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12,RESET ,
        ______ ,______   ,______,______  ,______,______,______     ,______   ,______ ,______ ,______ ,______ ,______,______,
        ______ ,______   ,______,______  ,______,______,______     ,______   ,______ ,______ ,______ ,______ ,______,
        ______ ,______   ,______,______  ,______,______,______     ,______   ,______ ,______ ,______ ,______ ,______,
        ______ ,CHANGE_OS,______,KC__MUTE,______,______,KC__VOLDOWN,KC__VOLUP,______
      ),

  /* Accent Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |REG_GRV|       |       |       |       |       |REG_CIR|       |       |       |       |       |       |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       | REG_E |       |       | REG_Y | REG_U | REG_I | REG_O |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             | REG_A |       |       |       |       |       |       |       |       |REG_TRM|REG_ACU|                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       | REG_C |       |       | REG_N |       |REG_CED|       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_ACCENT] = LAYOUT_60_split_rshift_5x1u(
        REG_GRV,______,______,______,______,______,REG_CIR,______,______ ,______,______ ,______ ,______,______,
        ______ ,______,______,REG_E ,______,______,REG_Y  ,REG_U ,REG_I  ,REG_O ,______ ,______ ,______,______,
        ______ ,REG_A ,______,______,______,______,______ ,______,______ ,______,REG_TRM,REG_ACU,______,
        ______ ,______,______,REG_C ,______,______,REG_N  ,______,REG_CED,______,______ ,______ ,______,
        ______ ,______,______,______,______,______,______ ,______,______
      ),
};


// Tap Dance
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_FUNCTION);
  } else {
    layer_off(_ACCENT);
    ALT_LETTER = '\0';
    ALT_MOD = -1;
  }
}

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_on(_FUNCTION);
  } else {
    layer_on(_ACCENT);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TAP_LAYER]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
