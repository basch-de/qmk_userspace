// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "test_common.hpp"
#include "positions.hpp"
#include <algorithm>
#include <vector>
#include <iterator>
#include <utility>
extern "C" {
#include "action_tapping.h"
#include "action_util.h"
#include "keymap_introspection.h"
void set_time(uint32_t time);
#ifdef TEST_CORNE
unsigned tested_encoder_layers(void);
uint16_t tested_encoder_code(unsigned, unsigned, unsigned);
#endif
}

// QMK supplies the matrix, timer, EEPROM backend and host driver test doubles.
// Production keymaps, hooks, layer handling, tapping and Caps Word remain real.
class UserspaceTest : public TestFixture {
  protected:
    testing::NiceMock<TestDriver> driver;
    std::vector<report_keyboard_t> reports;

    void SetUp() override {
        ON_CALL(driver, send_keyboard_mock(testing::_)).WillByDefault([this](report_keyboard_t &report) {
            reports.push_back(report);
        });
        for (unsigned layer = 0; layer < keymap_layer_count_raw(); ++layer) {
            for (unsigned row = 0; row < MATRIX_ROWS; ++row) {
                for (unsigned col = 0; col < MATRIX_COLS; ++col) {
                    add_key(KeymapKey(layer, col, row, keycode_at_keymap_location_raw(layer, row, col)));
                }
            }
        }
        default_layer_set(1);
        layer_clear();
        clear_oneshot_mods();
        clear_keyboard();
#ifdef CAPS_WORD_ENABLE
        caps_word_off();
#endif
        idle_for(1);
        reports.clear();
    }

    uint16_t code(unsigned index, unsigned layer = 0) const {
        auto p = positions[index];
        return keycode_at_keymap_location_raw(layer, p.row, p.col);
    }
    void press(unsigned index) {
        auto p = positions[index];
        press_key(p.col, p.row);
        run_one_scan_loop();
    }
    void release(unsigned index) {
        auto p = positions[index];
        release_key(p.col, p.row);
        run_one_scan_loop();
    }
    void tap(unsigned index, unsigned duration = 20) {
        press(index);
        idle_for(duration);
        release(index);
    }
    unsigned term(unsigned index, unsigned layer = 0) const {
        keyrecord_t record = {};
        auto p = positions[index];
        record.event.key = keypos_t{.col = uint8_t(p.col), .row = uint8_t(p.row)};
        (void)record; (void)index; (void)layer;
        return GET_TAPPING_TERM(code(index, layer), &record);
    }
    unsigned quick(unsigned index, unsigned layer = 0) const {
        keyrecord_t record = {};
        (void)record; (void)index; (void)layer;
        return GET_QUICK_TAP_TERM(code(index, layer), &record);
    }
    bool saw(uint8_t mods, uint8_t key) const {
        return std::any_of(reports.begin(), reports.end(), [=](const report_keyboard_t &report) {
            return report.mods == mods && std::find(std::begin(report.keys), std::end(report.keys), key) != std::end(report.keys);
        });
    }
    bool emitted(uint8_t key) const {
        return std::any_of(reports.begin(), reports.end(), [=](const report_keyboard_t &report) {
            return std::find(std::begin(report.keys), std::end(report.keys), key) != std::end(report.keys);
        });
    }
    bool saw_mods(uint8_t mods) const {
        return std::any_of(reports.begin(), reports.end(), [=](const report_keyboard_t &report) { return report.mods == mods; });
    }
    void expect_released() const {
        ASSERT_FALSE(reports.empty());
        EXPECT_EQ(get_mods(), 0);
        for (auto key : reports.back().keys) EXPECT_EQ(key, KC_NO);
    }
    void check_structure() {
        EXPECT_EQ(keymap_layer_count_raw(), expected_layers);
        EXPECT_EQ(sizeof(positions) / sizeof(positions[0]), physical_key_count);
        bool used[MATRIX_ROWS][MATRIX_COLS] = {};
        for (auto p : positions) {
            ASSERT_LT(p.row, unsigned(MATRIX_ROWS));
            ASSERT_LT(p.col, unsigned(MATRIX_COLS));
            EXPECT_FALSE(used[p.row][p.col]);
            used[p.row][p.col] = true;
        }
    }
};
