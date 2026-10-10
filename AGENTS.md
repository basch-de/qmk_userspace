# Projekt

Dieses Repository enthält die QMK-Userspace-Keymap für eine Preonic Drop rev3.

- Keyboard-Target: `preonic/rev3_drop`
- Keymap: `basch_de`
- Verzeichnis: `keyboards/preonic/keymaps/basch_de/`

# Arbeitsbereich

Änderungen erfolgen im Userspace-Projekt.

Wichtige Dateien:
- `keymap.c`: Tastenbelegung, Layer und eigene Logik
- `config.h`: QMK-Einstellungen
- `rules.mk`: Features und zusätzliche Quelldateien
- `qmk.json`: Build-Targets
- `.github/workflows/`: Online-Build-Konfiguration

Das veraltete lokale Verzeichnis `../qmk_firmware` darf nicht als fachliche
Referenz verwendet werden.

# Quellen und Versionen

Für QMK-APIs, Features und Konfiguration aktuelle offizielle Quellen aus dem
Internet prüfen:

- Dokumentation: https://docs.qmk.fm/
- Quellcode: https://github.com/qmk/qmk_firmware

Maßgeblich für die Kompatibilität ist der vom GitHub-Workflow verwendete
QMK-Commit beziehungsweise Branch. Bei versionsabhängigen Änderungen den
Workflow prüfen und dazu passende Dokumentation und Quellcode heranziehen.

# Nutzung und Host-Layout

Die Tastatur wird hauptsächlich unter macOS mit dem Host-Tastaturlayout
EurKEY next verwendet.

Sonderzeichen, Modifier und Makros auf diese Kombination abstimmen. Aus dem
Keymap-Namen `basch_de` kein deutsches QWERTZ-Hostlayout ableiten. Bei
layoutabhängigen Änderungen die tatsächlich verwendete EurKEY-next-Belegung
berücksichtigen; unklare Zuordnungen prüfen oder erfragen.

Langfristig ist ein Gaming-Layer für die Xbox vorgesehen. Diesen erst auf
konkreten Auftrag implementieren. Vorher gewünschte Belegung, unterstützte
Spiele und das auf der Xbox verwendete Tastaturlayout klären.

macOS-spezifische Shortcuts und Makros dürfen nicht ungeprüft in den Xbox-Layer
übernommen werden.

# Änderungen

Bestehende Benennungen, Code-Stil und die tabellarische Darstellung der
Tastenbelegung erhalten.

## Darstellung der Tastenmatrix

- Jeden Layer in `keymap.c` entsprechend den physischen Tastenpositionen
  formatieren: vier Reihen mit zwölf Tasten und eine untere Reihe mit elf
  Tasten bei `LAYOUT_preonic_1x2uC`.
- Tasten derselben physischen Spalte innerhalb eines Layers beginnen an
  derselben Zeichenposition. Die zentrale 2u-Taste der unteren Reihe beginnt
  in Spalte 6 und belegt den Platz der Spalten 6 und 7; die nächste Taste
  beginnt wieder unter Spalte 8.
- Spaltenbreiten für jeden Layer unabhängig anhand der längsten vollständigen
  Keycode-Ausdrücke bestimmen. Hinter dem Komma mindestens zwei Leerzeichen
  Abstand lassen. Spalten bei Änderungen nach Bedarf verbreitern oder verengen.
- Verschachtelte Ausdrücke wie `LT(_LOWER, KC_BSPC)` bleiben eine ungeteilte
  Zelle. Leerzeichen statt Tabs zur Ausrichtung verwenden.
- Beim Formatieren keine Keycodes, Argumente, Reihenfolge oder Funktion ändern.
- Die Belegungsdiagramme in den Kommentaren über allen Layern bei jeder
  Belegungsänderung aktualisieren. Sie müssen die tatsächlichen Keycodes und
  physischen Positionen einschließlich der zentralen 2u-Taste wiedergeben.
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

# Builds und Prüfung

Kompiliert wird ausschließlich online über GitHub Actions mit der dort
eingebundenen QMK-Version. Keine lokalen Builds ausführen.

Änderungen statisch auf Konsistenz prüfen. Ein erfolgreicher Build darf nur
behauptet werden, wenn das entsprechende GitHub-Build-Ergebnis für den
geprüften Änderungsstand vorliegt.

Ein erfolgreicher Build bestätigt die Kompilierbarkeit. Tap/Hold-Timing,
Combos und tatsächliche Zeichenausgabe müssen zusätzlich an der Tastatur
getestet werden. Ausstehende Hardwaretests im Ergebnis benennen.

Pushes und manuelle Workflow-Ausführungen nur bei entsprechendem Auftrag
durchführen.

# Hardware

Firmware nur auf ausdrücklichen Auftrag flashen.

# Kommunikation

Auf Deutsch antworten. Nach Änderungen kurz erklären, was angepasst wurde,
wie es geprüft wurde und ob noch ein Online-Build oder Hardwaretest aussteht.
