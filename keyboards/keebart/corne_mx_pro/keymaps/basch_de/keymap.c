// SPDX-License-Identifier: GPL-2.0-or-later
// Key positions ported from basch-de/zmk-config, see docs/corne-mainline.md.
#include QMK_KEYBOARD_H

enum corne_layers {
    _MACOS,
    _NUM,
    _SYM,
    _NAV,
    _WIN,
    _SHORT,
    _NUMPAD,
    _SYS
};

#define SYS_GRV   LT(_SYS, KC_GRV)
#define NAV_ESC   LT(_NAV, KC_ESC)
#define NUM_BSPC  LT(_NUM, KC_BSPC)
#define WIN_TAB   LT(_WIN, KC_TAB)
#define PAD_ENT   LT(_NUMPAD, KC_ENT)
#define SYM_SPC   LT(_SYM, KC_SPC)
#define SHORT_EQL LT(_SHORT, KC_EQL)

// QMK resolves tap/hold; process_record_user() only replaces these actions.
#define SHORT_CW  LT(_SHORT, KC_NO)
#define HYP_SPOT  HYPR_T(KC_NO)
#define COMM_DOT  LT(_MACOS, KC_COMM)

/* Diagram legend:
 * LT(layer, key) and all *_T(key) expressions mean Tap key / Hold layer or mods.
 * SYS_GRV: KC_GRV/SYS; NAV_ESC: KC_ESC/NAV; NUM_BSPC: KC_BSPC/NUM.
 * WIN_TAB: KC_TAB/WIN; PAD_ENT: KC_ENT/NUMPAD; SYM_SPC: KC_SPC/SYM.
 * SHORT_EQL: KC_EQL/SHORT; SHORT_CW: Caps Word toggle/SHORT.
 * HYP_SPOT: Cmd+Space/left Ctrl+Alt+Cmd+Shift; MEH_T: left Ctrl+Alt+Shift.
 * COMM_DOT: KC_COMM/KC_DOT; TG toggles a layer; TRNS is transparent; NO is disabled.
 * Labels describe QMK keycodes, not verified EurKEY-next output characters.
 * Each layer has 14 + 14 + 12 + 6 positions, including four inner extra keys.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* macos
 * |  SYS_GRV  |     KC_Q     |     KC_W     |     KC_E     |     KC_R     |   KC_T  | NO | NO |   KC_Y  |     KC_U     |     KC_I     |     KC_O     |       KC_P      |    KC_BSLS     |
 * |  HYP_SPOT | LCTL_T(KC_A) | LGUI_T(KC_S) | LALT_T(KC_D) | LSFT_T(KC_F) |   KC_G  | NO | NO |   KC_H  | RSFT_T(KC_J) | RALT_T(KC_K) | RGUI_T(KC_L) | RCTL_T(KC_SCLN) | MEH_T(KC_QUOT) |
 * | SHORT_EQL |     KC_Z     |     KC_X     |     KC_C     |     KC_V     |   KC_B  |         |   KC_N  |     KC_M     |   KC_COMM    |    KC_DOT    |     KC_SLSH     |    KC_MINS     |
 *                                           |   NAV_ESC    |   NUM_BSPC   | WIN_TAB |         | PAD_ENT |   SYM_SPC    |   SHORT_CW   |
 */
[_MACOS] = LAYOUT_split_3x6_3_ex2(
    SYS_GRV,    KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,     KC_NO,  KC_NO,  KC_Y,     KC_U,          KC_I,          KC_O,          KC_P,             KC_BSLS,
    HYP_SPOT,   LCTL_T(KC_A),  LGUI_T(KC_S),  LALT_T(KC_D),  LSFT_T(KC_F),  KC_G,     KC_NO,  KC_NO,  KC_H,     RSFT_T(KC_J),  RALT_T(KC_K),  RGUI_T(KC_L),  RCTL_T(KC_SCLN),  MEH_T(KC_QUOT),
    SHORT_EQL,  KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                     KC_N,     KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,          KC_MINS,
                                              NAV_ESC,       NUM_BSPC,      WIN_TAB,                  PAD_ENT,  SYM_SPC,       SHORT_CW
),

