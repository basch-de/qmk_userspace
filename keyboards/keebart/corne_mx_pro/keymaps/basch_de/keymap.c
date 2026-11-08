// SPDX-License-Identifier: GPL-2.0-or-later
// Key positions ported from basch-de/zmk-config, see docs/PROJECT.md.
#include QMK_KEYBOARD_H
#include "keymap_defs.h"

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
 * | NO | LSFT(LGUI(KC_O)) | LSFT(LGUI(KC_M)) | LSFT(LGUI(KC_K)) |           NO           | LSFT(LGUI(KC_H)) |         |  NO  | KC_ASST | LCTL(LGUI(KC_SPC)) |    NO   | NO |        NO        |
 *                                            |       TRNS       |          TRNS          |       TRNS       |         | TRNS |   TRNS  |        TRNS        |
 */
[_SHORT] = LAYOUT_split_3x6_3_ex2(
    KC_NO,  KC_NO,             KC_NO,             KC_NO,             KC_NO,                   KC_NO,             KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,               KC_NO,    KC_NO,  LCTL(LGUI(KC_Q)),
    KC_NO,  KC_NO,             KC_NO,             LSFT(LGUI(KC_4)),  LCTL(LSFT(LGUI(KC_4))),  KC_NO,             KC_NO,  KC_NO,  KC_NO,    KC_VOLD,  KC_MUTE,             KC_VOLU,  KC_NO,  KC_NO,
    KC_NO,  LSFT(LGUI(KC_O)),  LSFT(LGUI(KC_M)),  LSFT(LGUI(KC_K)),  KC_NO,                   LSFT(LGUI(KC_H)),                  KC_NO,    KC_ASST,  LCTL(LGUI(KC_SPC)),  KC_NO,    KC_NO,  KC_NO,
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
 * |   NO   |    NO   |   NO   | NO | NO | NO | NO | NO |    NO   |    NO   |    NO   |    NO   |    NO   | KC_PWR  |
 * |   NO   |    NO   |   NO   | NO | NO | NO | NO | NO | RM_HUED | RM_HUEU | RM_SATD | RM_SATU | RM_VALD | RM_VALU |
 * | QK_RBT | QK_BOOT | EE_CLR | NO | NO | NO |         | RM_TOGG | RM_NEXT |    NO   |  EE_CLR | QK_BOOT |  QK_RBT |
 *                             | NO | NO | NO |         |    NO   |    NO   |    NO   |
 */
[_SYS] = LAYOUT_split_3x6_3_ex2(
    KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_PWR,
    KC_NO,   KC_NO,    KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  RM_HUED,  RM_HUEU,  RM_SATD,  RM_SATU,  RM_VALD,  RM_VALU,
    QK_RBT,  QK_BOOT,  EE_CLR,  KC_NO,  KC_NO,  KC_NO,                  RM_TOGG,  RM_NEXT,  KC_NO,    EE_CLR,   QK_BOOT,  QK_RBT,
                                KC_NO,  KC_NO,  KC_NO,                  KC_NO,    KC_NO,    KC_NO
),
};

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
