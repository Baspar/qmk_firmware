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
#define REGISTER_LETTER(letter) if (record->event.pressed) { ALT_LETTER = (letter); check_accent(); } return RETURN_FALSE;
#define REGISTER_MOD(modifier) if(record->event.pressed) { ALT_MOD = (modifier); check_accent(); } return RETURN_FALSE;
#define MATCH_OR_CONTINUE(x) switch (x) { case RETURN_FALSE: return false; case RETURN_TRUE: return true; case CONTINUE: break; }

// Layers
#define _DEFAULT 0
#define _DEFAULT_MAC 1
#define _FUNCTION 2
#define _ASCII 3
#define _SUPERSCRIPT 4
#define _REVERSE 5
#define _MAD 6
#define _ZALGO 7
#define _ACCENT 8

#define MIN_ZALGO_MOD 2
#define MAX_ZALGO_MOD 8

// Custom keycodes
enum custom_keycodes {
  CHANGE_OS = SAFE_RANGE,
  CYCLE_MAD_LAYERS,
  CYCLE_UPPER_LAYERS,

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
  ANGRY,
  MEH,
  FLIP_TABLE,
  LENNY,
  WAT,
  HAPPY,
  BEAR,
  CAT,
  SAD,
  YAY,
  NO,

  // SUPERSCRIPT
  SUP_A,
  SUP_B,
  SUP_C,
  SUP_D,
  SUP_E,
  SUP_F,
  SUP_G,
  SUP_H,
  SUP_I,
  SUP_J,
  SUP_K,
  SUP_L,
  SUP_M,
  SUP_N,
  SUP_O,
  SUP_P,
  SUP_R,
  SUP_S,
  SUP_T,
  SUP_U,
  SUP_V,
  SUP_W,
  SUP_X,
  SUP_Y,
  SUP_Z,
  SUP_1,
  SUP_2,
  SUP_3,
  SUP_4,
  SUP_5,
  SUP_6,
  SUP_7,
  SUP_8,
  SUP_9,
  SUP_0,
  SUP_MIN,
  SUP_EQL,
  SUP_DOT,

