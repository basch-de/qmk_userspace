// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

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