/* num
 * | KC_COMM |   KC_1  |   KC_2  |   KC_3  |   KC_4  |   KC_5  | NO | NO |   KC_6  |   KC_7  |   KC_8  |  KC_9 |   KC_0  | KC_BSPC |
 * | KC_SLSH | KC_LCTL | KC_LGUI | KC_LALT | KC_LSFT | KC_MINS | NO | NO | KC_COLN | KC_LEFT | KC_DOWN | KC_UP | KC_RGHT |  KC_DOT |
 * |  KC_F12 |  KC_F1  |  KC_F2  |  KC_F3  |  KC_F4  |  KC_F5  |         |  KC_F6  |  KC_F7  |  KC_F8  | KC_F9 |  KC_F10 |  KC_F11 |
 *                               |   TRNS  |   TRNS  |   TRNS  |         |   TRNS  |   TRNS  |   TRNS  |
 */
[_NUM] = LAYOUT_split_3x6_3_ex2(
    KC_COMM,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_NO,  KC_NO,  KC_6,     KC_7,     KC_8,     KC_9,   KC_0,     KC_BSPC,
    KC_SLSH,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_MINS,  KC_NO,  KC_NO,  KC_COLN,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RGHT,  KC_DOT,
    KC_F12,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                    KC_F6,    KC_F7,    KC_F8,    KC_F9,  KC_F10,   KC_F11,
                                  _______,  _______,  _______,                  _______,  _______,  _______
),

/* sym
 * |  KC_GRV | KC_EXLM |  KC_AT  | KC_HASH |  KC_DLR |   KC_PERC   | NO | NO | KC_CIRC | KC_AMPR | KC_ASTR | KC_LPRN | KC_RPRN | KC_BSPC |
 * | KC_TILD | KC_LCTL | KC_LGUI | KC_LALT | KC_LSFT |      NO     | NO | NO | KC_MINS | KC_SLSH | KC_LBRC | KC_RBRC | KC_BSLS |  KC_EQL |
 * |    NO   |    NO   |    NO   |    NO   |    NO   | TG(_NUMPAD) |         | KC_UNDS | KC_QUES | KC_LCBR | KC_RCBR | KC_PIPE | KC_PLUS |
 *                               |   TRNS  |   TRNS  |     TRNS    |         |   TRNS  |   TRNS  |   TRNS  |
 */
[_SYM] = LAYOUT_split_3x6_3_ex2(
    KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,      KC_NO,  KC_NO,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
    KC_TILD,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_NO,        KC_NO,  KC_NO,  KC_MINS,  KC_SLSH,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_EQL,
    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TG(_NUMPAD),                  KC_UNDS,  KC_QUES,  KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_PLUS,
                                  _______,  _______,  _______,                      _______,  _______,  _______
),

/* nav
 * |        NO        | LGUI(KC_W) | LALT(LGUI(KC_LEFT)) | LGUI(KC_T) | LALT(LGUI(KC_RGHT)) |   NO   | NO | NO |  KC_PGUP   |    LGUI(KC_LEFT)    | LGUI(KC_RGHT) |       NO      |          NO         |  KC_DEL |
 * |        NO        |  KC_LCTL   |       KC_LGUI       |  KC_LALT   |       KC_LSFT       |   NO   | NO | NO |  KC_PGDN   |       KC_LEFT       |    KC_DOWN    |     KC_UP     |       KC_RGHT       | KC_BSPC |
 * | LSFT(LGUI(KC_Z)) | LGUI(KC_Z) |      LGUI(KC_X)     | LGUI(KC_C) |      LGUI(KC_V)     | KC_SPC |         | LGUI(KC_A) | LSFT(LALT(KC_LEFT)) | LALT(KC_LEFT) | LALT(KC_RGHT) | LSFT(LALT(KC_RGHT)) |    NO   |
 *                                                       |    TRNS    |         TRNS        |  TRNS  |         |    TRNS    |         TRNS        |      TRNS     |
 */
