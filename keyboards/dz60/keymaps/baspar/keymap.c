#include QMK_KEYBOARD_H

typedef union {
  uint32_t raw;
  struct {
    bool use_mac :1;
    uint8_t hues :8;
    uint8_t brightnesses :6;
    uint8_t modes :6;
    uint8_t speeds :6;
  };
} user_config_t;
user_config_t user_config;

// Macro
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define CONVERT_TO_UNICODE_(symbol, unicode) if (strcmp(name,symbol) == 0) { send_unicode_hex_string(unicode); }
#define CONVERT_TO_UNICODE(symbol, unicode) else if (strcmp(name,symbol) == 0) { send_unicode_hex_string(unicode); }
#define REGISTER_LETTER(letter) if (record->event.pressed) { ALT_LETTER = (letter); check_accent(); } return false;
#define REGISTER_MOD(modifier) if(record->event.pressed) { ALT_MOD = (modifier); check_accent(); } return false;

// Layers
#define _DEFAULT 0
#define _DEFAULT_MAC 1
#define _FUNCTION 2
#define _ACCENT 3
#define _ASCII 4

// Custom keycodes
enum custom_keycodes {
  CHANGE_OS = SAFE_RANGE,

  // ACCENTS
  ACCENT_LAYER,
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

  // RGB
  DEC_COL,
  INC_COL,
  RGB_OFF,
  RGB_STP,

  // ASCII
  MEH,
  FLIP_TABLE,
  LENNY,
  WAT,
  HAPPY,
  BEAR,
  CAT,
  SAD,
  YAY
};

enum rgb_status {
  ON,
  ONE_TIME_OFF,
  OFF
};

// Accent handling
char ALT_LETTER = '\0';
int ALT_MOD = -1;
void check_accent(void) {
  if (ALT_LETTER != '\0' && ALT_MOD != -1) {
    char name[6];
    name[0] = ALT_LETTER;
    name[1] = '\0';

    switch (ALT_MOD) {
      case REG_GRV:
        strcat(name, "_GRV");
        break;
      case REG_ACU:
        strcat(name, "_ACU");
        break;
      case REG_CED:
        strcat(name, "_CED");
        break;
      case REG_TRM:
        strcat(name, "_TRM");
        break;
      case REG_CIR:
        strcat(name, "_CIR");
        break;
      case REG_TIL:
        strcat(name, "_TIL");
        break;
    }

    // Lowercase
    CONVERT_TO_UNICODE_("a_GRV", "00E0")
    CONVERT_TO_UNICODE("a_ACU", "00E1")
    CONVERT_TO_UNICODE("a_CIR", "00E2")
    CONVERT_TO_UNICODE("a_TIL", "00E3")
    CONVERT_TO_UNICODE("a_TRM", "00E4")
    CONVERT_TO_UNICODE("e_GRV", "00E8")
    CONVERT_TO_UNICODE("e_ACU", "00E9")
    CONVERT_TO_UNICODE("e_CIR", "00EA")
    CONVERT_TO_UNICODE("e_TRM", "00EB")
    CONVERT_TO_UNICODE("i_GRV", "00EC")
    CONVERT_TO_UNICODE("i_ACU", "00ED")
    CONVERT_TO_UNICODE("i_CIR", "00EE")
    CONVERT_TO_UNICODE("i_TRM", "00EF")
    CONVERT_TO_UNICODE("o_GRV", "00F2")
    CONVERT_TO_UNICODE("o_ACU", "00F3")
    CONVERT_TO_UNICODE("o_CIR", "00F4")
    CONVERT_TO_UNICODE("o_TIL", "00F5")
    CONVERT_TO_UNICODE("o_TRM", "00F6")
    CONVERT_TO_UNICODE("u_GRV", "00F9")
    CONVERT_TO_UNICODE("u_ACU", "00FA")
    CONVERT_TO_UNICODE("u_CIR", "00FB")
    CONVERT_TO_UNICODE("u_TRM", "00FC")
    CONVERT_TO_UNICODE("y_ACU", "00FD")
    CONVERT_TO_UNICODE("c_CED", "00E7")
    CONVERT_TO_UNICODE("n_TIL", "00F1")
    // Uppercase
    CONVERT_TO_UNICODE("A_GRV", "00C0")
    CONVERT_TO_UNICODE("A_ACU", "00C1")
    CONVERT_TO_UNICODE("A_CIR", "00C2")
    CONVERT_TO_UNICODE("A_TIL", "00C3")
    CONVERT_TO_UNICODE("A_TRM", "00C4")
    CONVERT_TO_UNICODE("E_GRV", "00C8")
    CONVERT_TO_UNICODE("E_ACU", "00C9")
    CONVERT_TO_UNICODE("E_CIR", "00CA")
    CONVERT_TO_UNICODE("E_TRM", "00CB")
    CONVERT_TO_UNICODE("I_GRV", "00CC")
    CONVERT_TO_UNICODE("I_ACU", "00CD")
    CONVERT_TO_UNICODE("I_CIR", "00CE")
    CONVERT_TO_UNICODE("I_TRM", "00CF")
    CONVERT_TO_UNICODE("O_GRV", "00D2")
    CONVERT_TO_UNICODE("O_ACU", "00D3")
    CONVERT_TO_UNICODE("O_CIR", "00D4")
    CONVERT_TO_UNICODE("O_TIL", "00D5")
    CONVERT_TO_UNICODE("O_TRM", "00D6")
    CONVERT_TO_UNICODE("U_GRV", "00D9")
    CONVERT_TO_UNICODE("U_ACU", "00DA")
    CONVERT_TO_UNICODE("U_CIR", "00DB")
    CONVERT_TO_UNICODE("U_TRM", "00DC")
    CONVERT_TO_UNICODE("Y_ACU", "00DD")
    CONVERT_TO_UNICODE("C_CED", "00C7")
    CONVERT_TO_UNICODE("N_TIL", "00D1")

    ALT_LETTER = '\0';
    ALT_MOD = -1;
  }
}

