# Keebart Corne MX Pro hardware overlay

Source: [Keebart/vial-qmk-keebart, branch vial](https://github.com/Keebart/vial-qmk-keebart/tree/63e2d6248209f1926e60daa5b950c771cf09d837/keyboards/keebart/corne_mx_pro)
at commit `63e2d6248209f1926e60daa5b950c771cf09d837`.

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

The Corne workflow uses official Mainline QMK commit
`d194c077ed964195ec16d255c7a4b89a794cf03b`. The existing Preonic workflow retains
its own Mainline `master` reference.

The first integration stage builds only the manufacturer default keymap.
A successful Actions run is required before the personal keymap port begins.