  // REV
  REV_A,
  REV_B,
  REV_C,
  REV_D,
  REV_E,
  REV_F,
  REV_G,
  REV_H,
  REV_I,
  REV_J,
  REV_K,
  REV_L,
  REV_M,
  REV_N,
  REV_O,
  REV_P,
  REV_Q,
  REV_R,
  REV_S,
  REV_T,
  REV_U,
  REV_V,
  REV_W,
  REV_X,
  REV_Y,
  REV_Z,
  REV_SPACE,
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

// Special LED color
void special_mode_color(uint32_t H, uint32_t S,  uint32_t mode) {
  bool use_mac = user_config.use_mac;
  int brightness_mac = user_config.brightnesses % 8;
  int brightness_unix = user_config.brightnesses / 8 % 8;
  int brightness = (use_mac ? brightness_mac : brightness_unix) * 32 + SHIFT_BRIGHTNESS;

  rgblight_sethsv_noeeprom(H, S, brightness);
  rgblight_mode_noeeprom(mode);
}
uint32_t layer_state_set_user(uint32_t state) {
  if (IS_LAYER_ON(_MAD)) {
    special_mode_color(0, 255, 15);
  } else if (IS_LAYER_ON(_ZALGO)) {
    special_mode_color(0, 255, 19);
  } else if (IS_LAYER_ON(_SUPERSCRIPT)) {
    special_mode_color(16 * 3, 255, 15);
  } else if (IS_LAYER_ON(_REVERSE)) {
    special_mode_color(16 * 3, 255, 19);
  } else {
    switch(biton32(state)) {
      case _ASCII:
        special_mode_color(0, 0, 15);
        break;
      case _ACCENT:
        break;
      default:
        update_backlight();
        break;
    }
  }
  return state;
}

// Special KeyCodes
char* REVERSE_CODES[] = {
  "2C6F", "0250", // Ɐ / ɐ
  "A4ED", "0071", // ꓭ / q
  "A4DB", "0254", // ꓛ / ɔ
  "A4F7", "0070", // ꓷ / p
  "018E", "01DD", // Ǝ / ǝ
  "A4DE", "025F", // ꓞ / ɟ
  "A4E8", "0253", // ꓨ / ɓ
  "0048", "0265", // H / ɥ
  "0049", "1D09", // I / ᴉ
  "017F", "017F", // ſ / ſ
  "A4D8", "029E", // ꓘ / ʞ
  "A4F6", "0E45", // ꓶ / ๅ
  "0057", "026F", // W / ɯ
  "004E", "0075", // N / u
  "004F", "006F", // O / o
  "A4D2", "0064", // ꓒ / d
  "1FF8", "0062", // Ὸ / b
  "A4E4", "0279", // ꓤ / ɹ
  "0053", "0073", // S / s
  "A4D5", "0287", // ꓕ / ʇ
  "A4F5", "006E", // ꓵ / n
  "A4E5", "028C", // ꓥ / ʌ
  "004D", "028D", // M / ʍ
  "0058", "0078", // X / x
  "2144", "028E", // ⅄ / ʎ
  "005A", "007A", // Z / z
  "\\ ", "\\ " // Space
};
char* ASCII_CODES[] = {
  // ಠ益ಠ
  "0CA0 76CA 0CA0", "0CA0 76CA 0CA0",
  // ¯\_(ツ)_/¯
  "00AF 005C 005F 0028 30C4 0029 005F 002F 00AF", "00AF 005C 005F 0028 30C4 0029 005F 002F 00AF",
  // (╯°□°）╯︵ ┻━┻) / (ヘ･_･)ヘ┳━┳
  "0028 256F 00B0 25A1 00B0 FF09 256F FE35 0020 253B 2501 253B", "0028 30D8 FF65 005F FF65 0029 30D8 2533 2501 2533",
  // ( ͡° ل͜ ͡° )
  "0028 0020 0361 00B0 0020 035C 0296 0020 0361 00B0 0029", "0028 0020 0361 00B0 0020 035C 0296 0020 0361 00B0 0029",
  // ಠ_ಠ
  "0ca0 005f 0ca0", "0ca0 005f 0ca0",
  // ᕕ( ᐛ  )ᕗ
  "1555 0028 0020 141b 0020 0029 1557", "1555 0028 0020 141b 0020 0029 1557",
  // ʕ•ᴥ•ʔ
  "0295 2022 1d25 2022 0294", "0295 2022 1d25 2022 0294",
  // /ᐠ｡‸｡ᐟ\_
  "0020 002f 1420 ff61 2038 ff61 141f 005c", "0020 002f 1420 ff61 2038 ff61 141f 005c",
  // ಥ_ಥ / (;´༎ຶД༎ຶ`)`)
  "0ca5 005f 0ca5", "0028 003b 00b4 0f0e 0eb6 0414 0f0e 0eb6 0060 0029",
  // \( ﾟヮﾟ)/
  "005c 0028 0020 ff9f 30ee ff9f 0029 002f", "005c 0028 0020 ff9f 30ee ff9f 0029 002f",
  // ಠ╭╮ಠ
  "0ca0 256d 256e 0ca0", "0ca0 256d 256e 0ca0",
};
char* SUPERSCRIPT_CODES[] = {
  "1D43", "1D43", // ᵃ
  "1D47", "1D47", // ᵇ
  "1D9C", "1D9C", // ᶜ
  "1D48", "1D48", // ᵈ
  "1D49", "1D49", // ᵉ
  "1DA0", "1DA0", // ᶠ
  "1D4D", "1D4D", // ᵍ
  "02B0", "02B0", // ʰ
  "2071", "2071", // ⁱ
  "02B2", "02B2", // ʲ
  "1D4F", "1D4F", // ᵏ
  "02E1", "02E1", // ˡ
  "1D50", "1D50", // ᵐ
  "207F", "207F", // ⁿ
  "1D52", "1D52", // ᵒ
  "1D56", "1D56", // ᵖ
  "02B3", "02B3", // ʳ
  "02E2", "02E2", // ˢ
  "1D57", "1D57", // ᵗ
  "1D58", "1D58", // ᵘ
  "1D5B", "1D5B", // ᵛ
  "02B7", "02B7", // ʷ
  "02E3", "02E3", // ˣ
  "02B8", "02B8", // ʸ
  "1DBB", "1DBB", // ᶻ
  "00B9", "00B9", // ¹
  "00B2", "00B2", // ²
  "00B3", "00B3", // ³
  "2074", "2074", // ⁴
  "2075", "2075", // ⁵
  "2076", "2076", // ⁶
  "2077", "2077", // ⁷
  "2078", "2078", // ⁸
  "2079", "207D", // ⁹ / ⁽
  "2070", "207E", // ⁰ / ⁾
  "207B", "207B", // ⁻
  "207C", "207A", // ⁺ / ⁼
  "22C5", "22C5", // ⋅
};

// Main Loop
enum PROCESS_RESULT {
  CONTINUE = 0,
  RETURN_TRUE = 1,
  RETURN_FALSE = 2,
};
enum PROCESS_RESULT process_record_user_REVERSE(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= REV_A && keycode <= REV_SPACE) {
    bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
    if (record->event.pressed) {
      char* code = REVERSE_CODES[(keycode - REV_A) * 2 + (shift_pressed ? 0 : 1)];
      if (shift_pressed) unregister_code(KC_LSHIFT);
      if (code[0] == '\\') {
        send_string(code + 1);
      } else {
        send_unicode_hex_string(code);
      }
      SEND_STRING(SS_TAP(X_LEFT));
      if (shift_pressed) register_code(KC_LSHIFT);
    }
    return RETURN_FALSE;
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_MAD(uint16_t keycode, keyrecord_t *record) {
  if (layer_state_is(_MAD) && keycode >= KC_A && keycode <= KC_Z) {
    if (record->event.pressed) {
      int uppercase = rand() % 2 == 0;
      if (uppercase) register_code(KC_LSHIFT);
      tap_code(keycode);
      if (uppercase) unregister_code(KC_LSHIFT);
    }
    return RETURN_FALSE;
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_SUPERSCRIPT(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= SUP_A && keycode <= SUP_DOT) {
    bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
    if (record->event.pressed) {
      char* code = SUPERSCRIPT_CODES[(keycode - SUP_A) * 2 + (shift_pressed ? 1 : 0)];
      send_unicode_hex_string(code);
    }
    return RETURN_FALSE;
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_ASCII(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= ANGRY && keycode <= NO) {
    bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
    if (record->event.pressed) {
      char* code = ASCII_CODES[(keycode - ANGRY) * 2 + (shift_pressed ? 1 : 0)];
      send_unicode_hex_string(code);
    }
    return RETURN_FALSE;
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_RGB(uint16_t keycode, keyrecord_t *record) {
  bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
  switch (keycode) {
    // RGB
    case RGB_STP:
      if (!record->event.pressed) {
        if (shift_pressed) {
          change_speed(1);
        } else {
          change_mode(1);
        }
      }
      return RETURN_FALSE;
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
      }
      return RETURN_TRUE;
    case DEC_COL:
      if (!record->event.pressed) {
        if (shift_pressed) { change_brightness(-1); } else { change_hue(-1); }
      }
      return RETURN_FALSE;
    case INC_COL:
      if (!record->event.pressed) {
        if (shift_pressed) { change_brightness(1); } else { change_hue(1); }
      }
      return RETURN_FALSE;
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_ACCENT(uint16_t keycode, keyrecord_t *record) {
  bool shift_pressed = (keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT));
  switch (keycode) {
    // Accent
    case ACCENT_LAYER:
      if (record->event.pressed) {
        layer_on(_ACCENT);
      } else {
        layer_off(_ACCENT);
        ALT_LETTER = '\0';
        ALT_MOD = -1;
      }
      return RETURN_FALSE;
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
  }
  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_ZALGO(uint16_t keycode, keyrecord_t *record) {
  if (layer_state_is(_ZALGO) ) {
    if (keycode < KC_A || ( keycode > KC_0 && keycode < KC_MINUS ) || keycode > KC_SLASH) {
      return CONTINUE;
    }

    if (record->event.pressed) {
      tap_code(keycode);

      int number_zalgo_mod = ( rand() % ( MAX_ZALGO_MOD + 1 - MIN_ZALGO_MOD ) ) + MIN_ZALGO_MOD;
      unicode_input_start();
      for (int index = 0; index < number_zalgo_mod; index++) {
        uint16_t hex = ( rand() % ( 0x036F + 1 - 0x0300 ) ) + 0x0300;
        register_hex(hex);
      }
      unicode_input_finish();

    }
    return RETURN_FALSE;
  }

  return CONTINUE;
}
enum PROCESS_RESULT process_record_user_OTHER(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CHANGE_OS:
      if (!record->event.pressed) {
        change_OS();
      }
      return RETURN_FALSE;
    case CYCLE_MAD_LAYERS:
      if (record->event.pressed) {
        layer_off(_REVERSE);
        layer_off(_SUPERSCRIPT);
        if (IS_LAYER_ON(_MAD)) {
          layer_off(_MAD);
          layer_on(_ZALGO);
        } else if (IS_LAYER_ON(_ZALGO)) {
          layer_off(_ZALGO);
        } else {
          layer_on(_MAD);
        }
        return RETURN_FALSE;
      }
    case CYCLE_UPPER_LAYERS:
      if (record->event.pressed) {
        layer_off(_MAD);
        layer_off(_ZALGO);
        if (IS_LAYER_ON(_SUPERSCRIPT)) {
          layer_off(_SUPERSCRIPT);
          layer_on(_REVERSE);
        } else if (IS_LAYER_ON(_REVERSE)) {
          layer_off(_REVERSE);
        } else {
          layer_on(_SUPERSCRIPT);
        }
        return RETURN_FALSE;
      }
  }
  return CONTINUE;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed && rgb_status == ONE_TIME_OFF) {
    rgb_status = ON;
    rgblight_enable_noeeprom();
    return false;
  }

  MATCH_OR_CONTINUE(process_record_user_ASCII(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_RGB(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_ACCENT(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_OTHER(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_SUPERSCRIPT(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_MAD(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_REVERSE(keycode, record));
  MATCH_OR_CONTINUE(process_record_user_ZALGO(keycode, record));

  return true;
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
   * |  Ctrl / Esc |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Enter      |
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
   * |  Ctrl / Esc |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   '   |      Enter      |
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

  /* ASCII Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |       |       |       |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |  WAT  |       |       |       |  YAY  |       |       |       |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |             | ANGRY |  SAD  |       | FLIP  |       | HAPPY |       |       | LENNY |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |  CAT  |       | BEAR  |       |  MEH  |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_ASCII] = LAYOUT_60_split_rshift_5x1u(
      ______, ______, ______, ______, ______    , ______, ______, ______, ______, ______, ______, ______, ______, ______,
      ______, ______, WAT   , ______, ______    , ______, YAY   , ______, ______, ______, ______, ______, ______, ______,
      ______, ANGRY , SAD   , ______, FLIP_TABLE, ______, HAPPY , ______, ______, LENNY , ______, ______, ______,
      ______, ______, ______, CAT   , ______    , BEAR  , NO    , MEH   , ______, ______, ______, ______, ______,
      ______, ______, ______, ______, ______    , ______, ______, ______, ______
      ),

  /* SUPERSCRIPT Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |   ¹   |   ²   |   ³   |   ⁴   |   ⁵   |   ⁶   |   ⁷   |   ⁸   |   ⁹   |   ⁰   |   ⁻   | ⁼ ⁺   |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |   ʷ   |   ᵉ   |   ʳ   |   ᵗ   |   ʸ   |   ᵘ   |   ⁱ   |   ᵒ   |   ᵖ   |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |  _DEFAULT   |   ᵃ   |   ˢ   |   ᵈ   |   ᶠ   |   ᵍ   |   ʰ   |   ʲ   |   ᵏ   |   ˡ   |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |   ᶻ   |   ˣ   |   ᶜ   |   ᵛ   |   ᵇ   |   ⁿ   |   ᵐ   |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_SUPERSCRIPT] = LAYOUT_60_split_rshift_5x1u(
      ______          , SUP_1 , SUP_2 , SUP_3 , SUP_4  , SUP_5 , SUP_6 , SUP_7 , SUP_8 , SUP_9  , SUP_0 , SUP_MIN , SUP_EQL, ______,
      ______          , ______, SUP_W , SUP_E , SUP_R  , SUP_T , SUP_Y , SUP_U , SUP_I , SUP_O  , SUP_P , ______  , ______ , ______,
      TG(_SUPERSCRIPT), SUP_A , SUP_S , SUP_D , SUP_F  , SUP_G , SUP_H , SUP_J , SUP_K , SUP_L  , ______, ______  , ______ ,
      ______          , SUP_Z , SUP_X , SUP_C , SUP_V  , SUP_B , SUP_N , SUP_M , ______, SUP_DOT, ______, ______  , ______ ,
      ______          , ______, ______, ______, ______ , ______, ______, ______, ______
      ),

  /* REVERSE Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |       |       |       |    KC_DEL     |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |  b/Ὸ  |  ʍ/M  |  ǝ/Ǝ  |  ɹ/ꓤ  |  ʇ/ꓕ  |  ʎ/⅄  |  n/ꓵ  |  ᴉ/I  |  o/O  |  d/ꓒ  |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |  _DEFAULT   |  ɐ/Ɐ  |  s/S  |  p/ꓷ  |  ɟ/ꓞ  |  ɓ/ꓨ  |  ɥ/H  |  ſ/ſ  |  ʞ/ꓘ  |  ๅ/ꓶ  |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |  z/Z  |  x/X  |  ɔ/ꓛ  |  ʌ/ꓥ  |  q/ꓭ  |  u/N  |  ɯ/W  |       |       |       |             | BSPC  |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |           "Backward Space"                      |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_REVERSE] = LAYOUT_60_split_rshift_5x1u(
      ______      , ______ , ______ , ______   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_DEL,
      ______      , REV_Q  , REV_W  , REV_E    , REV_R  , REV_T  , REV_Y  , REV_U  , REV_I  , REV_O  , REV_P  , ______ , ______ , ______,
      TG(_REVERSE), REV_A  , REV_S  , REV_D    , REV_F  , REV_G  , REV_H  , REV_J  , REV_K  , REV_L  , ______ , ______ , ______ ,
      ______      , REV_Z  , REV_X  , REV_C    , REV_V  , REV_B  , REV_N  , REV_M  , ______ , ______ , ______ , ______ , KC_BSPC,
      ______      , ______ , ______ , REV_SPACE, ______ , ______ , ______ , ______ , ______
      ),

  /* MAD Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |       |       |       |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       |       |       |       |       |       |       |       |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |  _DEFAULT   |       |       |       |       |       |       |       |       |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |       |       |       |       |       |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_MAD] = LAYOUT_60_split_rshift_5x1u(
      ______  , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ , ______,
      ______  , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ , ______,
      TG(_MAD), ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ ,
      ______  , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ ,
      ______  , ______, ______, ______, ______ , ______, ______, ______, ______
      ),

  /* ZALGO Layer
   * ,-----------------------------------------------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |       |       |       |               |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |           |       |       |       |       |       |       |       |       |       |       |       |       |           |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |   _DEFAULT  |       |       |       |       |       |       |       |       |       |       |       |                 |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |                 |       |       |       |       |       |       |       |       |       |       |             |       |
   * |-----------------------------------------------------------------------------------------------------------------------+
   * |         |         |         |                                                 |       |       |       |       |       |
   * `-----------------------------------------------------------------------------------------------------------------------'
   */

  [_ZALGO] = LAYOUT_60_split_rshift_5x1u(
      ______    , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ , ______,
      ______    , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ , ______,
      TG(_ZALGO), ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ ,
      ______    , ______, ______, ______, ______ , ______, ______, ______, ______, ______ , ______, ______ , ______ ,
      ______    , ______, ______, ______, ______ , ______, ______, ______, ______
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
        REG_GRV          ,______,______,______     ,______,______,REG_CIR,______,______ ,______,______ ,______             ,______ ,______,
        ______           ,______,______,REG_E      ,______,______,REG_Y  ,REG_U ,REG_I  ,REG_O ,______ ,______             ,______ ,______,
        CYCLE_MAD_LAYERS ,REG_A ,______,______     ,______,______,______ ,______,______ ,______,REG_TRM,REG_ACU            ,______ ,
        ______           ,______,______,REG_C      ,______,______,REG_N  ,______,REG_CED,______,______ ,CYCLE_UPPER_LAYERS ,______ ,
        ______           ,______,______,OSL(_ASCII),______,______,______ ,______,______
      ),
};