// Backlight handling
#define SHIFT_HUE 15
#define SHIFT_BRIGHTNESS 15
int rgb_status = ON;
int rgb_modes[8] = {
  1,  // RGBLIGHT_MODE_STATIC_LIGHT
  2,  // RGBLIGHT_MODE_BREATHING
  6,  // RGBLIGHT_MODE_RAINBOW_MOOD
  9,  // RGBLIGHT_MODE_RAINBOW_SWIRL
  15, // RGBLIGHT_MODE_SNAKE
  21, // RGBLIGHT_MODE_KNIGHT
  24, // RGBLIGHT_MODE_CHRISTMAS
  25  // RGBLIGHT_MODE_STATIC_GRADIENT
};
int rgb_speeds[8] = {
  1, // RGBLIGHT_MODE_STATIC_LIGHT
  4, // RGBLIGHT_MODE_BREATHING
  3, // RGBLIGHT_MODE_RAINBOW_MOOD
  6, // RGBLIGHT_MODE_RAINBOW_SWIRL
  6, // RGBLIGHT_MODE_SNAKE
  3, // RGBLIGHT_MODE_KNIGHT
  1, // RGBLIGHT_MODE_CHRISTMAS
  8  // RGBLIGHT_MODE_STATIC_GRADIENT
};
void update_backlight(void) {
  bool use_mac = user_config.use_mac;
  int hue_mac = user_config.hues % 16;
  int hue_unix = user_config.hues / 16;
  int mode_mac = user_config.modes % 8;
  int mode_unix = user_config.modes / 8 % 8;
  int speed_mac = user_config.speeds % 8;
  int speed_unix = user_config.speeds / 8 % 8;
  int brightness_mac = user_config.brightnesses % 8;
  int brightness_unix = user_config.brightnesses / 8 % 8;
  int max_speed = rgb_speeds[use_mac ? mode_mac : mode_unix];
  rgblight_sethsv_noeeprom(
      (use_mac ? hue_mac : hue_unix) * 16 + SHIFT_HUE,
      255,
      (use_mac ? brightness_mac : brightness_unix) * 32 + SHIFT_BRIGHTNESS
    );
  rgblight_mode_noeeprom(rgb_modes[use_mac ? mode_mac : mode_unix] + (use_mac ? speed_mac : speed_unix) % max_speed);
}
void change_brightness(int delta) {
  bool use_mac = user_config.use_mac;

  int brightness_mac = user_config.brightnesses % 8;
  int brightness_unix = user_config.brightnesses / 8 % 8;

  if (use_mac) {
    brightness_mac = MIN(7, MAX(0, brightness_mac + delta));
  } else {
    brightness_unix = MIN(7, MAX(0, brightness_unix + delta));
  }

  user_config.brightnesses = (brightness_unix * 8) + brightness_mac;

  update_backlight();
  eeconfig_update_user(user_config.raw);
}
void change_hue(int delta) {
  bool use_mac = user_config.use_mac;

  int hue_mac = user_config.hues % 16;
  int hue_unix = user_config.hues / 16;

  if (use_mac) {
    hue_mac = (hue_mac + delta) % 16;
  } else {
    hue_unix = (hue_unix + delta) % 16;
  }

  user_config.hues = hue_unix * 16 + hue_mac;

  update_backlight();
  eeconfig_update_user(user_config.raw);
}
void change_mode(int delta) {
  bool use_mac = user_config.use_mac;

  int mode_mac = user_config.modes % 8;
  int mode_unix = user_config.modes / 8 % 8;

  int speed_mac = user_config.speeds % 8;
  int speed_unix = user_config.speeds / 8 % 8;


  if (use_mac) {
    mode_mac = (mode_mac + delta) % 8;
    speed_mac = 0;
  } else {
    mode_unix = (mode_unix + delta) % 8;
    speed_unix = 0;
  }

  user_config.modes = (mode_unix * 8) + mode_mac;
  user_config.speeds = (speed_unix * 8) + speed_mac;

  update_backlight();
  eeconfig_update_user(user_config.raw);
}
void change_speed(int delta) {
  bool use_mac = user_config.use_mac;

  int mode_mac = user_config.modes % 8;
  int mode_unix = user_config.modes / 8 % 8;
  int max_speed = rgb_speeds[use_mac ? mode_mac : mode_unix];

  int speed_mac = user_config.speeds % 8;
  int speed_unix = user_config.speeds / 8 % 8;

  if (use_mac) {
    speed_mac = (speed_mac + delta) % max_speed;
  } else {
    speed_unix = (speed_unix + delta) % max_speed;
  }

  user_config.speeds = (speed_unix * 8) + speed_mac;

  update_backlight();
  eeconfig_update_user(user_config.raw);
}

