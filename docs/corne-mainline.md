# Corne MX Pro: Mainline-QMK-Portierung

Die Keebart Corne MX Pro Standard (46 Tasten, RP2040) wird zusätzlich zur
Preonic im bestehenden External Userspace gepflegt. Firmware-Basis ist
unverändertes offizielles QMK; ausschließlich die Hardwaredefinition wird im
Actions-Checkout ergänzt. Es werden keine Vial-/Studio-Komponenten eingebunden.

## Quellen und geprüfte Versionen

- [Mainline QMK](https://github.com/qmk/qmk_firmware/tree/d194c077ed964195ec16d255c7a4b89a794cf03b),
  Commit `d194c077ed964195ec16d255c7a4b89a794cf03b` für beide Corne-Keymaps.
- [Keebart-Hardwaredefinition](https://github.com/Keebart/vial-qmk-keebart/tree/63e2d6248209f1926e60daa5b950c771cf09d837/keyboards/keebart/corne_mx_pro),
  Branch `vial`, Commit `63e2d6248209f1926e60daa5b950c771cf09d837`.
  Übernommene Dateien und minimale Mainline-Anpassungen stehen in
  [vendor/qmk/README.md](../vendor/qmk/README.md).
- [Tatsächliche ZMK-Keymap](https://github.com/basch-de/zmk-config/blob/17dc18d4065161066a459656a87f36f11cd4ae88/config/corne_choc_pro.keymap)
  und [Konfiguration](https://github.com/basch-de/zmk-config/blob/17dc18d4065161066a459656a87f36f11cd4ae88/config/corne_choc_pro.conf),
  Commit `17dc18d4065161066a459656a87f36f11cd4ae88`. Deren `west.yml` verwendet
  ZMK `v0.3`; dessen Standarddefinitionen für `mt`, `lt` und Caps Word wurden
  zusätzlich geprüft.

Die Preonic verwendet weiterhin den bisherigen offiziellen QMK-Branch `master`.
Eine Corne-Aktualisierung ändert diese Referenz nicht.

## Aufbau und unabhängige Builds

`qmk.json` enthält die persönlichen Targets:

| Tastatur | Keymap | Workflow |
| --- | --- | --- |
| `preonic/rev3_drop` | `basch_de` | `build.yml`, Variante `preonic-personal` |
| `keebart/corne_mx_pro/standard` | `basch_de` | `build.yml`, Variante `corne-personal` |

Der gemeinsame Workflow `.github/workflows/build.yml` folgt dem Buildmuster
des Studio-Projekts: unabhängige Matrix-Jobs, ein festgelegtes Container-Image,
ein isolierter Hersteller-Userspace und getrennte Firmware-/Provenance-Artefakte.
Firmware-Basis bleibt offizielles Mainline-QMK. Die bisherigen zwei Workflows
wurden durch diese eine Datei ersetzt.

Die zusätzliche Variante `corne-standard-default` baut die Hersteller-Keymap als
Hardware-Referenz ohne persönliche Keymap-Dateien. Alle drei Varianten laufen
mit `fail-fast: false`; jeder Job kompiliert ausschließlich sein explizites
Target mit `qmk mass-compile`. Die versionierte `qmk.json` wird nicht verändert.
Nur die Corne-Jobs installieren das Hardware-Overlay. Die Preonic-Keymap,
`config.h` und `rules.mk` bleiben unverändert.

Pro Lauf wird der aktuelle Mainline-`master` für die Preonic einmal aufgelöst.
Beide Corne-Jobs verwenden denselben bisherigen gepinnten Mainline-Commit.
Ein neuer QMK-Commit startet keinen Lauf in diesem Repository; der nächste
Push, Pull Request oder manuelle Start nutzt die zugehörigen Referenzen.

Erwartete Firmware-Artefakte:

- `Firmware`: Preonic-BIN, mit der bisherigen Veröffentlichung kompatibel.
- `corne-standard-default`: UF2 der Herstellerbelegung.
- `corne-standard-basch_de`: UF2 der persönlichen Corne-Keymap.

Zu jeder Variante kommt ein `provenance-…`-Artefakt mit QMK-/Userspace-Commit,
Submodulen, Compiler, Python-Paketen, Buildlog und Firmware-Prüfsumme hinzu.
Auch bei fehlgeschlagener Kompilierung werden vorhandene Logs hochgeladen.
Im Actions-Tab den Lauf **Build QMK firmware** und dessen **Artifacts** öffnen.

Die Preonic-Veröffentlichung unter `latest` bleibt auf `main` erhalten.
Sie wartet auf den Abschluss der Matrix, wird aber auch bei einem fehlgeschlagenen
Corne-Job ausgeführt. Ohne erfolgreich hochgeladenes Preonic-Artefakt wird die
vorherige Veröffentlichung nicht gelöscht. Pull Requests veröffentlichen keine
Releases. Corne-Firmware bleibt als unabhängiges Actions-Artefakt verfügbar.

Es wurde kein lokaler Firmware-Build ausgeführt. Alle Firmware-Builds finden
in GitHub Actions statt. Es wurden keine anderen Repositories verändert.

## Belegung

Alle acht Layer wurden positionsgetreu aus der ZMK-Datei übertragen:
`macos`, `num`, `sym`, `nav`, `win`, `short`, `numpad`, `sys`.
Die ersten beiden Reihen enthalten jeweils 14 Tasten inklusive zweier innerer
Zusatztasten, die dritte 12 und die Daumenreihe 6: insgesamt 46 pro Layer.
Die vier inneren Zusatztasten bleiben wie in ZMK auf allen Layern deaktiviert.
Die Diagramme direkt über den QMK-Layern zeigen jede physische Position.

- Linke HRMs: A/Ctrl, S/Cmd, D/Alt, F/Shift.
- Rechte HRMs: J/RShift, K/RAlt, L/RCmd, Semikolon/RCtrl.
- Linke äußere Home-Row-Taste: Spotlight (Cmd+Space) / linker Hyper.
- Rechte äußere Home-Row-Taste: Quote / linker Meh (Ctrl+Alt+Shift), wie in ZMK.
- Daumen links: Esc/NAV, Backspace/NUM, Tab/WIN.
- Daumen rechts: Enter/NUMPAD, Space/SYM, Caps-Word-Toggle/SHORT.
- Äußere linke Taste der dritten Reihe: Equal/SHORT.
- NUMPAD verwendet normale Ziffern und Operatoren wie die Vorlage, keine
  abweichenden HID-Keypad-Keycodes. Komma/Punkt ist Tap/Hold, kein Shift-Mod-Morph.
- `win` ist der vorhandene macOS-Fenster-Shortcut-Layer, kein Windows-/Xbox-Layer.
- SYS unten links: `QK_RBT`, `QK_BOOT`, `EE_CLR`; unten rechts gespiegelt:
  `EE_CLR`, `QK_BOOT`, `QK_RBT`. Die beiden `EE_CLR`-Positionen waren in ZMK frei.

Symbol- und Shortcut-Keycodes entsprechen den HID-Tasten/Modifiern der Vorlage.
Die tatsächliche Zeichenausgabe unter **EurKEY next** wurde nicht verifiziert;
deshalb verwenden die Diagramme QMK-Namen und behaupten keine Host-Zuordnungen.

## Tap/Hold und Startwerte

Verwendet werden ausschließlich QMKs eigene Tap-Hold-Verarbeitung, dokumentierte
Konfigurationsoptionen und Hooks. Es gibt keine eigene Timing-Engine und keine
Änderungen unter `quantum/`. Ausgangswerte für Hardwaretests:

| ZMK-Behavior | QMK-Umsetzung | Tapping Term / Quick Tap (ms) |
| --- | --- | --- |
| `hml` / `hmr` | Mod-Tap, Chordal Hold, Permissive Hold nur für HRMs | 240 / 160 |
| `hlt` | Layer-Tap, Hold-on-other-key-press | 180 / 0 |
| `rhlt` (Tab/WIN) | Layer-Tap, Hold-on-other-key-press, Quick Tap | 180 / 160 |
| `rlt` (Enter/NUMPAD) | Layer-Tap, normale Tap-bevorzugende QMK-Entscheidung | 220 / 200 |
| `lcw` | Layer-Tap auf SHORT; Tap ruft `caps_word_toggle()` auf | 180 / 0 |
| normales `lt` (Equal/SHORT) | Layer-Tap, Tap-bevorzugung | 180 / 0 |
| normales `mt` (Spotlight/Hyper, Quote/Meh, Komma/Punkt) | Hold-on-other-key-press | 200 / 0 |

Die längeren HRM- und Enter-Zeitfenster sollen Tap-Rolls ermöglichen; die kürzeren
Hold-bevorzugenden Layer-Taps sollen beim Chorden zügig reagieren. Quick Tap
bleibt nur für die in der Quelle wiederholbaren Tasten aktiv. Die Werte sind
bewusst neu gewählte QMK-Startwerte; eine Verhaltensgleichheit ist damit noch
nicht nachgewiesen. Anpassungen erfolgen nach Tipp- und Wiederholungstests.

`chordal_hold_layout` kennzeichnet jede Hand explizit und alle sechs Daumentasten
mit `'*'`. `get_chordal_hold()` begrenzt die Handregel auf die acht HRMs, sodass
andere Dual-Role-Tasten mit beiden Händen funktionieren. `get_permissive_hold()`
nähert ZMK `balanced` über verschachtelte Tastendrücke an. `get_tapping_term()`
und `get_quick_tap_term()` unterscheiden die Behavior-Gruppen.

Spotlight, Caps Word/SHORT und Komma/Punkt verwenden die dokumentierte
[Interception von Mod-/Layer-Taps](https://docs.qmk.fm/mod_tap#intercepting-mod-taps)
in `process_record_user()`. QMK entscheidet dabei weiterhin Tap oder Hold.
Ein gehaltener Punkt wird als Key-down/Key-up gesendet und kann am Host wiederholen.

## Verbleibende Abweichungen und Alternativen

| Bereich | Verhalten und Grenze | Mögliche Alternative |
| --- | --- | --- |
| `hold-trigger-on-release` | Chordal Hold entscheidet bei gleichhändigen Kombinationen bereits beim Drücken der zweiten Taste auf Tap. ZMK wartet bei dieser Option auf deren Loslassen. Mehrtastenfolgen können deshalb unterschiedlich ausfallen. | Standard-QMK behalten und HRM-Timings nach Hardwaretests anpassen; bei Bedarf die dokumentierte Handregel gezielt ändern. |
| Mehrere gleichhändige HRMs | QMK erlaubt bestimmte gestapelte Mod-Tap-Chords trotz Handregel; das ist keine exakte Nachbildung der ZMK-Triggerliste. | Chords praktisch testen; gegebenenfalls einen dokumentierten alternativen HRM-Ansatz wählen. |
| Quick Tap | QMK begrenzt Quick Tap auf den Tapping Term und unterscheidet sich bei Wiederholungs-/Unterbrechungsfolgen von ZMK. Die ZMK-Werte 200/250 werden deshalb nicht unverändert übernommen. | Eigene QMK-Werte nach Repeat-Tests abstimmen. |
| Caps Word | Toggle, unbegrenzte Leerlaufdauer, Buchstaben, auch implizit geshiftete Ziffern, Unterstrich, Backspace und Delete sind übernommen. Deaktivierte Tasten verändern den Zustand nicht. Ein normaler Bindestrich beendet Caps Word wie in ZMK; Shift setzt es fort. QMK beendet Caps Word beim Aktivieren von Ctrl/Cmd/linkem Alt, während ZMK reine Modifier passieren lässt. | Dokumentiertes Standard-QMK-Verhalten akzeptieren; keine Umgehung der Tastenverarbeitung. |
| `C_VOICE_COMMAND` | SHORT, dritte Reihe, rechte zweite Taste: deaktiviert. ZMK sendet Consumer Usage `0xCF`; QMK `KC_ASST` sendet stattdessen `0x1CB` und wäre kein gleichwertiger Port. | Nach Absprache einen in macOS konfigurierten Shortcut oder `KC_ASST` verwenden. |
| `C_PWR` | SYS oben rechts: deaktiviert. ZMK nutzt Consumer Power `0x30`; QMK `KC_PWR` nutzt System Power und hat andere Semantik. | Explizit gewünschten macOS-Energie-Shortcut oder bewusst System Power festlegen. |
| Bluetooth / externe Versorgung | Die fünf Profilplätze, BT-Clear und External-Power-Toggle bleiben deaktiviert; diese kabelgebundene RP2040-Definition stellt die ZMK-Funktionen nicht bereit. | Keine Firmware-Nachbildung; gegebenenfalls geeignete Hardware wählen. |
| Studio | `studio_unlock` bleibt deaktiviert. | Änderungen in der versionierten QMK-Keymap. |
| RGB / Schlafen | Hersteller-RGB-Matrix und Encoder erhalten; SYS steuert RGB Matrix. Persönliche Defaults: Hue 142, Sat 250, Value 51; fünf Minuten RGB-Leerlaufabschaltung, Helligkeitsschritt 13. Herstellerlimit 100/255 bleibt bestehen. ZMK-Effekte, Wireless-Deep-Sleep nach 30 Minuten und BLE-Energieverwaltung werden nicht nachgebildet. | Standard-RGB-Matrix-Effekte am Gerät auswählen; Defaults gelten nur ohne gespeicherte Einstellungen. |
| OLED / Encoder | Hersteller-Konfiguration bleibt aktiviert; vier Encoder-Aktionen gelten auf allen persönlichen Layern. Es wird keine zusätzliche Display-Oberfläche eingeführt. Der Hersteller verwendet teilweise gemeinsame I2C-/Encoder-Pins. | Tatsächliche Bestückung und optionale Peripherie prüfen; Pinänderungen nur anhand bestätigter Hardwaredaten. |
| Split-Systemaktionen | `QK_BOOT`, `QK_RBT` und `EE_CLR` sind von beiden Seiten erreichbar, wirken bei normalem Split-Betrieb auf den USB-Master. Das Betätigen auf einer Seite adressiert nicht automatisch deren MCU. | Für die andere Hälfte deren vorhandene physische BOOT-/RESET-Wege verwenden; kein eigener Split-RPC in dieser Version. |

Die SYS-Tasten wurden nur belegt, nicht betätigt. Es wurden kein EEPROM-Reset,
keine Flash-Löschung und kein Flashen ausgeführt.

## Prüfung und Nachweise

Die Hardware wurde vor Beginn der persönlichen Portierung separat mit der
Herstellerbelegung geprüft:

- [Standard-Build mit Mainline-Tri-Layer-Option erfolgreich](https://github.com/basch-de/qmk_userspace/actions/runs/42490114024),
  Userspace-Commit `a156ac1f`.
- [Preonic am selben Stand erfolgreich](https://github.com/basch-de/qmk_userspace/actions/runs/42490114445).

Auch die vollständige Portierung an Commit `d78254a3` wurde online erfolgreich
kompiliert:

| Prüfung | Ergebnis |
| --- | --- |
| [Corne `default` und `basch_de`](https://github.com/basch-de/qmk_userspace/actions/runs/42494150245) | Beide Matrix-Jobs erfolgreich, beide UF2-Artefakte vorhanden |
| [Preonic einschließlich bestehendem Publish-Job](https://github.com/basch-de/qmk_userspace/actions/runs/42494150831) | Erfolgreich, unabhängig vom Corne-Workflow |

UF2-Artefakte dieses geprüften Portierungsstands:
[persönliche Keymap](https://github.com/basch-de/qmk_userspace/actions/runs/42494150245/artifacts/13622721652)
und [Herstellerbelegung](https://github.com/basch-de/qmk_userspace/actions/runs/42494150245/artifacts/13622148764).

Für die persönliche Portierung wurden alle **368 Layerpositionen** statisch mit
der gepinnten ZMK-Quelldatei verglichen, einschließlich der ausdrücklich oben
aufgeführten Ausnahmen. Zusätzlich wurden Layoutgröße, eindeutige Matrixpositionen,
Hand-/Daumenzuordnung, RGB-LED-Zahl, JSON und unveränderte Preonic-Dateien geprüft.
Die abschließenden Logs und UF2-Dateien sind bei den
[Actions-Läufen auf main](https://github.com/basch-de/qmk_userspace/actions?query=branch%3Amain)
für den jeweiligen Commit zu finden. Ein grüner Build bestätigt Kompilierbarkeit,
keine Hardwarefunktion.

Noch an der Tastatur zu testen:

1. Alle 46 Positionen und acht Layer; beide NUMPAD-Toggle-Wege und Rückkehr.
2. Gleichhändige Rolls, gegenüberliegende HRM-Chords, mehrere Modifier und alle
   sechs Daumentasten als HRM-Trigger; gedrückte/losgelassene Reihenfolgen.
3. Tap-Hold-Grenzen, schnelles Tap-dann-Halten von Tab/Enter, Buchstabenwiederholung,
   Hyper/Spotlight, Caps Word/SHORT und Komma/Punkt einschließlich Host-Repeat.
4. EurKEY-next-Zeichen, Option-/Cmd-Kombinationen, Screenshot-/Fenster-Shortcuts.
5. Split-Kommunikation, USB-Master auf beiden Seiten, RGB/Idle und vorhandene Encoder/OLED.
   Systemtasten erst bei bewusst gewünschtem Neustart/Bootloader/EEPROM-Reset testen.

Referenzen: [Tap-Hold / Chordal Hold](https://docs.qmk.fm/tap_hold),
[Caps Word](https://docs.qmk.fm/features/caps_word),
[External Userspace](https://docs.qmk.fm/newbs_external_userspace),
[Split Keyboard](https://docs.qmk.fm/features/split_keyboard).
