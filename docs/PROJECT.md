# QMK External Userspace: Projektdokumentation

Dieses Projekt enthält zwei persönliche `basch_de`-Keymaps in einem gemeinsamen
QMK External Userspace. Firmware-Basis ist offizielles Mainline-QMK. Für die Corne
wird nur die Hardwaredefinition im Actions-Checkout ergänzt; Vial-/Studio-
Firmwarekomponenten und Änderungen am QMK-Kern sind nicht enthalten.

| Tastatur | Hardware | Persönliche Keymap |
| --- | --- | --- |
| Preonic Drop rev3 | 60 einzelne 1u-Tasten, fünf Reihen mit zwölf Spalten | `keyboards/preonic/keymaps/basch_de/` |
| Keebart Corne MX Pro Standard | RP2040, 46 Tasten, Reihen mit 14 + 14 + 12 + 6 Positionen | `keyboards/keebart/corne_mx_pro/keymaps/basch_de/` |

Beide Tastaturen werden hauptsächlich unter macOS mit EurKEY next verwendet.
Die [README](../README.md) ist der kurze Einstieg;
[AGENTS.md](../AGENTS.md) enthält die Arbeitsregeln.

## Architektur und Builds

`qmk.json` enthält die persönlichen Targets:

| Tastatur | Keymap | Workflow |
| --- | --- | --- |
| `preonic/rev3_drop` | `basch_de` | `build.yml`, Variante `preonic-personal` |
| `keebart/corne_mx_pro/standard` | `basch_de` | `build.yml`, Variante `corne-standard-basch_de` |

Der gemeinsame Workflow `.github/workflows/build.yml` folgt dem Buildmuster
des Studio-Projekts: unabhängige Matrix-Jobs, isolierte Hersteller-Userspaces
und getrennte Firmware-/Provenance-Artefakte. Die Container-Auswahl folgt dem
offiziellen QMK-Workflow mit `latest`.
Firmware-Basis bleibt offizielles Mainline-QMK. Die bisherigen zwei Workflows
wurden durch diese eine Datei ersetzt.

Die zusätzlichen Varianten `preonic-default` und `corne-standard-default` bauen
die Hersteller-Keymaps als Hardware-Referenzen ohne persönliche Keymap-Dateien.
Alle vier Varianten laufen
mit `fail-fast: false`; jeder Job kompiliert ausschließlich sein explizites
Target mit `qmk mass-compile`. Die versionierte `qmk.json` wird nicht verändert.
Nur die Corne-Jobs installieren das Hardware-Overlay. Beide persönlichen
Keymaps trennen Belegung und Diagramme (`keymap.c`) von der Verhaltenslogik
(`behaviors.c`); gemeinsame Layernamen und Dual-Role-Aliase stehen jeweils in
`keymap_defs.h`. Diese Aufteilung ändert weder Belegung noch Verhalten.

Pro Lauf wird der aktuelle Mainline-`master` einmal für alle vier Varianten
aufgelöst. Es gibt keinen dauerhaften Firmware-Commit-Pin mehr.
Ein neuer QMK-Commit startet keinen Lauf in diesem Repository; der nächste
Push, Pull Request oder manuelle Start übernimmt den dann aktuellen Stand.

Erwartete Firmware-Artefakte:

- `preonic-basch_de`: BIN der persönlichen Preonic-Keymap.
- `preonic-default`: BIN der originalen Mainline-Preonic-Standardbelegung.
- `corne-standard-default`: UF2 der Herstellerbelegung.
- `corne-standard-basch_de`: UF2 der persönlichen Corne-Keymap.

Zu jeder Variante kommt ein `provenance-…`-Artefakt mit QMK-/Userspace-Commit,
Submodulen, Compiler, Python-Paketen, Buildlog und Firmware-Prüfsumme hinzu.
Auch bei fehlgeschlagener Kompilierung werden vorhandene Logs hochgeladen.
Im Actions-Tab den Lauf **Build QMK firmware** und dessen **Artifacts** öffnen.

Alle vier Varianten werden gleichberechtigt ausschließlich als Actions-
Artefakte bereitgestellt. Erfolgreiche Varianten liefern ihre Dateien auch bei
Fehlern anderer Varianten. Es gibt keinen Publish-Job und keine automatische
Release- oder Tag-Veröffentlichung mehr. Ein vorhandener alter Preonic-Release
`latest` bleibt ein historischer Stand und wird nicht weiter aktualisiert.
Aktuelle Firmware und Buildnachweise stehen beim jeweiligen Actions-Lauf;
ihre Verfügbarkeit unterliegt der Aufbewahrungsrichtlinie des Repositories.