[_NAV] = LAYOUT_split_3x6_3_ex2(
    KC_NO,             LGUI(KC_W),  LALT(LGUI(KC_LEFT)),  LGUI(KC_T),  LALT(LGUI(KC_RGHT)),  KC_NO,    KC_NO,  KC_NO,  KC_PGUP,     LGUI(KC_LEFT),        LGUI(KC_RGHT),  KC_NO,          KC_NO,                KC_DEL,
    KC_NO,             KC_LCTL,     KC_LGUI,              KC_LALT,     KC_LSFT,              KC_NO,    KC_NO,  KC_NO,  KC_PGDN,     KC_LEFT,              KC_DOWN,        KC_UP,          KC_RGHT,              KC_BSPC,
    LSFT(LGUI(KC_Z)),  LGUI(KC_Z),  LGUI(KC_X),           LGUI(KC_C),  LGUI(KC_V),           KC_SPC,                   LGUI(KC_A),  LSFT(LALT(KC_LEFT)),  LALT(KC_LEFT),  LALT(KC_RGHT),  LSFT(LALT(KC_RGHT)),  KC_NO,
                                                          _______,     _______,              _______,                  _______,     _______,              _______
),

/* win
 * | NO |   LCTL(LALT(KC_D))  |   LCTL(LALT(KC_F))  |  LCTL(LALT(KC_G)) |   LCTL(LALT(KC_U))  |  LCTL(LALT(KC_I))  | NO | NO |  LCTL(LALT(KC_U))  |   LCTL(LALT(KC_I))  |   LCTL(LALT(KC_D))  |  LCTL(LALT(KC_F)) |   LCTL(LALT(KC_G))  | NO |
 * | NO | LCTL(LALT(KC_LEFT)) | LCTL(LALT(KC_DOWN)) | LCTL(LALT(KC_UP)) | LCTL(LALT(KC_RGHT)) | LCTL(LALT(KC_ENT)) | NO | NO | LCTL(LALT(KC_ENT)) | LCTL(LALT(KC_LEFT)) | LCTL(LALT(KC_DOWN)) | LCTL(LALT(KC_UP)) | LCTL(LALT(KC_RGHT)) | NO |
 * | NO |   LCTL(LALT(KC_E))  |   LCTL(LALT(KC_R))  |  LCTL(LALT(KC_T)) |   LCTL(LALT(KC_J))  |  LCTL(LALT(KC_K))  |         |  LCTL(LALT(KC_J))  |   LCTL(LALT(KC_K))  |   LCTL(LALT(KC_E))  |  LCTL(LALT(KC_R)) |   LCTL(LALT(KC_T))  | NO |
 *                                                  |        TRNS       |         TRNS        |        TRNS        |         |        TRNS        |         TRNS        |         TRNS        |
 */
[_WIN] = LAYOUT_split_3x6_3_ex2(
    KC_NO,  LCTL(LALT(KC_D)),     LCTL(LALT(KC_F)),     LCTL(LALT(KC_G)),   LCTL(LALT(KC_U)),     LCTL(LALT(KC_I)),    KC_NO,  KC_NO,  LCTL(LALT(KC_U)),    LCTL(LALT(KC_I)),     LCTL(LALT(KC_D)),     LCTL(LALT(KC_F)),   LCTL(LALT(KC_G)),     KC_NO,
    KC_NO,  LCTL(LALT(KC_LEFT)),  LCTL(LALT(KC_DOWN)),  LCTL(LALT(KC_UP)),  LCTL(LALT(KC_RGHT)),  LCTL(LALT(KC_ENT)),  KC_NO,  KC_NO,  LCTL(LALT(KC_ENT)),  LCTL(LALT(KC_LEFT)),  LCTL(LALT(KC_DOWN)),  LCTL(LALT(KC_UP)),  LCTL(LALT(KC_RGHT)),  KC_NO,
    KC_NO,  LCTL(LALT(KC_E)),     LCTL(LALT(KC_R)),     LCTL(LALT(KC_T)),   LCTL(LALT(KC_J)),     LCTL(LALT(KC_K)),                    LCTL(LALT(KC_J)),    LCTL(LALT(KC_K)),     LCTL(LALT(KC_E)),     LCTL(LALT(KC_R)),   LCTL(LALT(KC_T)),     KC_NO,
                                                        _______,            _______,              _______,                             _______,             _______,              _______
),

