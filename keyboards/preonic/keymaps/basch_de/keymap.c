/* Copyright 2015-2021 Jack Humbert
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

enum preonic_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _WINDOW
};

enum preonic_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  BACKLIT
};

//#define QWERTY PDF(_QWERTY)

// KC_NO ist der Tap-Platzhalter; case CTL_SPOT in process_record_user() sendet
// beim Tippen Cmd+Space. Beim Halten liefert LCTL_T weiterhin linken Ctrl.
#define CTL_SPOT LCTL_T(KC_NO)

// KC_NO ist der Tap-Platzhalter; case WIN_BSP in process_record_user() sendet
// beim Tippen Option+Backspace. Beim Halten aktiviert LT den WINDOW-Layer.
#define WIN_BSP LT(_WINDOW, KC_NO)

/* Diagramm-Legende: Tap/Hold zeigt Tippen/Halten, TRNS ist transparent.
 * LCmd/RCmd entsprechen den GUI-Modifiern unter macOS.
 * Hyper ist linker Ctrl+Alt+Cmd+Shift; Spotlight sendet Cmd+Space.
 * Sticky Shift gilt nach dem Tippen fuer die naechste Taste, gehalten als Shift.
 * Symbolbeschriftungen benennen QMK-Keycodes, nicht verifizierte EurKEY-next-Ausgaben.
 * NUHS/NUBS sind die ISO-Keycodes, S(...) bezeichnet Shift.
 * Alle fuenf Reihen haben zwoelf einzelne 1u-Tasten.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 * |        `        |  1   |  2  |  3  |     4      |   5   |        6        |      7      |  8   |  9   |  0  |     -     |
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 * |    Tab/Hyper    |  Q   |  W  |  E  |     R      |   T   |        Y        |      U      |  I   |  O   |  P  | Backslash |
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 * |     Esc/LCmd    |  A   |  S  |  D  |     F      |   G   |        H        |      J      |  K   |  L   |  ;  |   '/RAlt  |
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 * |   Sticky Shift  |  Z   |  X  |  C  |     V      |   B   |        N        |      M      |  ,   |  .   |  /  |  =/RShift |
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 * | Spotlight/LCtrl | LAlt |  [  |  ]  | Bksp/Lower | Enter | Opt-Bksp/Window | Space/Raise | Left | Down |  Up |   Right   |
 * +-----------------+------+-----+-----+------------+-------+-----------------+-------------+------+------+-----+-----------+
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,          KC_1,     KC_2,     KC_3,     KC_4,                 KC_5,    KC_6,     KC_7,                KC_8,     KC_9,     KC_0,     KC_MINS,
  HYPR_T(KC_TAB),  KC_Q,     KC_W,     KC_E,     KC_R,                 KC_T,    KC_Y,     KC_U,                KC_I,     KC_O,     KC_P,     KC_BSLS,
  LGUI_T(KC_ESC),  KC_A,     KC_S,     KC_D,     KC_F,                 KC_G,    KC_H,     KC_J,                KC_K,     KC_L,     KC_SCLN,  RALT_T(KC_QUOT),
  OSM(MOD_LSFT),   KC_Z,     KC_X,     KC_C,     KC_V,                 KC_B,    KC_N,     KC_M,                KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_EQL),
  CTL_SPOT,        KC_LALT,  KC_LBRC,  KC_RBRC,  LT(_LOWER, KC_BSPC),  KC_ENT,  WIN_BSP,  LT(_RAISE, KC_SPC),  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT
),

/* Gaming (vorerst transparent; noch keine Umschalttaste)
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 */
[_GAMING] = LAYOUT_preonic_grid(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

/* Lower
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 * |  ~   |  !   |  @   |  #   |  $   |  %   |  ^   |    &    |    *    |  (   |  )   | Bksp |
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 * |  ~   |  !   |  @   |  #   |  $   |  %   |  ^   |    &    |    *    |  (   |  )   | Del  |
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |    _    |    +    |  {   |  }   | Pipe |
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 * | TRNS |  F7  |  F8  |  F9  | F10  | F11  | F12  | S(NUHS) | S(NUBS) | Home | End  | TRNS |
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |   TRNS  |   Next  | Vol- | Vol+ | Play |
 * +------+------+------+------+------+------+------+---------+---------+------+------+------+
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,     KC_ASTR,     KC_LPRN,  KC_RPRN,  KC_BSPC,
  KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,     KC_ASTR,     KC_LPRN,  KC_RPRN,  KC_DEL,
  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_UNDS,     KC_PLUS,     KC_LCBR,  KC_RCBR,  KC_PIPE,
  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   S(KC_NUHS),  S(KC_NUBS),  KC_HOME,  KC_END,   _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     KC_MNXT,     KC_VOLD,  KC_VOLU,  KC_MPLY
),

/* Raise
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 * |  `   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |    Bksp   |
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 * |  `   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |    Del    |
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  -   |  =   |  [   |  ]   | Backslash |
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 * | TRNS |  F7  |  F8  |  F9  | F10  | F11  | F12  | NUHS | NUBS | PgUp | PgDn |    TRNS   |
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | Next | Vol- | Vol+ |    Play   |
 * +------+------+------+------+------+------+------+------+------+------+------+-----------+
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
  KC_DEL,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NUHS,  KC_NUBS,  KC_PGUP,  KC_PGDN,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
),

/* Adjust (Lower + Raise)
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 * |     F1    |    F2   |    F3   |   F4  |   F5   |    F6   |    F7   |  F8  |  F9  | F10  | F11  | F12  |
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 * | QK_REBOOT | QK_BOOT | DB_TOGG |  TRNS |  TRNS  |   TRNS  |   TRNS  | TRNS | TRNS | TRNS | TRNS | Del  |
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 * |  RM_TOGG  |   TRNS  | MU_NEXT | AU_ON | AU_OFF | AG_NORM | AG_SWAP | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 * |  UG_TOGG  | AU_PREV | AU_NEXT | MU_ON | MU_OFF |  MI_ON  |  MI_OFF | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 * |  BACKLIT  |   TRNS  |   TRNS  |  TRNS |  TRNS  |   TRNS  |   TRNS  | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +-----------+---------+---------+-------+--------+---------+---------+------+------+------+------+------+
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
  QK_REBOOT,  QK_BOOT,  DB_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_DEL,
  RM_TOGG,    _______,  MU_NEXT,  AU_ON,    AU_OFF,   AG_NORM,  AG_SWAP,  _______,  _______,  _______,  _______,  _______,
  UG_TOGG,    AU_PREV,  AU_NEXT,  MU_ON,    MU_OFF,   MI_ON,    MI_OFF,   _______,  _______,  _______,  _______,  _______,
  BACKLIT,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

/* Window (vorerst transparent; Opt-Bksp halten)
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 */
[_WINDOW] = LAYOUT_preonic_grid(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case CTL_SPOT:
          if (record->tap.count) {
            if (record->event.pressed) {
              tap_code16(LGUI(KC_SPC));
            }
            return false;
          }
          break;
        case WIN_BSP:
          if (record->tap.count) {
            if (record->event.pressed) {
              tap_code16(LALT(KC_BSPC));
            }
            return false;
          }
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            gpio_write_pin_low(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            gpio_write_pin_high(E6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
