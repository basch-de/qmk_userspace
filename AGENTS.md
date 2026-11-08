# Projekt

Dieses Repository enthält die persönlichen Keymaps für zwei Tastaturen in
einem gemeinsamen QMK External Userspace. Beide verwenden die Keymap `basch_de`.

## Preonic Drop rev3

- Keyboard-Target: `preonic/rev3_drop`
- Verzeichnis: `keyboards/preonic/keymaps/basch_de/`
- Physische Belegung: 60 einzelne 1u-Tasten in einem Raster mit fünf Reihen
  und zwölf Spalten; die ehemalige zentrale 2u-Leertaste ist aufgeteilt.

## Keebart Corne MX Pro Standard

- Keyboard-Target: `keebart/corne_mx_pro/standard`
- Controller: RP2040
- Persönliche Keymap: `keyboards/keebart/corne_mx_pro/keymaps/basch_de/`
- Hardwaredefinition und Hersteller-Keymap `default`:
  `vendor/qmk/keyboards/keebart/corne_mx_pro/`
- Physische Belegung: 46 Tasten; die ersten beiden Reihen haben jeweils
  14 Positionen, die dritte 12 und die Daumenreihe sechs. Die vier inneren
  Zusatztasten sind eigenständige Positionen.
- Layout-Makro: `LAYOUT_split_3x6_3_ex2`
- Layer: `macos`, `num`, `sym`, `nav`, `win`, `short`, `numpad`, `sys`
- Portierungsquellen, Einschränkungen und Hardware-Testliste:
  `docs/corne-mainline.md`; Herkunft und Anpassungen des Hardware-Overlays:
  `vendor/qmk/README.md`.

# Arbeitsbereich

Änderungen erfolgen im Userspace-Projekt. Keine anderen Repositories verändern.
Änderungen an einer Tastatur dürfen die Konfiguration und Builds der anderen
nicht beeinträchtigen.

Wichtige Dateien:
- `keymap.c`: Tastenbelegung, Layer und eigene Logik
- `config.h`: QMK-Einstellungen
- `rules.mk`: Features und zusätzliche Quelldateien
- `qmk.json`: Build-Targets
- `.github/workflows/`: Online-Build-Konfiguration
- `vendor/qmk/`: Hardware-Overlay für die Corne; wird erst im Actions-Checkout
  in offizielles QMK kopiert
- `docs/corne-mainline.md`: dokumentierte Corne-Portierung und Abweichungen

Das veraltete lokale Verzeichnis `../qmk_firmware` darf nicht als fachliche
Referenz verwendet werden.

# Quellen und Versionen

Für QMK-APIs, Features und Konfiguration aktuelle offizielle Quellen aus dem
Internet prüfen:

- Dokumentation: https://docs.qmk.fm/
- Quellcode: https://github.com/qmk/qmk_firmware

Maßgeblich für die Kompatibilität ist der vom GitHub-Workflow verwendete
QMK-Commit beziehungsweise Branch der betroffenen Tastatur:

- Gemeinsamer Workflow: `.github/workflows/build.yml`.
- Preonic: aktueller Mainline-Branch `master`, pro Lauf auf einen Commit aufgelöst.
- Corne: auf einen Mainline-Commit gepinnt; beide Corne-Varianten verwenden
  innerhalb eines Laufs denselben Commit.

Bei versionsabhängigen Änderungen den jeweiligen Workflow prüfen und dazu
passende Dokumentation und Quellcode heranziehen. Die beiden Referenzen nicht
ohne Auftrag vereinheitlichen. Bei Hardware-Overlay-Updates die dokumentierte
Keebart-Quelle prüfen und notwendige Mainline-Anpassungen nachvollziehbar halten.

Firmware-Basis ist ausschließlich offizielles Mainline-QMK. Keine Änderungen
am QMK-Kern, insbesondere unter `quantum/`, und keine Vial- oder
Keebart-Studio-Abhängigkeiten einführen.

# Nutzung und Host-Layout

Die Tastaturen werden hauptsächlich unter macOS mit dem Host-Tastaturlayout
EurKEY next verwendet.

Sonderzeichen, Modifier und Makros auf diese Kombination abstimmen. Aus dem
Keymap-Namen `basch_de` kein deutsches QWERTZ-Hostlayout ableiten. Bei
layoutabhängigen Änderungen die tatsächlich verwendete EurKEY-next-Belegung
berücksichtigen; unklare Zuordnungen prüfen oder erfragen.