Die persönlichen Varianten führen zusätzlich die in [tests/README.md](../tests/README.md)
beschriebenen nativen QMK-Tests aus. Sie verwenden die echten Produktions-Keymaps,
Timing-Hooks und QMK-Verarbeitung einschließlich der erzeugten Tastaturberichte.
Abgedeckt sind Struktur und kritische Layer-/SYS-Zugänge, HRMs, Daumentasten,
Quick Tap und eigene Dual-Role-Aktionen. Testlogs und die verwendeten
Hardware-Metadaten werden mit den bestehenden Provenance-Artefakten gespeichert.
Die Herstellerbelegungen bleiben unabhängige Kompilierungsprüfungen.

Es wurde kein lokaler Firmware-Build ausgeführt. Alle Firmware-Builds finden
in GitHub Actions statt. Es wurden keine anderen Repositories verändert.

### Container und Python-Abhängigkeiten

Der gemeinsame Workflow verwendet direkt:

```yaml
container: ghcr.io/qmk/qmk_cli:latest
```

Das entspricht der Container-Auswahl im
[offiziellen QMK-Userspace-Workflow](https://github.com/qmk/.github/blob/main/.github/workflows/qmk_userspace_build.yml).
Es wird kein eigener Image-Digest festgeschrieben oder aus einem anderen Projekt
übernommen. Jede Buildvariante zieht das unter `latest` verfügbare Image.
Ein neues Image allein startet keinen Workflow-Lauf in diesem Repository.

Wie im offiziellen QMK-Workflow wird nach dem Firmware-Checkout
`pip install -r firmware/requirements.txt` ausgeführt. Dadurch werden die
Python-Abhängigkeiten des verwendeten QMK-Stands installiert. Die tatsächlich
verwendeten Paketversionen dokumentiert `pip freeze` im Provenance-Artefakt.

### Reproduzierbarkeit

Das tatsächlich gezogene Container-Image ist im Actions-Log der
Container-Initialisierung nachvollziehbar.

Der Tag `latest` ist beweglich. Auch die Firmware folgt dem aktuellen
Mainline-`master`; die Python-Pakete folgen dessen Anforderungen. Damit wird die
Buildumgebung automatisch aktualisiert; ein identischer Userspace-Commit allein
garantiert keinen vollständig identischen späteren Build. Alle vier Varianten
verwenden denselben einmal pro Workflow-Lauf aufgelösten Firmware-Commit.

## Preonic Drop rev3

Die Preonic verwendet 60 unabhängige 1u-Tasten im Raster 5 × 12; die ehemalige
zentrale 2u-Leertaste ist aufgeteilt. Maßgeblich sind die Belegungen und Diagramme
in `keyboards/preonic/keymaps/basch_de/keymap.c`.

Die Layer heißen QWERTY, GAMING, LOWER, RAISE, ADJUST und WINDOW.
LOWER und RAISE zusammen aktivieren ADJUST. Eigene Dual-Role-Aktionen sind
Spotlight/Ctrl und Option-Backspace/WINDOW. Diese Hooks liegen in `behaviors.c`;
QMK entscheidet weiterhin Tap oder Hold. WINDOW ist derzeit transparent.
Physische DIP-Schalter und Encoder sind deaktiviert, da sie nicht installiert sind.
Der bisherige Gaming-Layer wird durch die Corne-Portierung nicht erweitert.

Die nativen Preonic-Tests prüfen kritische Layer-/Systemzugänge, ADJUST,
Gaming-Zugang sowie beide eigenen Dual-Role-Aktionen. Tap-Hold-Gefühl und
Hostausgabe bleiben an der Tastatur zu prüfen.

## Corne MX Pro: ZMK-Portierung

### Quellen und geprüfte Versionen

- [Mainline QMK](https://github.com/qmk/qmk_firmware/tree/d194c077ed964195ec16d255c7a4b89a794cf03b),
  bei der ursprünglichen Portierung geprüfter Commit
  `d194c077ed964195ec16d255c7a4b89a794cf03b`. Aktuelle Builds folgen für beide
  Tastaturen `master`; der tatsächlich verwendete Commit steht im Buildnachweis.
- [Keebart-Hardwaredefinition](https://github.com/Keebart/vial-qmk-keebart/tree/63e2d6248209f1926e60daa5b950c771cf09d837/keyboards/keebart/corne_mx_pro),
  Branch `vial`, Commit `63e2d6248209f1926e60daa5b950c771cf09d837`.
  Übernommene Dateien und minimale Mainline-Anpassungen stehen in
  [vendor/qmk/README.md](../vendor/qmk/README.md).
- [Tatsächliche ZMK-Keymap](https://github.com/basch-de/zmk-config/blob/17dc18d4065161066a459656a87f36f11cd4ae88/config/corne_choc_pro.keymap)
  und [Konfiguration](https://github.com/basch-de/zmk-config/blob/17dc18d4065161066a459656a87f36f11cd4ae88/config/corne_choc_pro.conf),
  Commit `17dc18d4065161066a459656a87f36f11cd4ae88`. Deren `west.yml` verwendet
  ZMK `v0.3`; dessen Standarddefinitionen für `mt`, `lt` und Caps Word wurden
  zusätzlich geprüft.

### Belegung

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
- SHORT, dritte Reihe, rechte zweite Taste: `KC_ASST` (QMK Assistant).
- SYS oben rechts: `KC_PWR` (QMK System Power).
- SYS unten links: `QK_RBT`, `QK_BOOT`, `EE_CLR`; unten rechts gespiegelt:
  `EE_CLR`, `QK_BOOT`, `QK_RBT`. Die beiden `EE_CLR`-Positionen waren in ZMK frei.

Symbol- und Shortcut-Keycodes entsprechen den HID-Tasten/Modifiern der Vorlage.
Die tatsächliche Zeichenausgabe unter **EurKEY next** wurde nicht verifiziert;
deshalb verwenden die Diagramme QMK-Namen und behaupten keine Host-Zuordnungen.

### Tap/Hold und Startwerte

Verwendet werden ausschließlich QMKs eigene Tap-Hold-Verarbeitung, dokumentierte
Konfigurationsoptionen und Hooks. Es gibt keine eigene Timing-Engine und keine
Änderungen unter `quantum/`. Ausgangswerte für Hardwaretests:

| ZMK-Behavior | QMK-Umsetzung | Tapping Term / Quick Tap (ms) |
| --- | --- | --- |
| `hml` / `hmr` | Mod-Tap, Chordal Hold, Permissive Hold nur für HRMs | 250 / 200 |
| `hlt` | Layer-Tap, Hold-on-other-key-press | 200 / 0 |
| `rhlt` (Tab/WIN) | Layer-Tap, Hold-on-other-key-press, Quick Tap | 200 / 200 |
| `rlt` (Enter/NUMPAD) | Layer-Tap, normale Tap-bevorzugende QMK-Entscheidung | 200 / 200 |
| `lcw` | Layer-Tap auf SHORT; Tap ruft `caps_word_toggle()` auf | 200 / 0 |
| normales `lt` (Equal/SHORT) | Layer-Tap, Tap-bevorzugung | 200 / 0 |
| normales `mt` (Spotlight/Hyper, Quote/Meh, Komma/Punkt) | Hold-on-other-key-press | 200 / 0 |

Die 250 ms für HRMs mit Permissive Hold und Chordal Hold folgen dem Startvorschlag
der [offiziellen QMK-Dokumentation](https://docs.qmk.fm/tap_hold#configuring-home-row-mods)
und [Pascal Getreuers HRM-Leitfaden](https://getreuer.info/posts/keyboards/hrms-are-hard/index.html).
Alle anderen Dual-Role-Tasten verwenden QMKs allgemeinen Standard von 200 ms.
Permissive Hold beziehungsweise Hold-on-other-key-press können einen Hold bereits
vor Ablauf dieser Frist entscheiden. Die frühere Staffelung mit 180/220/240 ms
war heuristisch gewählt und wurde ohne Nachweis eines Vorteils durch diese
einfachere Ausgangskonfiguration ersetzt.

Quick Tap ist nur für die in der Quelle wiederholbaren Tasten aktiv: HRMs,
Tab und Enter verwenden jeweils 200 ms; alle anderen Dual-Role-Tasten 0 ms.
Der HRM-Wert erhält die in ZMK gewählten 200 ms. Die ZMK-Werte von 250 ms für
Tab und Enter werden auf deren QMK-Tapping-Term von 200 ms begrenzt.
Eine zusätzliche Verkürzung auf 160 ms ist nicht erforderlich. Quick Tap wird
anhand von Wiederholungen und schnellen Wechseln zum Hold geprüft; gleiche
Zahlen allein beweisen keine Verhaltensgleichheit mit ZMK.

`chordal_hold_layout` kennzeichnet jede Hand explizit und alle sechs Daumentasten
mit `'*'`. `get_chordal_hold()` begrenzt die Handregel auf die acht HRMs, sodass
andere Dual-Role-Tasten mit beiden Händen funktionieren. `get_permissive_hold()`
nähert ZMK `balanced` über verschachtelte Tastendrücke an. `get_tapping_term()`
und `get_quick_tap_term()` unterscheiden die Behavior-Gruppen.

Spotlight, Caps Word/SHORT und Komma/Punkt verwenden die dokumentierte
[Interception von Mod-/Layer-Taps](https://docs.qmk.fm/mod_tap#intercepting-mod-taps)
in `process_record_user()`. QMK entscheidet dabei weiterhin Tap oder Hold.
Ein gehaltener Punkt wird als Key-down/Key-up gesendet und kann am Host wiederholen.

### Verbleibende Abweichungen und Alternativen

| Bereich | Verhalten und Grenze | Mögliche Alternative |
| --- | --- | --- |
| `hold-trigger-on-release` | Chordal Hold entscheidet bei gleichhändigen Kombinationen bereits beim Drücken der zweiten Taste auf Tap. ZMK wartet bei dieser Option auf deren Loslassen. Mehrtastenfolgen können deshalb unterschiedlich ausfallen. | Standard-QMK behalten und HRM-Timings nach Hardwaretests anpassen; bei Bedarf die dokumentierte Handregel gezielt ändern. |
| Mehrere gleichhändige HRMs | QMK erlaubt bestimmte gestapelte Mod-Tap-Chords trotz Handregel; das ist keine exakte Nachbildung der ZMK-Triggerliste. | Chords praktisch testen; gegebenenfalls einen dokumentierten alternativen HRM-Ansatz wählen. |
| Quick Tap | QMK begrenzt Quick Tap auf den Tapping Term und unterscheidet sich bei Wiederholungs-/Unterbrechungsfolgen von ZMK. HRMs behalten 200 ms; Tab und Enter verwenden wegen dieser Grenze 200 statt der ZMK-250 ms. | Werte nach Repeat-Tests abstimmen. |
| Caps Word | Auf Nutzerauftrag QMK-Standard ohne eigenen Fortsetzungs-Hook oder Timeout-Override: aktuell fünf Sekunden Idle-Timeout, Buchstaben werden großgeschrieben und `KC_MINS` wird zu Unterstrich und setzt das Wort fort. Ziffern, `KC_UNDS`, Backspace und Delete setzen es ebenfalls fort; Shift und andere worttrennende Tasten beenden es. Das unterscheidet sich bewusst von der ZMK-Vorlage. Caps-Word-Toggle/SHORT bleibt erhalten. | Hostausgabe und Bedienung an der Tastatur prüfen; keine eigene Caps-Word-Verarbeitung ergänzen. |
| `C_VOICE_COMMAND` | Auf Nutzerauftrag durch QMK `KC_ASST` (Assistant) an derselben Position ersetzt. ZMK sendet Consumer Usage `0xCF`; QMK sendet `0x1CB`. Damit ist die Taste belegt, aber die HID-Aktion unterscheidet sich. | Hostwirkung unter macOS prüfen; bei Bedarf einen dort konfigurierten Shortcut festlegen. |
| `C_PWR` | Auf Nutzerauftrag durch QMK `KC_PWR` (System Power) an derselben Position ersetzt. ZMK nutzt Consumer Power `0x30`; QMK nutzt System Power mit anderer Semantik. | Gewählte System-Power-Aktion bewusst am Host prüfen. |
| Bluetooth / externe Versorgung | Die fünf Profilplätze, BT-Clear und External-Power-Toggle bleiben deaktiviert; diese kabelgebundene RP2040-Definition stellt die ZMK-Funktionen nicht bereit. | Keine Firmware-Nachbildung; gegebenenfalls geeignete Hardware wählen. |
| Studio | `studio_unlock` bleibt deaktiviert. | Änderungen in der versionierten QMK-Keymap. |
| RGB / Schlafen | Hersteller-RGB-Matrix erhalten; SYS steuert RGB Matrix. Auf Nutzerauftrag QMK-Standard ohne LED-Leerlaufabschaltung; `RGB_MATRIX_SLEEP` aus der Hardwaredefinition schaltet die Beleuchtung beim Host-Suspend aus. Persönliche Farbdefaults: Hue 142, Sat 250, Value 51; Helligkeitsschritt 13. Herstellerlimit 100/255 bleibt bestehen. ZMK-Effekte, Wireless-Deep-Sleep nach 30 Minuten und BLE-Energieverwaltung werden nicht nachgebildet. | Standard-RGB-Matrix-Effekte am Gerät auswählen; Farbdefaults gelten nur ohne gespeicherte Einstellungen. |
| OLED / Encoder | Die persönliche Corne hat keine Encoder. `ENCODER_ENABLE` und `ENCODER_MAP_ENABLE` sind dort deaktiviert; die persönliche Encoder-Map entfällt. Alle 46 Tastenpositionen bleiben erhalten. Hersteller-Hardwaredefinition, `default`-Keymap und OLED-Konfiguration bleiben unverändert. Es wird keine zusätzliche Display-Oberfläche eingeführt. | Optionale Peripherie nur passend zur tatsächlichen Bestückung aktivieren; Pinänderungen nur anhand bestätigter Hardwaredaten. |
| Split-Systemaktionen | `QK_BOOT`, `QK_RBT` und `EE_CLR` sind von beiden Seiten erreichbar, wirken bei normalem Split-Betrieb auf den USB-Master. Das Betätigen auf einer Seite adressiert nicht automatisch deren MCU. | Für die andere Hälfte deren vorhandene physische BOOT-/RESET-Wege verwenden; kein eigener Split-RPC in dieser Version. |

Die SYS-Tasten wurden nur belegt, nicht betätigt. Es wurden kein EEPROM-Reset,
keine Flash-Löschung und kein Flashen ausgeführt.

## Prüfstand und Hardwaretests

Die folgenden Nachweise beziehen sich auf die jeweils genannten historischen
Revisionen. Sie bestätigen keine späteren Keymap- oder Timingänderungen.

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
| [Preonic einschließlich damaligem Publish-Job](https://github.com/basch-de/qmk_userspace/actions/runs/42494150831) | Erfolgreich, unabhängig vom Corne-Workflow |

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
5. Split-Kommunikation, USB-Master auf beiden Seiten, RGB/Host-Suspend und gegebenenfalls OLED.
   Systemtasten erst bei bewusst gewünschtem Neustart/Bootloader/EEPROM-Reset testen.

Referenzen: [Tap-Hold / Chordal Hold](https://docs.qmk.fm/tap_hold),
[Caps Word](https://docs.qmk.fm/features/caps_word),
[External Userspace](https://docs.qmk.fm/newbs_external_userspace),
[Split Keyboard](https://docs.qmk.fm/features/split_keyboard).

## Manueller Export für Keebart Studio

`exports/` ist ein lokaler, Git-ignorierter Ausgabeordner. Die aktuell
importierbare Datei liegt unter
`exports/corne_mx_pro_basch_de/basch_de.keebart`.

Der Export wurde manuell aus der Corne-Keymap und ihren Behaviors in ein natives
Studio-Profil übertragen. Änderungen an den QMK-Quelldateien aktualisieren ihn
nicht automatisch. Grundlage war eine Sicherung aus Studio 0.7.2. Die
QMK-Quelldateien bleiben die maßgebliche Mainline-Konfiguration; der Export
ist keine Firmwarekomponente und wird von den QMK-Builds nicht verwendet.

Der zusammengeführte C-Zwischenstand wurde entfernt: Studio konnte dessen
QMK-Hooks nicht importieren. Am 2026-11-09 hat der Nutzer den erfolgreichen
Import der korrigierten `.keebart`-Datei und erstes Tippen auf der Tastatur
bestätigt. Gezielte Verhaltenstests stehen weiterhin aus.

### Übertragene Daten

- Alle 368 physischen Belegungen auf acht benannten Layern in der 8×7-Matrix.
- 16 Layerplätze bleiben erhalten; nur die ersten acht sind sichtbar.
- 19 Studio-Compound-Aktionen bilden die QMK-Dual-Role-Tasten und abgefangenen Taps ab.
- HRMs: 250 ms, Permissive Hold, Chordal Hold, 200 ms Quick Tap.
- Andere Dual-Role-Tasten: 200 ms; Quick Tap für Tab und Enter 200 ms, sonst 0.
- Sechs Daumentasten als Chordal-Hold-Ausnahmen. `chordal_exempt` enthält
  Matrixpositionsnummern (`row * 7 + col`): `[24,25,26,52,53,54]`.
  Die ursprünglichen `{row, col}`-Objekte verursachten den inzwischen behobenen
  Importfehler `invalid type: map, expected u8`.
- Spotlight/Hyper, Caps Word/SHORT, Komma/Punkt, Assistant und System Power.
- Ohne physische Encoder sind alle Drehaktionen unbelegt. Das Geräteschema
  behält vier leere Encoderplätze je Layer; `encoder_views` bleibt leer.
  Alle 46 normalen Tastenpositionen bleiben verfügbar.
- Kein eigener LED-Inaktivitäts-Timeout; es gilt der Firmware-Standard.
  Farben, Helligkeit, Computerprofil, Geräteidentität und Hardware-Metadaten
  stammen aus der ursprünglichen Sicherung.
- Last-verified- und Checkpoint-Daten stammen ebenfalls aus der Sicherung.
  Sie belegen keine Anwendung oder Prüfung des neuen Profils.

### Unterschiede und Prüfstand

- Studio verwendet eine eigene Compound-Engine. Die QMK-Callbacks sind in
  Einstellungen übersetzt und werden nicht ausgeführt. Timing, Tastenkombinationen
  und Loslassen müssen noch geprüft werden, einschließlich der unbelegten inneren
  Tasten und der Wiederholung beim gehaltenen Punkt.
- Mainline verwendet Standard-QMK-Caps-Word ohne eigenen Fortsetzungs-Hook oder
  Timeout-Override. Das Studio-Profil verwendet den Caps-Word-Toggle der Firmware.
  Deren Verhalten muss noch an der Tastatur geprüft werden; die zugehörigen
  Firmwareoptionen sind nicht im Backup hinterlegt.
- Mainline-RGB-Startwerte und `RGB_MATRIX_VAL_STEP=13` werden einkompiliert.
  Der Import behält die Beleuchtungskonfiguration aus der Studio-Sicherung.
- JSON, Matrix-/Aktionsreferenzen und Prüfsumme wurden statisch geprüft.
  Import und erstes Tippen sind vom Nutzer bestätigt. Vollständige
  Tap/Hold-Gleichheit sowie alle Layer und Sonderaktionen sind noch nicht geprüft.

### Tap/Hold-Aktionen

| Slot | QMK-Belegung | Tap | Hold | Term (ms) | Quick Tap (ms) | Permissive | Tap bevorzugt | Chordal |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0 | `SYS_GRV` | `0x0035` | `0x5227` | 200 | 0 | False | False | False |
| 1 | `HYP_SPOT` | `0x082C` | `0x0F00` | 200 | 0 | False | False | False |
| 2 | `LCTL_T(KC_A)` | `0x0004` | `0x00E0` | 250 | 200 | True | False | True |
| 3 | `LGUI_T(KC_S)` | `0x0016` | `0x00E3` | 250 | 200 | True | False | True |
| 4 | `LALT_T(KC_D)` | `0x0007` | `0x00E2` | 250 | 200 | True | False | True |
| 5 | `LSFT_T(KC_F)` | `0x0009` | `0x00E1` | 250 | 200 | True | False | True |
| 6 | `RSFT_T(KC_J)` | `0x000D` | `0x00E5` | 250 | 200 | True | False | True |
| 7 | `RALT_T(KC_K)` | `0x000E` | `0x00E6` | 250 | 200 | True | False | True |
| 8 | `RGUI_T(KC_L)` | `0x000F` | `0x00E7` | 250 | 200 | True | False | True |
| 9 | `RCTL_T(KC_SCLN)` | `0x0033` | `0x00E4` | 250 | 200 | True | False | True |
| 10 | `MEH_T(KC_QUOT)` | `0x0034` | `0x0700` | 200 | 0 | False | False | False |
| 11 | `SHORT_EQL` | `0x002E` | `0x5225` | 200 | 0 | False | True | False |
| 12 | `NAV_ESC` | `0x0029` | `0x5223` | 200 | 0 | False | False | False |
| 13 | `NUM_BSPC` | `0x002A` | `0x5221` | 200 | 0 | False | False | False |
| 14 | `WIN_TAB` | `0x002B` | `0x5224` | 200 | 200 | False | False | False |
| 15 | `PAD_ENT` | `0x0028` | `0x5226` | 200 | 200 | False | True | False |
| 16 | `SYM_SPC` | `0x002C` | `0x5222` | 200 | 0 | False | False | False |
| 17 | `SHORT_CW` | `0x7C73` | `0x5225` | 200 | 0 | False | False | False |
| 18 | `COMM_DOT` | `0x0036` | `0x0037` | 200 | 0 | False | False | False |