// OS handling
void go_to_mode(void) {
  if (user_config.use_mac) {
    /* set_unicode_input_mode(UC_MAC); */
    set_unicode_input_mode(UC_OSX);
  } else {
    set_unicode_input_mode(UC_LNX);
  }
  update_backlight();
}
void change_OS(void) {
  user_config.use_mac = !user_config.use_mac;
  set_single_persistent_default_layer(user_config.use_mac);
  go_to_mode();
  eeconfig_update_user(user_config.raw);
}

// Init
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  rgblight_enable();
  go_to_mode();
}

// Main Loop
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
  if (record->event.pressed && rgb_status == ONE_TIME_OFF) {
    rgb_status = ON;
    rgblight_enable_noeeprom();
    return false;
  }
  switch (keycode) {
    // ASCII
    case MEH:
      if (record->event.pressed) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      }
      return false;
    case FLIP_TABLE:
      if (record->event.pressed) {
        if (shift_pressed) {
          send_unicode_hex_string("0028 30D8 FF65 005F FF65 0029 30D8 2533 2501 2533");
        } else {
          send_unicode_hex_string("0028 256F 00B0 25A1 00B0 FF09 256F FE35 0020 253B 2501 253B");
        }
      }
      return false;
    case WAT:
      if (record->event.pressed) {
        send_unicode_hex_string("0ca0 005f 0ca0");
      }
      return false;
    case HAPPY:
      if (record->event.pressed) {
        send_unicode_hex_string("1555 0028 0020 141b 0020 0029 1557");
      }
      return false;
    case SAD:
      if (record->event.pressed) {
        send_unicode_hex_string("0ca5 005f 0ca5");
      }
      return false;
    case CAT:
      if (record->event.pressed) {
        send_unicode_hex_string("0020 002f 1420 ff61 2038 ff61 141f 005c");
      }
      return false;
    case BEAR:
      if (record->event.pressed) {
        send_unicode_hex_string("0295 0020 2022 1d25 2022 0294");
      }
      return false;
    case LENNY:
      if (record->event.pressed) {
        send_unicode_hex_string("0028 0020 0361 00b0 0020 0644 035c 0020 0361 00b0 0029");
      }
      return false;
    case YAY:
      if (record->event.pressed) {
        send_unicode_hex_string("005c 0028 0020 ff9f 30ee ff9f 0029 002f");
      }
      return false;

    // RGB
    case RGB_STP:
      if (!record->event.pressed) {
        if (shift_pressed) {
          change_speed(1);
        } else {
          change_mode(1);
        }
        return false;
      }
    case RGB_OFF:
      if (!record->event.pressed) {
        if (shift_pressed && rgb_status == ON) {
          rgblight_disable_noeeprom();
          rgb_status = OFF;
        } else if (!shift_pressed && rgb_status == ON){
          rgblight_disable_noeeprom();
          rgb_status = ONE_TIME_OFF;
        } else {
          rgblight_enable_noeeprom();
          rgb_status = ON;
        }
        return false;
      }
    case DEC_COL:
      if (!record->event.pressed) {
        if (shift_pressed) { change_brightness(-1); } else { change_hue(-1); }
        return false;
      }
    case INC_COL:
      if (!record->event.pressed) {
        if (shift_pressed) { change_brightness(1); } else { change_hue(1); }
        return false;
      }

    // Accent
    case ACCENT_LAYER:
      if (record->event.pressed) {
        layer_on(_ACCENT);
      } else {
        layer_off(_ACCENT);
        ALT_LETTER = '\0';
        ALT_MOD = -1;
      }
      return false;
    case REG_GRV:
      REGISTER_MOD(shift_pressed ? REG_TIL : REG_GRV)
    case REG_ACU:
      REGISTER_MOD(REG_ACU)
    case REG_CED:
      REGISTER_MOD(shift_pressed ? REG_CIR : REG_CED)
    case REG_TRM:
      REGISTER_MOD(REG_TRM)
    case REG_CIR:
      REGISTER_MOD(REG_CIR)
    case REG_TIL:
      REGISTER_MOD(REG_TIL)
    case REG_A:
      REGISTER_LETTER(shift_pressed ? 'A' : 'a');
    case REG_E:
      REGISTER_LETTER(shift_pressed ? 'E' : 'e');
    case REG_I:
      REGISTER_LETTER(shift_pressed ? 'I' : 'i');
    case REG_O:
      REGISTER_LETTER(shift_pressed ? 'O' : 'o');
    case REG_U:
      REGISTER_LETTER(shift_pressed ? 'U' : 'u');
    case REG_Y:
      REGISTER_LETTER(shift_pressed ? 'Y' : 'y');
    case REG_C:
      REGISTER_LETTER(shift_pressed ? 'C' : 'c');
    case REG_N:
      REGISTER_LETTER(shift_pressed ? 'N' : 'n');
    case CHANGE_OS:
      if (!record->event.pressed) {
        change_OS();
      }
      return false;
    default:
      return true;
  }
}