/* short
 * | NO |        NO        |        NO        |        NO        |           NO           |        NO        | NO | NO |  NO  |    NO   |         NO         |    NO   | NO | LCTL(LGUI(KC_Q)) |
 * | NO |        NO        |        NO        | LSFT(LGUI(KC_4)) | LCTL(LSFT(LGUI(KC_4))) |        NO        | NO | NO |  NO  | KC_VOLD |      KC_MUTE       | KC_VOLU | NO |        NO        |
 * | NO | LSFT(LGUI(KC_O)) | LSFT(LGUI(KC_M)) | LSFT(LGUI(KC_K)) |           NO           | LSFT(LGUI(KC_H)) |         |  NO  |    NO   | LCTL(LGUI(KC_SPC)) |    NO   | NO |        NO        |
 *                                            |       TRNS       |          TRNS          |       TRNS       |         | TRNS |   TRNS  |        TRNS        |
 */
[_SHORT] = LAYOUT_split_3x6_3_ex2(
    KC_NO,  KC_NO,             KC_NO,             KC_NO,             KC_NO,                   KC_NO,             KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,  LCTL(LGUI(KC_Q)),
    KC_NO,  KC_NO,             KC_NO,             LSFT(LGUI(KC_4)),  LCTL(LSFT(LGUI(KC_4))),  KC_NO,             KC_NO,  KC_NO,  KC_NO,    KC_VOLD,  KC_MUTE,             KC_VOLU,  KC_NO,  KC_NO,
    KC_NO,  LSFT(LGUI(KC_O)),  LSFT(LGUI(KC_M)),  LSFT(LGUI(KC_K)),  KC_NO,                   LSFT(LGUI(KC_H)),                  KC_NO,    KC_NO,    LCTL(LGUI(KC_SPC)),  KC_NO,    KC_NO,  KC_NO,
                                                  _______,           _______,                 _______,                           _______,  _______,  _______
),

/* numpad
 * | NO |    NO   |    NO   |    NO   |    NO   |      NO     | NO | NO | KC_SLSH | KC_7 | KC_8 | KC_9 | KC_MINS  |  KC_EQL |
 * | NO | KC_LCTL | KC_LGUI | KC_LALT | KC_LSFT |      NO     | NO | NO | KC_ASTR | KC_4 | KC_5 | KC_6 | KC_PLUS  |  KC_ENT |
 * | NO |    NO   |    NO   |    NO   |    NO   | TG(_NUMPAD) |         |   KC_0  | KC_1 | KC_2 | KC_3 | COMM_DOT | KC_COLN |
 *                          |   TRNS  |   TRNS  |     TRNS    |         |   TRNS  | TRNS | TRNS |
 */
[_NUMPAD] = LAYOUT_split_3x6_3_ex2(
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_NO,  KC_NO,  KC_SLSH,  KC_7,     KC_8,     KC_9,  KC_MINS,   KC_EQL,
    KC_NO,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_NO,        KC_NO,  KC_NO,  KC_ASTR,  KC_4,     KC_5,     KC_6,  KC_PLUS,   KC_ENT,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    TG(_NUMPAD),                  KC_0,     KC_1,     KC_2,     KC_3,  COMM_DOT,  KC_COLN,
                                _______,  _______,  _______,                      _______,  _______,  _______
),

/* sys
 * |   NO   |    NO   |   NO   | NO | NO | NO | NO | NO |    NO   |    NO   |    NO   |    NO   |    NO   |    NO   |
 * |   NO   |    NO   |   NO   | NO | NO | NO | NO | NO | RM_HUED | RM_HUEU | RM_SATD | RM_SATU | RM_VALD | RM_VALU |
 * | QK_RBT | QK_BOOT | EE_CLR | NO | NO | NO |         | RM_TOGG | RM_NEXT |    NO   |  EE_CLR | QK_BOOT |  QK_RBT |
 *                             | NO | NO | NO |         |    NO   |    NO   |    NO   |
 */
