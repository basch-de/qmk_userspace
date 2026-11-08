// SPDX-License-Identifier: GPL-2.0-or-later
#include "fixture.hpp"

class Preonic : public UserspaceTest {};
enum { QWERTY, GAMING, LOWER, RAISE, ADJUST, WINDOW };

TEST_F(Preonic, StructureAndProtectedBootAccess) {
    check_structure();
    // Check actual bottom-row access independently of logical matrix ordering.
    EXPECT_EQ(code(52), LT(LOWER, KC_BSPC));
    EXPECT_EQ(code(55), LT(RAISE, KC_SPC));
    EXPECT_EQ(code(13, ADJUST), QK_BOOT);
    EXPECT_EQ(code(12, ADJUST), QK_REBOOT);
}

TEST_F(Preonic, LowerRaiseActivateAdjustAndReleaseCleanly) {
    press(52); idle_for(term(52) + 10);
    EXPECT_TRUE(layer_state_is(LOWER));
    press(55); idle_for(term(55) + 10);
    EXPECT_TRUE(layer_state_is(ADJUST));
    release(55);
    EXPECT_FALSE(layer_state_is(ADJUST));
    EXPECT_TRUE(layer_state_is(LOWER));
    release(52);
    EXPECT_EQ(layer_state, 0u);
}

TEST_F(Preonic, GamingToggleRemainsReachable) {
    layer_on(LOWER); layer_on(RAISE);
    ASSERT_TRUE(layer_state_is(ADJUST));
    tap(59);
    EXPECT_TRUE(layer_state_is(GAMING));
    layer_off(LOWER); layer_off(RAISE);
    EXPECT_TRUE(layer_state_is(GAMING));
    reports.clear();
    tap(36);
    EXPECT_TRUE(saw_mods(MOD_BIT(KC_LSFT)));
    EXPECT_EQ(get_oneshot_mods(), 0);
    layer_clear();
}

TEST_F(Preonic, SpotlightTapAndControlHold) {
    tap(48);
    EXPECT_TRUE(saw(MOD_BIT(KC_LGUI), KC_SPC));
    EXPECT_FALSE(saw_mods(MOD_BIT(KC_LCTL)));
    expect_released();
    idle_for(TAPPING_TERM + 20);
    reports.clear();
    press(48); idle_for(TAPPING_TERM + 10);
    press(13);
    EXPECT_TRUE(saw(MOD_BIT(KC_LCTL), KC_Q));
    release(13); release(48);
    expect_released();
}

TEST_F(Preonic, OptionBackspaceTapAndWindowHold) {
    tap(54);
    EXPECT_TRUE(saw(MOD_BIT(KC_LALT), KC_BSPC));
    expect_released();
    idle_for(TAPPING_TERM + 20);
    reports.clear();
    press(54); idle_for(TAPPING_TERM + 10);
    EXPECT_TRUE(layer_state_is(WINDOW));
    release(54);
    EXPECT_FALSE(layer_state_is(WINDOW));
    EXPECT_FALSE(emitted(KC_BSPC));
}
