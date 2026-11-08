# QMK External Userspace

Personal `basch_de` keymaps for two keyboards:

- Preonic Drop rev3: `preonic/rev3_drop`, 60 individual 1u keys.
- Keebart Corne MX Pro Standard: `keebart/corne_mx_pro/standard`, RP2040, 46 keys.

Both targets are listed in `qmk.json`. Firmware uses official Mainline QMK.
The Corne hardware definition is installed from the versioned
[hardware overlay](vendor/qmk/README.md); no Vial or Studio runtime is included.

See the [Corne migration notes](docs/corne-mainline.md) for source versions,
ZMK behavior mapping, remaining differences, and the hardware test list.

## GitHub Actions

The single workflow [build.yml](.github/workflows/build.yml) runs on pushes,
pull requests, and manual starts. Its three independent matrix jobs build:

| Variant | Firmware reference | Artifact |
| --- | --- | --- |
| `preonic-personal` | Official QMK `master`, resolved once per run | `Firmware` (BIN) |
| `corne-standard-default` | Pinned official QMK commit | `corne-standard-default` (UF2) |
| `corne-personal` | Same pinned official QMK commit | `corne-standard-basch_de` (UF2) |

Each job compiles only its selected target with `qmk mass-compile`. A failure
in one variant does not cancel the other builds. The manufacturer Corne keymap
uses a separate userspace without personal keymap files. Only the Corne jobs
install the hardware overlay; the versioned `qmk.json` is left unchanged.

Like the Studio project's build structure, the workflow uses a fixed QMK
container image and records provenance separately for every variant:
firmware and userspace revisions, submodules, compiler, Python packages,
build logs, and firmware checksums. These are uploaded as `provenance-<variant>`
artifacts, including available logs when compilation fails.

Download the firmware from **Actions → Build QMK firmware → run → Artifacts**.
The existing Preonic `latest` release is refreshed on `main`, independently of
Corne build success. A missing Preonic artifact leaves the previous release
intact. Pull requests do not publish releases.

All firmware compilation takes place in GitHub Actions. The workflow does not
flash devices, clear EEPROM, or delete device flash. Compilation success does
not replace physical testing of tap/hold behavior, host output, or peripherals.

## Working on keymaps

- Preonic: `keyboards/preonic/keymaps/basch_de/`.
- Corne: `keyboards/keebart/corne_mx_pro/keymaps/basch_de/`.
- Corne hardware and manufacturer baseline: `vendor/qmk/`.
- Repository instructions: [AGENTS.md](AGENTS.md).

Keep each keymap's physical matrix and diagrams aligned. Changes for one
keyboard must preserve the other keyboard's configuration and build behavior.