[_SYS] = LAYOUT_split_3x6_3_ex2(
    KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  RM_HUED,  RM_HUEU,  RM_SATD,  RM_SATU,  RM_VALD,  RM_VALU,
    QK_RBT,  QK_BOOT,  EE_CLR,  KC_NO,  KC_NO,  KC_NO,                  RM_TOGG,  RM_NEXT,  KC_NO,    EE_CLR,   QK_BOOT,  QK_RBT,
                                KC_NO,  KC_NO,  KC_NO,                  KC_NO,    KC_NO,    KC_NO
),
};

static bool is_home_row_mod(uint16_t keycode) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case LGUI_T(KC_S):
        case LALT_T(KC_D):
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case RALT_T(KC_K):
        case RGUI_T(KC_L):
        case RCTL_T(KC_SCLN):
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (is_home_row_mod(keycode)) {
        return 240;
    }
    switch (keycode) {
        case PAD_ENT:
            return 220;
        case SYS_GRV:
        case NAV_ESC:
        case NUM_BSPC:
        case WIN_TAB:
        case SYM_SPC:
        case SHORT_CW:
        case SHORT_EQL:
            return 180;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (is_home_row_mod(keycode)) {
        return 160;
    }
    switch (keycode) {
        case WIN_TAB:
            return 160;
        case PAD_ENT:
            return 200;
        default:
            return 0;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    // ZMK balanced: settle a hold on a nested press/release, not a roll.
    return is_home_row_mod(keycode);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    switch (keycode) {
        case SYS_GRV:
        case NAV_ESC:
        case NUM_BSPC:
        case WIN_TAB:
        case SYM_SPC:
        case SHORT_CW:
        case HYP_SPOT:
        case MEH_T(KC_QUOT):
        case COMM_DOT:
            return true;
        default:
            return false;
    }
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x6_3_ex2(
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',           '*', '*', '*'
    );

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
    (void)other_keycode;
    // Apply handedness only to HRMs; layer taps and outer mod-taps remain usable
    // with either hand. '*' thumbs can trigger HRM holds from either hand.
    if (!is_home_row_mod(tap_hold_keycode)) {
        return true;
    }
    // The four inner extra keys are absent from ZMK's HRM trigger lists.
    if (other_record->event.key.col == 6) {
        return false;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HYP_SPOT:
            if (record->tap.count) {
                if (record->event.pressed) {
                    caps_word_off();
                    tap_code16(LGUI(KC_SPC));
                }
                return false;
            }
            break;
        case SHORT_CW:
            if (record->tap.count) {
                if (record->event.pressed) {
                    caps_word_toggle();
                }
                return false;
            }
            break;
        case COMM_DOT:
            if (!record->tap.count) {
                // Preserve a held dot, including host repeat; QMK owns timing.
                if (record->event.pressed) {
                    caps_word_off();
                    register_code(KC_DOT);
                } else {
                    unregister_code(KC_DOT);
                }
                return false;
            }
            break;
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_LSFT:
        case KC_RSFT:
            return true;
        case KC_MINS:
            // ZMK continues an underscore, but a plain hyphen ends the word.
            return (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
        default:
            return false;
    }
}

// Retain the manufacturer's four encoder actions on every personal layer.
#define CORNE_ENCODERS { ENCODER_CCW_CW(RM_NEXT, RM_PREV), \
                         ENCODER_CCW_CW(RM_HUEU, RM_HUED), \
                         ENCODER_CCW_CW(RM_VALU, RM_VALD), \
                         ENCODER_CCW_CW(RM_SATU, RM_SATD) }

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MACOS]  = CORNE_ENCODERS,
    [_NUM]    = CORNE_ENCODERS,
    [_SYM]    = CORNE_ENCODERS,
    [_NAV]    = CORNE_ENCODERS,
    [_WIN]    = CORNE_ENCODERS,
    [_SHORT]  = CORNE_ENCODERS,
    [_NUMPAD] = CORNE_ENCODERS,
    [_SYS]    = CORNE_ENCODERS,
};
