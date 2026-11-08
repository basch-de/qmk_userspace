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

#pragma once

enum preonic_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _WINDOW
};

// KC_NO is the tap placeholder; case CTL_SPOT in process_record_user() sends
// Cmd+Space on tap. LCTL_T provides left Ctrl while held.
#define CTL_SPOT LCTL_T(KC_NO)

// KC_NO is the tap placeholder; case WIN_BSP in process_record_user() sends
// Option+Backspace on tap. LT activates the WINDOW layer while held.
#define WIN_BSP LT(_WINDOW, KC_NO)