Langfristig ist ein Gaming-Layer für die Xbox vorgesehen. Diesen erst auf
konkreten Auftrag implementieren. Vorher gewünschte Belegung, unterstützte
Spiele und das auf der Xbox verwendete Tastaturlayout klären.

macOS-spezifische Shortcuts und Makros dürfen nicht ungeprüft in den Xbox-Layer
übernommen werden. Der Corne-Layer `win` enthält macOS-Fenster-Shortcuts und
ist kein Windows- oder Xbox-Layer.

# Änderungen

Bestehende Benennungen, Code-Stil und die tabellarische Darstellung der
Tastenbelegung erhalten.

## Darstellung der Tastenmatrix

- Jeden Layer in `keymap.c` entsprechend den physischen Tastenpositionen der
  jeweiligen Tastatur formatieren.
- Preonic: fünf Reihen mit jeweils zwölf Tasten, insgesamt 60 Belegungen.
  Auch die untere Reihe hat zwölf unabhängige Positionen; die mittleren
  Tasten in Spalte 6 und 7 separat darstellen. Keine Zellen für eine zentrale
  2u-Taste zusammenfassen.
- Corne: vier Belegungszeilen mit 14, 14, 12 und sechs Tasten, insgesamt
  46 Belegungen. Linke und rechte Hälfte, die vier inneren Zusatztasten und
  beide Daumencluster korrekt zuordnen. Die dritte Reihe hat keine inneren
  Zusatztasten; deren Lücke bei der Ausrichtung berücksichtigen.
- Tasten derselben physischen Spalte innerhalb eines Layers beginnen an
  derselben Zeichenposition.
- Spaltenbreiten für jeden Layer unabhängig anhand der längsten vollständigen
  Keycode-Ausdrücke bestimmen. Hinter dem Komma mindestens zwei Leerzeichen
  Abstand lassen. Spalten bei Änderungen nach Bedarf verbreitern oder verengen.
- Verschachtelte Ausdrücke wie `LT(_LOWER, KC_BSPC)` bleiben eine ungeteilte
  Zelle. Leerzeichen statt Tabs zur Ausrichtung verwenden.
- Beim Formatieren keine Keycodes, Argumente, Reihenfolge oder Funktion ändern.
- Die Belegungsdiagramme in den Kommentaren über allen Layern bei jeder
  Belegungsänderung aktualisieren. Sie müssen die tatsächlichen Keycodes und
  alle physischen Positionen der jeweiligen Tastatur wiedergeben.
- Tap/Hold-Funktionen und transparente beziehungsweise deaktivierte Tasten
  eindeutig kennzeichnen. Eine Legende für verwendete Abkürzungen pflegen.
- Spaltenbreiten der Diagramme pro Layer an die Beschriftungen anpassen.
  Hostabhängige Zeichenausgaben nur als solche beschriften, wenn die Zuordnung
  für EurKEY next geprüft ist; andernfalls QMK-Keycode-Namen verwenden.

Tastenbelegung und bestehendes Verhalten nur im Rahmen der angefragten
Änderung anpassen. Bestehende Wege zum Bootloader erhalten.

Neue Features bei Bedarf auch in `config.h` und `rules.mk` konfigurieren.
Kommentare sollen besondere Entscheidungen und nicht offensichtliches
Verhalten erklären.

Quelltext, Bezeichner und alle Kommentare in Quelldateien sowie `config.h`
und `rules.mk` auf Englisch verfassen. Die Kommunikation bleibt auf Deutsch.

## Corne-Verhalten und Portierungsgrenzen

- Ausschließlich dokumentierte Standard-QMK-Keycodes, Funktionen,
  Konfigurationsoptionen und offizielle Hooks/Callbacks verwenden. Eigene
  Keycodes und einfache C-Logik nur über die offizielle QMK-API umsetzen.
- Keine eigene Tap-Hold-Engine und keine undokumentierten Eingriffe in interne
  Strukturen oder die Tastenverarbeitung einführen.
- HRMs verwenden Chordal Hold und Permissive Hold mit expliziter Hand- und
  Daumenzuordnung. Layer-Taps und äußere Mod-Taps haben eigene Regeln.
  Unterschiede zu ZMK `balanced` und `hold-trigger-on-release` beachten.
