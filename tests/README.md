# Native Mainline QMK tests

The personal CI variants run the official QMK Google Test framework with the
same resolved firmware revision as the firmware builds. No local compilation
is required or permitted by this repository's workflow. The default variants
continue to serve as independent firmware compilation baselines.

`prepare.py` creates `tests/basch_corne` or `tests/basch_preonic` inside the
disposable Actions firmware checkout. It uses QMK's own metadata and keyboard
header generators, copies the production keymap, behaviors, shared definitions,
config and rules without editing them, and installs a host-only adapter plus
our tests. The production rules compile `behaviors.c` as a separate source file,
just as in the firmware builds. QMK discovers these
test suites normally; no QMK core source or existing tests are patched.

The adapter exposes the compiled encoder table without emulating encoder
hardware. Test fixtures load the actual compiled keymap into QMK's standard
per-test keymap facility. Matrix scanning, tapping, layers, user callbacks,
Caps Word and keyboard report generation use real QMK code. GPIO, time, EEPROM
and USB transport use QMK's native test backends. System reset/boot/EEPROM-clear
bindings are inspected as data and never pressed in these tests.

Coverage includes:

- Actual physical geometry, layer count, critical layer access and system keys.
- All eight HRMs: taps, opposite-hand nested chords, same-hand chords, rolls,
  and per-key timeout behavior.
- All six thumb positions with HRMs from both hands; disabled extra keys,
  modifier stacking and same-hand rolls past the tapping term.
- Quick Tap inside/outside its window, Tab/Enter repeat, and 16-bit timer wrap.
- Hold-preferred/tap-preferred layer taps, every layer entrance, NUMPAD toggle.
- Spotlight/Hyper, Caps Word/SHORT, Caps Word continuation/termination, comma/dot
  hold and release after a layer change.
- Preonic Lower+Raise/Adjust, Gaming access and direct Shift, Spotlight/Ctrl,
  and Option-Backspace/Window.

The CI commands are `qmk test-c -t basch_corne` and
`qmk test-c -t basch_preonic`, after preparation. `test-setup.log`, `tests.log`
and the merged `test-hardware.json` are included in each personal variant's
existing provenance artifact, including available logs on failure. A failed
suite fails its personal variant before firmware upload; other matrix variants
remain independent.

These tests check contracts and event/report sequences rather than maintaining
a second complete binding table. Intended changes to those contracts require
reviewing the affected expectations. They do not certify MCU execution, split
transport, electrical pins, physical encoders/OLED/RGB, host autorepeat, or the
actual EurKEY-next/macOS interpretation. Physical testing remains necessary.

Reference: [official QMK unit testing documentation](https://docs.qmk.fm/unit_testing).
