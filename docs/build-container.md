# QMK-Build-Container

Der gemeinsame Workflow verwendet direkt:

```yaml
container: ghcr.io/qmk/qmk_cli:latest
```

Das entspricht der Container-Auswahl im
[offiziellen QMK-Userspace-Workflow](https://github.com/qmk/.github/blob/main/.github/workflows/qmk_userspace_build.yml).
Es wird kein eigener Image-Digest festgeschrieben oder aus einem anderen Projekt
übernommen. Jede Buildvariante zieht das unter `latest` verfügbare Image.
Ein neues Image allein startet keinen Workflow-Lauf in diesem Repository.

## Python-Abhängigkeiten

Wie im offiziellen QMK-Workflow wird nach dem Firmware-Checkout
`pip install -r firmware/requirements.txt` ausgeführt. Dadurch werden die
Python-Abhängigkeiten des verwendeten QMK-Stands installiert. Die tatsächlich
verwendeten Paketversionen dokumentiert `pip freeze` im Provenance-Artefakt.

## Validierung und Buildnachweise

Die vier Varianten werden ausschließlich über GitHub Actions kompiliert:
Preonic `default` und `basch_de`, Corne `default` und `basch_de`.
Firmware- und Provenance-Artefakte werden auf Vollständigkeit geprüft.
Es werden keine Releases oder Tags veröffentlicht.
Ein erfolgreicher Build bestätigt Kompilierbarkeit; Hardwaretests
bleiben davon getrennt. Es gibt keine Flash- oder EEPROM-Reset-Schritte.

Jede Variante liefert ein Provenance-Artefakt mit Firmware-/Userspace-Revision,
Submodulen, Compiler, Python-Paketen, Buildlog und Firmware-Prüfsumme.
Das tatsächlich gezogene Container-Image ist im Actions-Log der
Container-Initialisierung nachvollziehbar.

Der Tag `latest` ist beweglich. Ebenso folgen die Firmware dem aktuellen
Mainline-`master` und die Python-Pakete dessen Anforderungen. Damit wird die
Buildumgebung automatisch aktualisiert; ein identischer Userspace-Commit allein
garantiert keinen vollständig identischen späteren Build. Alle vier Varianten
verwenden denselben einmal pro Workflow-Lauf aufgelösten Firmware-Commit.
