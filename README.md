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
pull requests, and manual starts. Its four independent matrix jobs build:

| Variant | Firmware reference | Artifact |
| --- | --- | --- |
| `preonic-personal` | Official QMK `master`, resolved once per run | `preonic-basch_de` (BIN) |
| `preonic-default` | Same resolved official QMK commit | `preonic-default` (BIN) |
| `corne-standard-default` | Same resolved official QMK commit | `corne-standard-default` (UF2) |
| `corne-standard-basch_de` | Same resolved official QMK commit | `corne-standard-basch_de` (UF2) |

Like the Studio project, each run resolves the current firmware branch once
and uses that exact commit for every variant. Here the source is official QMK
`master`; firmware is not permanently pinned to a commit. A new upstream commit
is picked up on the next push, pull request, or manual run and does not itself
trigger a build in this repository. The build container follows official QMK's
`ghcr.io/qmk/qmk_cli:latest` tag.

Each job compiles only its selected target with `qmk mass-compile`. A failure
in one variant does not cancel the other builds. Both manufacturer keymaps
use separate userspaces without personal keymap files. Only the Corne jobs
install the hardware overlay; the versioned `qmk.json` is left unchanged.

The workflow records provenance separately for every variant:
firmware and userspace revisions, submodules, compiler, Python packages,
build logs, and firmware checksums. These are uploaded as `provenance-<variant>`
artifacts, including available logs when compilation fails.

The personal Preonic and Corne jobs also run [native QMK behavior tests](tests/README.md)
against their actual production keymaps and the same firmware revision. These
cover critical layer/system bindings, tap/hold sequences and custom actions.
Test setup/output logs and hardware metadata are included in the corresponding
provenance artifact. Default builds remain independent compilation baselines.

The container uses `ghcr.io/qmk/qmk_cli:latest` directly, as in the official QMK
userspace workflow. See [build container behavior](docs/build-container.md).
As in QMK's own userspace workflow, Python dependencies are installed from the
checked-out firmware's `requirements.txt`; the resulting versions are recorded
with `pip freeze`. Both the image tag and the resulting Python environment can
change between builds.

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