// Keymap
#define ______ KC_TRNS
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
   * | Accent  |   GUI   |   Alt   |                     Space                       |  Fn   |   ←   |   ↓   |   ↑   |   →   |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_DEFAULT] = LAYOUT_60_split_rshift_5x1u(
        KC_GRAVE         ,KC_1   ,KC_2   ,KC_3  ,KC_4         ,KC_5   ,KC_6   ,KC_7 ,KC_8   ,KC_9  ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,
        KC_TAB           ,KC_Q   ,KC_W   ,KC_E  ,KC_R         ,KC_T   ,KC_Y   ,KC_U ,KC_I   ,KC_O  ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
        LCTL_T(KC_ESCAPE),KC_A   ,KC_S   ,KC_D  ,KC_F         ,KC_G   ,KC_H   ,KC_J ,KC_K   ,KC_L  ,KC_SCLN,KC_QUOT,KC_ENT ,
        KC_LSFT          ,KC_Z   ,KC_X   ,KC_C  ,KC_V         ,KC_B   ,KC_N   ,KC_M ,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL ,
        ACCENT_LAYER     ,KC_LGUI,KC_LALT,KC_SPC,MO(_FUNCTION),KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT
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
   * | Accent  |  Option |   Cmd   |                     Space                       |  Fn   |   ←   |   ↓   |   ↑   |   →   |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_DEFAULT_MAC] = LAYOUT_60_split_rshift_5x1u(
        KC_GRAVE         ,KC_1   ,KC_2   ,KC_3  ,KC_4         ,KC_5   ,KC_6   ,KC_7  ,KC_8   ,KC_9  ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,
        KC_TAB           ,KC_Q   ,KC_W   ,KC_E  ,KC_R         ,KC_T   ,KC_Y   ,KC_U  ,KC_I   ,KC_O  ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
        LCTL_T(KC_ESCAPE),KC_A   ,KC_S   ,KC_D  ,KC_F         ,KC_G   ,KC_H   ,KC_J  ,KC_K   ,KC_L  ,KC_SCLN,KC_QUOT,KC_ENT ,
        KC_LSFT          ,KC_Z   ,KC_X   ,KC_C  ,KC_V         ,KC_B   ,KC_N   ,KC_M  ,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_DEL ,
        ACCENT_LAYER     ,KC_LALT,KC_LGUI,KC_SPC,MO(_FUNCTION),KC_LEFT,KC_DOWN,KC_UP ,KC_RIGHT
      ),

  /* Function
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |RGB_OFF|   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |    Reset      |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       |       |       |       |       |       |       |       |       |DEC_COL|INC_COL|           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             |       |PrtScrn|       |       |       |       |VOL_DWN|VOL_UP |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |       |       |       |       |       |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * | CHNG_OS |         |         |                    VOL_TOGGLE                   |       | HOME  |PAGE_DN|PAGE_UP|  END  |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_FUNCTION] = LAYOUT_60_split_rshift_5x1u(
        RGB_OFF   ,KC_F1  ,KC_F2  ,KC_F3   ,KC_F4  ,KC_F5  ,KC_F6    ,KC_F7       ,KC_F8     ,KC_F9  ,KC_F10 ,KC_F11  ,KC_F12 ,RESET  ,
        ______    ,______ ,______ ,______  ,______ ,______ ,______   ,______      ,______    ,______ ,______ ,DEC_COL ,INC_COL,RGB_STP,
        ______    ,______ ,KC_PSCR,______  ,______ ,______ ,______   ,KC__VOLDOWN ,KC__VOLUP ,______ ,______ ,______  ,______ ,
        ______    ,______ ,______ ,______  ,______ ,______ ,______   ,______      ,______    ,______ ,______ ,______  ,______ ,
        CHANGE_OS ,______ ,______ ,KC__MUTE,______ ,KC_HOME,KC_PGDOWN,KC_PGUP     ,KC_END
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
   * |         |         |         |                     ASCII                       |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_ACCENT] = LAYOUT_60_split_rshift_5x1u(
        REG_GRV,______,______,______     ,______,______,REG_CIR,______,______ ,______,______ ,______ ,______ ,______,
        ______ ,______,______,REG_E      ,______,______,REG_Y  ,REG_U ,REG_I  ,REG_O ,______ ,______ ,______ ,______,
        ______ ,REG_A ,______,______     ,______,______,______ ,______,______ ,______,REG_TRM,REG_ACU,______ ,
        ______ ,______,______,REG_C      ,______,______,REG_N  ,______,REG_CED,______,______ ,______ ,______ ,
        ______ ,______,______,OSL(_ASCII),______,______,______ ,______,______
      ),

  /* ASCII Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |       |       |       |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |  WAT  |       |       |       |  YAY  |       |       |       |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             |       |  SAD  |       | FLIP  |       | HAPPY |       |       |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |  CAT  |       | BEAR  |       |  MEH  |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_ASCII] = LAYOUT_60_split_rshift_5x1u(
      ______, ______, ______, ______, ______    , ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, WAT   , ______, ______    , ______, YAY   , ______, ______, ______, ______, ______, ______, ______,
      ______, ______, SAD   , ______, FLIP_TABLE, ______, HAPPY , ______, ______, LENNY , ______, ______, ______,
      ______, ______, ______, CAT   , ______    , BEAR  , ______, MEH   , ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______    , ______, ______, ______, ______
      ),
};
