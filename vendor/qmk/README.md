# Keebart Corne MX Pro hardware overlay

Source: [Keebart/vial-qmk-keebart, branch vial](https://github.com/Keebart/vial-qmk-keebart/tree/63e2d6248209f1926e60daa5b950c771cf09d837/keyboards/keebart/corne_mx_pro)
at commit `63e2d6248209f1926e60daa5b950c771cf09d837`.

## Upstream checks during sessions

- Last checked: 2026-11-08.
- Observed `vial` head: `63e2d6248209f1926e60daa5b950c771cf09d837`.
- Result: branch head matches the imported source; no upstream update available.

Recheck occasionally during substantive Corne or build-system work, roughly
monthly, or on request. When upstream advances, compare the relevant original
hardware and default-keymap files against the imported source before deciding
which changes apply. Record the check separately from an actual import.
This is a session maintenance task, independent of firmware compilation.

## Overlay contents and Mainline adjustments

Only the shared hardware definition, Standard variant, and manufacturer default
keymap are included. No Vial keymaps, Vial runtime, Studio, Mini variant, or QMK
core files are included. GitHub Actions copies this hardware subtree into a fresh
official QMK checkout before compilation. Personal keymaps remain in the external
userspace `keyboards/` tree.

Mainline compatibility changes:

- Remove `DYNAMIC_KEYMAP_LAYER_COUNT` and `VIALRGB_NO_DIRECT` from `config.h`.
- Enable Mainline `TRI_LAYER_ENABLE` for the default keymap's existing
  `TL_LOWR`/`TL_UPPR` keys and their Adjust/bootloader layer.
- Replace obsolete default-keymap `RGB_*` controls with their current RGB Matrix
  equivalents: `RM_TOGG`, `RM_NEXT`, `RM_PREV`, `RM_HUEU`, `RM_HUED`, `RM_SATU`,
  `RM_SATD`, `RM_VALU`, and `RM_VALD`. Key positions, layer behavior, and encoder
  actions are preserved.

The matrix pins, handedness pin, serial transport, USB detection, bootmagic,
RGB Matrix layout, OLED and encoder configuration are retained from the source.
Hardware verification is still required, including the manufacturer's shared
I2C/encoder pin assignments; optional peripherals must match the installed hardware.

The shared `.github/workflows/build.yml` follows official Mainline QMK `master`.
Each run resolves that branch once and uses the same commit for all four
Preonic and Corne variants. Firmware is not permanently pinned; the build
container follows `ghcr.io/qmk/qmk_cli:latest`, as in official QMK's userspace
workflow. This hardware overlay remains versioned
in the userspace repository and is not fetched from Keebart during the build.

The manufacturer default keymap passed the first integration stage before the
personal port began. See [migration notes](../../docs/corne-mainline.md) for
the build evidence, source mapping, and remaining behavior differences.
