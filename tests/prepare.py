#!/usr/bin/env python3
"""Prepare native QMK tests from production sources; run by GitHub Actions only.

This creates test files in the disposable CI firmware checkout. No firmware core
or production keymap is modified. Metadata and layout headers come from QMK's
own generators, including inherited keyboard definitions and layout aliases.
"""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
PROFILES = {
    "preonic/rev3_drop": ("basch_preonic", "LAYOUT_preonic_grid", 60, 6, "TEST_PREONIC"),
    "keebart/corne_mx_pro/standard": ("basch_corne", "LAYOUT_split_3x6_3_ex2", 46, 8, "TEST_CORNE"),
}


def main():
    if len(sys.argv) != 3 or sys.argv[2] not in PROFILES:
        raise SystemExit("Usage: prepare.py FIRMWARE KEYBOARD")
    firmware = Path(sys.argv[1]).resolve()
    keyboard = sys.argv[2]
    suite, layout_name, physical_count, layers, flag = PROFILES[keyboard]
    destination = firmware / "tests" / suite
    if destination.exists():
        raise SystemExit(f"Test destination already exists: {destination}")
    destination.mkdir()
    metadata_path = destination / "hardware.json"
    with metadata_path.open("w") as output:
        subprocess.run(["qmk", "info", "-kb", keyboard, "-f", "json", "--api"], cwd=firmware, stdout=output, check=True)
    subprocess.run(["qmk", "generate-keyboard-h", "-kb", keyboard, "-o", str(destination / "test_keyboard.h")], cwd=firmware, check=True)
    metadata = json.loads(metadata_path.read_text())
    resolved = layout_name
    while resolved not in metadata["layouts"]:
        resolved = metadata["layout_aliases"][resolved]
    positions = [key["matrix"] for key in metadata["layouts"][resolved]["layout"]]
    if len(positions) != physical_count or len(set(map(tuple, positions))) != physical_count:
        raise SystemExit("Unexpected physical key count or duplicate matrix coordinates")
    rows = metadata["matrix_size"]["rows"]
    cols = metadata["matrix_size"]["cols"]
    if any(not (0 <= row < rows and 0 <= col < cols) for row, col in positions):
        raise SystemExit("Physical position outside the reported matrix")
    if os.environ.get("BUILD_INFO"):
        shutil.copyfile(metadata_path, Path(os.environ["BUILD_INFO"]) / "test-hardware.json")
    keymap_keyboard = "preonic" if keyboard == "preonic/rev3_drop" else "keebart/corne_mx_pro"
    source = ROOT / "keyboards" / keymap_keyboard / "keymaps/basch_de"
    for name, output in [("keymap.c", "production_keymap.c"), ("config.h", "production_config.h"), ("rules.mk", "production_rules.mk")]:
        shutil.copyfile(source / name, destination / output)
    shutil.copyfile(ROOT / "tests/fixture.hpp", destination / "fixture.hpp")
    shutil.copyfile(ROOT / ("tests/corne.cpp" if flag == "TEST_CORNE" else "tests/preonic.cpp"), destination / "test_userspace.cpp")
    config = (
        '// Generated host configuration; production timing settings are included intact.\n'
        '#pragma once\n#include "test_common.h"\n'
        f'#undef MATRIX_ROWS\n#define MATRIX_ROWS {rows}\n'
        f'#undef MATRIX_COLS\n#define MATRIX_COLS {cols}\n'
        '#include "production_config.h"\n'
    )
    adapter = '// SPDX-License-Identifier: GPL-2.0-or-later\n#include "test_keyboard.h"\n#define QMK_KEYBOARD_H "test_keyboard.h"\n'
    if flag == "TEST_CORNE":
        encoders = len(metadata["encoder"]["rotary"]) + len(metadata["split"]["encoder"]["right"]["rotary"])
        if encoders != 4:
            raise SystemExit("Corne encoder count changed; review the host data adapter")
        # Only expose the real encoder table; encoder hardware is not emulated.
        adapter += f'#define NUM_ENCODERS {encoders}\n#define NUM_DIRECTIONS 2\n#define ENCODER_CCW_CW(ccw, cw) {{(cw), (ccw)}}\n'
    adapter += '#include "production_keymap.c"\n'
    if flag == "TEST_CORNE":
        adapter += '''
unsigned tested_encoder_layers(void) { return sizeof(encoder_map) / sizeof(encoder_map[0]); }
uint16_t tested_encoder_code(unsigned layer, unsigned encoder, unsigned direction) {
    return encoder_map[layer][encoder][direction];
}
'''
    (destination / "keymap.c").write_text(adapter)
    (destination / "config.h").write_text(config)
    (destination / "test.mk").write_text(
        'include $(TEST_PATH)/production_rules.mk\n'
        'COMMAND_ENABLE = no\n'
        f'OPT_DEFS += -D{flag}\n'
    )
    (destination / "positions.hpp").write_text(
        '// Generated from the actual QMK hardware metadata.\n#pragma once\n'
        'struct PhysicalPosition { unsigned row, col; };\n'
        'static constexpr PhysicalPosition positions[] = {' + ','.join(f'{{{r},{c}}}' for r,c in positions) + '};\n'
        f'static constexpr unsigned expected_layers = {layers};\n'
        f'static constexpr unsigned physical_key_count = {physical_count};\n'
    )
    print(f"Prepared {suite}: {physical_count} physical keys, {rows}x{cols} matrix, {layers} layers")


if __name__ == "__main__":
    main()