- Tapping Terms und Quick-Tap-Werte sind QMK-Startwerte für Hardwaretests.
  ZMK-Timingwerte nicht ungeprüft übernehmen oder Verhaltensgleichheit behaupten.
- Nicht vollständig abbildbare ZMK-Funktionen und mögliche Alternativen in
  `docs/corne-mainline.md` dokumentieren. Deaktivierte Funktionen nicht ohne
  Auftrag durch vermeintlich ähnliche Host-Shortcuts oder HID-Keycodes ersetzen.
- SYS-Zugänge zu `QK_BOOT`, `QK_RBT` und `EE_CLR` auf beiden Seiten erhalten.
  Diese Standardaktionen betreffen im normalen Split-Betrieb den USB-Master,
  nicht automatisch die Hälfte, auf der die Taste gedrückt wurde.
- Split-Kommunikation, RGB und vorhandene Encoder/OLED erhalten. Pinänderungen
  nur anhand geprüfter Hardwaredaten vornehmen.

# Builds und Prüfung

Kompiliert wird ausschließlich online über GitHub Actions mit der dort
eingebundenen QMK-Version. Keine lokalen Builds ausführen.

Der gemeinsame Workflow `build.yml` hält die Builds unabhängig:

- Vier Matrix-Jobs bauen jeweils `default` und `basch_de` für Preonic und Corne.
  `fail-fast: false` verhindert, dass ein fehlgeschlagener Build andere abbricht.
- Jeder Job kompiliert nur sein explizites Target. Die versionierte `qmk.json`
  bleibt dabei unverändert und enthält beide persönlichen Targets.
- Nur die Corne-Jobs installieren das Hardware-Overlay. Beide `default`-Builds
  verwenden je einen separaten Userspace ohne persönliche Keymap-Dateien.
  Beide Preonic-Varianten verwenden denselben pro Lauf aufgelösten QMK-Commit.
- Firmware und Provenance werden je Variante als Actions-Artefakte gespeichert:
  QMK-/Userspace-Revisionen, Submodule, Compiler, Python-Pakete, Buildlog und
  Firmware-Prüfsumme. Der QMK-Container ist per Digest festgelegt.
- Die persönliche Preonic-Keymap behält ihr `Firmware`-Artefakt und die
  Veröffentlichung unter `latest` auf `main`. Fehler der anderen Varianten
  verhindern diese Veröffentlichung nicht; ohne persönliches Preonic-Artefakt
  bleibt die vorherige Veröffentlichung erhalten. Preonic `default` wird als
  separates `preonic-default`-BIN-Artefakt bereitgestellt.
- Pushes, Pull Requests und manuelle Starts nutzen denselben Workflow.
  Pull Requests veröffentlichen keine Releases. Keine Flash-Schritte ergänzen.

Bei Änderungen der Corne-Hardwaredefinition zuerst die Herstellerbelegung
`default` gegen Mainline-QMK prüfen, bevor die persönliche Keymap auf die
geänderte Hardwarebasis angepasst wird. Bei gemeinsamen Build-Änderungen beide
Tastaturen online prüfen, sofern die Workflow-Ausführung beauftragt ist.

Änderungen statisch auf Konsistenz prüfen. Ein erfolgreicher Build darf nur
behauptet werden, wenn das entsprechende GitHub-Build-Ergebnis für den
geprüften Änderungsstand vorliegt.

Ein erfolgreicher Build bestätigt die Kompilierbarkeit. Tap/Hold-Timing,
Combos und tatsächliche Zeichenausgabe müssen zusätzlich an der Tastatur
getestet werden; bei der Corne auch Split-Kommunikation, RGB und vorhandene
Encoder/OLED. Ausstehende Hardwaretests im Ergebnis benennen.

Pushes und manuelle Workflow-Ausführungen nur bei entsprechendem Auftrag
durchführen.

# Hardware

Firmware nur auf ausdrücklichen Auftrag flashen.
EEPROM-Resets und Flash-Löschungen ebenfalls nur auf ausdrücklichen Auftrag
durchführen. Eine Belegung mit `EE_CLR` ist keine Erlaubnis, die Aktion auszulösen.

# Kommunikation

Auf Deutsch antworten. Nach Änderungen kurz erklären, was angepasst wurde,
wie es geprüft wurde und ob noch ein Online-Build oder Hardwaretest aussteht.
