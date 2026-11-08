# QMK External Userspace

Personal `basch_de` keymaps for two keyboards:

- Preonic Drop rev3: `preonic/rev3_drop`, 60 individual 1u keys.
- Keebart Corne MX Pro Standard: `keebart/corne_mx_pro/standard`, RP2040, 46 keys.

Both targets are listed in `qmk.json`. Firmware uses official Mainline QMK.
The Corne hardware definition is installed from the versioned
[hardware overlay](vendor/qmk/README.md); no Vial or Studio runtime is included.

See the [project documentation](docs/PROJECT.md) for architecture, build details,
the Corne's ZMK behavior mapping, remaining differences, and hardware tests.

## GitHub Actions

The single workflow [build.yml](.github/workflows/build.yml) runs on pushes,
pull requests, and manual starts. Its four independent matrix jobs build:

| Variant | Firmware reference | Artifact |
| --- | --- | --- |
| `preonic-personal` | Official QMK `master`, resolved once per run | `preonic-basch_de` (BIN) |
| `preonic-default` | Same resolved official QMK commit | `preonic-default` (BIN) |
| `corne-standard-default` | Same resolved official QMK commit | `corne-standard-default` (UF2) |
| `corne-standard-basch_de` | Same resolved official QMK commit | `corne-standard-basch_de` (UF2) |

Every variant uses the same QMK commit resolved once per run. Firmware follows
official QMK `master`; the build container follows `ghcr.io/qmk/qmk_cli:latest`.
Jobs compile independently and upload firmware plus `provenance-<variant>`
artifacts with revisions, environment details, build logs and checksums.

The personal Preonic and Corne jobs also run [native QMK behavior tests](tests/README.md)
against their actual production keymaps and the same firmware revision. These
cover critical layer/system bindings, tap/hold sequences and custom actions.
Test setup/output logs and hardware metadata are included in the corresponding
provenance artifact. Default builds remain independent compilation baselines.

Download the firmware from **Actions → Build QMK firmware → run → Artifacts**.
All variants are provided exclusively as Actions artifacts, with no automatic
release or tag publication. Successful variants upload their artifacts even
when another variant fails. Any existing legacy Preonic `latest` release is a
historical build and is no longer updated; use the selected Actions run for
current firmware. Artifact availability follows the repository's retention policy.

All firmware compilation takes place in GitHub Actions. The workflow does not
flash devices, clear EEPROM, or delete device flash. Compilation success does
not replace physical testing of tap/hold behavior, host output, or peripherals.

## Working on keymaps

- Preonic: `keyboards/preonic/keymaps/basch_de/`.
- Corne: `keyboards/keebart/corne_mx_pro/keymaps/basch_de/`.
- Corne hardware and manufacturer baseline: `vendor/qmk/`.
- Repository instructions: [AGENTS.md](AGENTS.md).

Both personal keymap directories separate bindings and diagrams (`keymap.c`)
from behavior hooks (`behaviors.c`). Shared layer names and dual-role aliases
live in `keymap_defs.h`; `rules.mk` compiles the behavior source separately.

Keep each keymap's physical matrix and diagrams aligned. Changes for one
keyboard must preserve the other keyboard's configuration and build behavior.
