// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM 200
#define QUICK_TAP_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define CHORDAL_HOLD

// ZMK v0.3 Caps Word has no idle timeout.
#define CAPS_WORD_IDLE_TIMEOUT 0

// Match the source's five-minute lighting idle timeout, not its wireless sleep.
#define RGB_MATRIX_TIMEOUT 300000

// Source defaults: hue 200 degrees, saturation 98%, brightness 20%.
// Keep the manufacturer's maximum brightness of 100/255.
#undef RGB_MATRIX_DEFAULT_HUE
#define RGB_MATRIX_DEFAULT_HUE 142
#undef RGB_MATRIX_DEFAULT_SAT
#define RGB_MATRIX_DEFAULT_SAT 250
#undef RGB_MATRIX_DEFAULT_VAL
#define RGB_MATRIX_DEFAULT_VAL 51
#define RGB_MATRIX_VAL_STEP 13
