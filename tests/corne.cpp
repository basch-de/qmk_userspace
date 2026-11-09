// SPDX-License-Identifier: GPL-2.0-or-later
#include "fixture.hpp"

class Corne : public UserspaceTest {};
enum { MACOS, NUM, SYM, NAV, WIN, SHORT, NUMPAD, SYS };

struct HrmCase { unsigned position; uint8_t tap, modifier; unsigned opposite, same; };
static const HrmCase hrms[] = {
    {15, KC_A, MOD_BIT(KC_LCTL), 8, 1},
    {16, KC_S, MOD_BIT(KC_LGUI), 8, 1},
    {17, KC_D, MOD_BIT(KC_LALT), 8, 1},
    {18, KC_F, MOD_BIT(KC_LSFT), 8, 1},
    {23, KC_J, MOD_BIT(KC_RSFT), 1, 8},
    {24, KC_K, MOD_BIT(KC_RALT), 1, 8},
    {25, KC_L, MOD_BIT(KC_RGUI), 1, 8},
    {26, KC_SCLN, MOD_BIT(KC_RCTL), 1, 8},
};
class CorneHrm : public Corne, public testing::WithParamInterface<unsigned> {};
INSTANTIATE_TEST_SUITE_P(AllHomeRowMods, CorneHrm, testing::Range(0u, 8u));

TEST_F(Corne, PhysicalStructureAndCriticalLayerAccess) {
    check_structure();
    EXPECT_EQ(code(0), LT(SYS, KC_GRV));
    EXPECT_EQ(code(28), LT(SHORT, KC_EQL));
    const uint16_t thumbs[] = {LT(NAV, KC_ESC), LT(NUM, KC_BSPC), LT(WIN, KC_TAB),
                              LT(NUMPAD, KC_ENT), LT(SYM, KC_SPC), LT(SHORT, KC_NO)};
    for (unsigned i = 0; i < 6; ++i) EXPECT_EQ(code(40 + i), thumbs[i]);
    EXPECT_EQ(code(33, SYM), TG(NUMPAD));
    EXPECT_EQ(code(33, NUMPAD), TG(NUMPAD));
    EXPECT_EQ(code(35, SHORT), KC_ASST);
}

TEST_F(Corne, SystemActionsAreSymmetricAndConfinedToSys) {
    EXPECT_EQ(code(13, SYS), KC_PWR);
    for (auto pair : {std::make_pair(28u, 39u), {29u, 38u}, {30u, 37u}}) {
        auto expected = pair.first == 28 ? QK_RBT : pair.first == 29 ? QK_BOOT : EE_CLR;
        EXPECT_EQ(code(pair.first, SYS), expected);
        EXPECT_EQ(code(pair.second, SYS), expected);
    }
    for (unsigned layer = 0; layer < expected_layers; ++layer) {
        for (unsigned i = 0; i < physical_key_count; ++i) {
            auto key = code(i, layer);
            if (layer != SYS) EXPECT_FALSE(key == QK_RBT || key == QK_BOOT || key == EE_CLR);
        }
        for (unsigned i : {6u, 7u, 20u, 21u}) EXPECT_EQ(code(i, layer), KC_NO);
    }
}

TEST_P(CorneHrm, TapProducesOnlyTheLetter) {
    auto h = hrms[GetParam()];
    tap(h.position);
    EXPECT_TRUE(saw(0, h.tap));
    EXPECT_FALSE(saw_mods(h.modifier));
    expect_released();
}

TEST_P(CorneHrm, NestedOppositeHandPressUsesModifier) {
    auto h = hrms[GetParam()];
    press(h.position); idle_for(10);
    press(h.opposite); idle_for(10); release(h.opposite);
    EXPECT_TRUE(saw(h.modifier, uint8_t(code(h.opposite))));
    EXPECT_FALSE(emitted(h.tap));
    release(h.position);
    expect_released();
}

TEST_P(CorneHrm, SameHandNestedPressStaysTap) {
    auto h = hrms[GetParam()];
    press(h.position); idle_for(10);
    press(h.same); idle_for(10); release(h.same); release(h.position);
    EXPECT_TRUE(saw(0, h.tap));
    EXPECT_TRUE(saw(0, uint8_t(code(h.same))));
    EXPECT_FALSE(saw_mods(h.modifier));
    expect_released();
}

TEST_P(CorneHrm, OppositeHandRollStaysTap) {
    auto h = hrms[GetParam()];
    press(h.position); idle_for(10); press(h.opposite);
    idle_for(10); release(h.position); release(h.opposite);
    EXPECT_TRUE(saw(0, h.tap));
    EXPECT_FALSE(saw_mods(h.modifier));
    expect_released();
}

TEST_P(CorneHrm, TimeoutRespectsThePerKeyTappingTerm) {
    auto h = hrms[GetParam()];
    press(h.position); idle_for(term(h.position) - 10);
    EXPECT_FALSE(saw_mods(h.modifier));
    idle_for(20);
    EXPECT_TRUE(saw_mods(h.modifier));
    release(h.position);
    EXPECT_FALSE(emitted(h.tap));
    expect_released();
}

