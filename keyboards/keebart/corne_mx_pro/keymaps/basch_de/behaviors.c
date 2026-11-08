// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "keymap_defs.h"

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
        case S(KC_1) ... S(KC_0):
        case KC_NO:
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