class CorneThumb : public Corne, public testing::WithParamInterface<unsigned> {};
INSTANTIATE_TEST_SUITE_P(AllThumbs, CorneThumb, testing::Range(0u, 12u));
TEST_P(CorneThumb, ThumbCanTriggerAnHrmFromEitherHand) {
    // Every thumb is exercised once with a left HRM and once with a right HRM.
    const auto h = hrms[GetParam() < 6 ? 0 : 4];
    press(h.position); idle_for(10); tap(40 + GetParam() % 6, 20); release(h.position);
    EXPECT_TRUE(saw_mods(h.modifier));
    EXPECT_FALSE(emitted(h.tap));
    EXPECT_EQ(get_mods(), 0);
}

TEST_F(Corne, DisabledInnerKeysDoNotTriggerOppositeHandHold) {
    press(15); tap(7); release(15);
    EXPECT_TRUE(saw(0, KC_A));
    EXPECT_FALSE(saw_mods(MOD_BIT(KC_LCTL)));
    expect_released();
}

TEST_F(Corne, SameHandDecisionStaysTapPastTheTimeout) {
    press(15); press(1); idle_for(term(15) + 20); release(1); release(15);
    EXPECT_TRUE(saw(0, KC_A));
    EXPECT_FALSE(saw_mods(MOD_BIT(KC_LCTL)));
    expect_released();
}

TEST_F(Corne, MultipleHomeRowModifiersCanFormAChord) {
    press(23); press(24); tap(1); release(24); release(23);
    EXPECT_TRUE(saw(MOD_BIT(KC_RSFT) | MOD_BIT(KC_RALT), KC_Q));
    EXPECT_FALSE(emitted(KC_J)); EXPECT_FALSE(emitted(KC_K));
    expect_released();
}

TEST_F(Corne, QuickTapRepeatsInsideItsWindow) {
    tap(15); idle_for(quick(15) - 10); reports.clear();
    press(15); idle_for(term(15) + 20);
    EXPECT_TRUE(saw(0, KC_A));
    EXPECT_FALSE(saw_mods(MOD_BIT(KC_LCTL)));
    release(15); expect_released();
}

TEST_F(Corne, QuickTapHoldsOutsideItsWindow) {
    tap(15); idle_for(quick(15) + 10); reports.clear();
    press(15); idle_for(term(15) + 20);
    EXPECT_TRUE(saw_mods(MOD_BIT(KC_LCTL)));
    EXPECT_FALSE(emitted(KC_A));
    release(15); expect_released();
}

TEST_F(Corne, QuickTapWorksAcrossTheSixteenBitTimerWrap) {
    set_time(65510);
    tap(15); idle_for(80); reports.clear();
    press(15); idle_for(term(15) + 20);
    EXPECT_TRUE(saw(0, KC_A));
    EXPECT_FALSE(saw_mods(MOD_BIT(KC_LCTL)));
    release(15); expect_released();
}

TEST_F(Corne, TabQuickTapRepeatsAndThenReturnsToLayerHold) {
    tap(42); idle_for(quick(42) - 10); reports.clear();
    press(42); idle_for(term(42) + 20);
    EXPECT_TRUE(saw(0, KC_TAB)); EXPECT_FALSE(layer_state_is(WIN));
    release(42); idle_for(quick(42) + 20); reports.clear();
    press(42); idle_for(term(42) + 20);
    EXPECT_TRUE(layer_state_is(WIN)); EXPECT_FALSE(emitted(KC_TAB));
    release(42); EXPECT_EQ(layer_state, 0u);
}

TEST_F(Corne, EnterQuickTapRepeatsAndThenReturnsToLayerHold) {
    tap(43); idle_for(quick(43) - 10); reports.clear();
    press(43); idle_for(term(43) + 20);
    EXPECT_TRUE(saw(0, KC_ENT)); EXPECT_FALSE(layer_state_is(NUMPAD));
    release(43); idle_for(quick(43) + 20); reports.clear();
    press(43); idle_for(term(43) + 20);
    EXPECT_TRUE(layer_state_is(NUMPAD)); EXPECT_FALSE(emitted(KC_ENT));
    release(43); EXPECT_EQ(layer_state, 0u);
}

TEST_F(Corne, HoldPreferredLayerTapActivatesOnInterruption) {
    press(41); press(1);
    EXPECT_TRUE(layer_state_is(NUM));
    release(1); release(41);
    EXPECT_TRUE(saw(0, KC_1)); EXPECT_FALSE(emitted(KC_BSPC));
    EXPECT_EQ(layer_state, 0u); expect_released();
}

TEST_F(Corne, EnterLayerTapPrefersTapDuringARoll) {
    press(43); press(1);
    EXPECT_FALSE(layer_state_is(NUMPAD));
    release(43); release(1);
    EXPECT_TRUE(saw(0, KC_ENT)); EXPECT_TRUE(saw(0, KC_Q));
    EXPECT_EQ(layer_state, 0u); expect_released();
}

TEST_F(Corne, NumpadToggleIsReachableAndCanBeTurnedOff) {
    press(44); idle_for(term(44) + 10); tap(33); release(44);
    ASSERT_TRUE(layer_state_is(NUMPAD));
    tap(33);
    EXPECT_FALSE(layer_state_is(NUMPAD));
    EXPECT_EQ(layer_state, 0u);
}

TEST_F(Corne, SpotlightTapAndHyperHold) {
    tap(14);
    EXPECT_TRUE(saw(MOD_BIT(KC_LGUI), KC_SPC));
    expect_released();
    idle_for(term(14) + 20); reports.clear();
    press(14); press(1);
    EXPECT_TRUE(saw(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI), KC_Q));
    release(1); release(14);
    EXPECT_FALSE(emitted(KC_SPC)); expect_released();
}

TEST_F(Corne, CapsWordThumbTogglesWithoutSendingAKey) {
    tap(45); EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(reports.empty());
    idle_for(term(45) + 10);
    tap(45); EXPECT_FALSE(is_caps_word_on()); EXPECT_TRUE(reports.empty());
}

TEST_F(Corne, CapsWordThumbHoldActivatesShortOnEitherHand) {
    press(45); press(17);
    EXPECT_TRUE(layer_state_is(SHORT)); EXPECT_FALSE(is_caps_word_on());
    release(17); release(45);
    EXPECT_FALSE(layer_state_is(SHORT));
}

TEST_F(Corne, CapsWordCapitalizesLettersAndSpaceEndsTheWord) {
    tap(45); tap(15);
    EXPECT_TRUE(saw(MOD_BIT(KC_LSFT), KC_A)); EXPECT_TRUE(is_caps_word_on());
    tap(44);
    EXPECT_FALSE(is_caps_word_on()); EXPECT_TRUE(saw(0, KC_SPC));
    expect_released();
}

TEST_F(Corne, CapsWordUsesStandardContinuationAndSymbolTermination) {
    caps_word_on(); layer_on(NUM);
    tap(1); EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(saw(0, KC_1));
    tap(13); EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(saw(0, KC_BSPC));
    layer_clear(); layer_on(NAV);
    tap(13); EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(saw(0, KC_DEL));
    layer_clear(); layer_on(SYM);
    tap(34); EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(saw(MOD_BIT(KC_LSFT), KC_MINS));
    tap(1); EXPECT_FALSE(is_caps_word_on()); EXPECT_TRUE(saw(MOD_BIT(KC_LSFT), KC_1));
    layer_clear();
    expect_released();
}

TEST_F(Corne, CapsWordUsesStandardHyphenAndIdleTimeout) {
    caps_word_on();
    tap(39);
    EXPECT_TRUE(is_caps_word_on()); EXPECT_TRUE(saw(MOD_BIT(KC_LSFT), KC_MINS));
    expect_released();
    ASSERT_GT(CAPS_WORD_IDLE_TIMEOUT, 0);
    idle_for(CAPS_WORD_IDLE_TIMEOUT - 50); EXPECT_TRUE(is_caps_word_on());
    idle_for(100); EXPECT_FALSE(is_caps_word_on());
}

TEST_F(Corne, CommaTapAndHeldDotUseRealQmkTapHoldProcessing) {
    layer_on(NUMPAD); tap(38);
    EXPECT_TRUE(saw(0, KC_COMM)); EXPECT_FALSE(emitted(KC_DOT)); expect_released();
    idle_for(term(38, NUMPAD) + 20); reports.clear();
    press(38); idle_for(term(38, NUMPAD) + 20);
    EXPECT_TRUE(saw(0, KC_DOT)); EXPECT_EQ(layer_state, 1u << NUMPAD);
    // QMK's release cache must retain the held action after a layer change.
    layer_clear(); release(38);
    EXPECT_FALSE(emitted(KC_COMM)); expect_released();
}

class CorneLayerHold : public Corne, public testing::WithParamInterface<unsigned> {};
INSTANTIATE_TEST_SUITE_P(AllLayerEntrances, CorneLayerHold, testing::Range(0u, 8u));
TEST_P(CorneLayerHold, HoldActivatesItsLayerAndReleaseDeactivatesIt) {
    const unsigned keys[] = {0, 40, 41, 42, 43, 44, 45, 28};
    const unsigned layers[] = {SYS, NAV, NUM, WIN, NUMPAD, SYM, SHORT, SHORT};
    auto key = keys[GetParam()], layer = layers[GetParam()];
    press(key); idle_for(term(key) + 10);
    EXPECT_TRUE(layer_state_is(layer));
    release(key);
    EXPECT_EQ(layer_state, 0u);
    EXPECT_FALSE(is_caps_word_on());
}

TEST_F(Corne, EqualShortLayerTapRemainsATapDuringARoll) {
    press(28); press(1);
    EXPECT_FALSE(layer_state_is(SHORT));
    release(28); release(1);
    EXPECT_TRUE(saw(0, KC_EQL)); EXPECT_TRUE(saw(0, KC_Q));
    EXPECT_EQ(layer_state, 0u); expect_released();
}
