# Auswahl des QMK-Build-Containers

Der gemeinsame Workflow verwendet das offizielle Image `ghcr.io/qmk/qmk_cli`.
Als Ausgangspunkt dient `latest`, wie im
[offiziellen QMK-Userspace-Workflow](https://github.com/qmk/.github/blob/main/.github/workflows/qmk_userspace_build.yml).
Im eigenen Workflow wird anschließend dessen konkreter Digest eingetragen.

## Herkunft des ausgewählten Images

Am 08.11.2026 wurde `latest` direkt über die GitHub Container Registry aufgelöst.
Der Digest wurde sowohl aus dem Registry-Header `Docker-Content-Digest` gelesen
als auch unabhängig als SHA-256 des unveränderten Manifest-Bodys berechnet.
Beide Werte stimmen überein.

- Image: `ghcr.io/qmk/qmk_cli:latest`
- OCI-Image-Index:
  `sha256:b7d7fa8fb4432b569931de5ad59098cb788f440ed61a62c5126746b71aee0f4a`
- Darin referenziertes Manifest für die `linux/amd64`-Build-Runner:
  `sha256:cd9eb2923030b02135bac2c8d7d81d563c2b17776b4461ff98186848e57253de`
- Der Index enthält auch eine `linux/arm64`-Variante.

Die Auswahl beruht damit auf dem offiziellen QMK-Image. Der zuvor aus dem
Studio-Projekt übernommene Digest `sha256:2dc05fc9…4513b07` wurde ersetzt.
Die Registry- und Hashprüfung bestätigt die eindeutige Referenzierung; sie ist
kein vollständiges Audit aller Softwarebestandteile des Images.

## Validierung und Buildnachweise

Ein Container-Wechsel muss über GitHub Actions mit allen vier Varianten
validiert werden: Preonic `default` und `basch_de`, Corne `default` und `basch_de`.
Zusätzlich werden die Firmware-Artefakte und die persönliche Preonic-
Veröffentlichung geprüft. Maßgeblich ist der Actions-Lauf für den jeweiligen
Userspace-Commit, der den Image-Digest in `.github/workflows/build.yml` festlegt.

Jede Variante liefert ein Provenance-Artefakt mit Firmware-/Userspace-Revision,
Submodulen, Compiler, Python-Paketen, Buildlog und Firmware-Prüfsumme.
Die Image-Referenz ist über den darin gespeicherten Userspace-Commit eindeutig
nachvollziehbar. Ein erfolgreicher Build bestätigt Kompilierbarkeit;
Hardwaretests bleiben davon getrennt. Es werden keine lokalen Firmware-Builds
oder Geräteaktionen ausgeführt.

## Python-Abhängigkeiten

Wie im offiziellen QMK-Userspace-Workflow wird nach dem Checkout
`pip install -r firmware/requirements.txt` ausgeführt. Damit können zusätzliche
Pakete oder andere Paketversionen installiert werden, die der aktuelle QMK-Stand
benötigt. `pip freeze` dokumentiert die resultierende Umgebung.

Der Digest fixiert das Container-Image. Der Firmware-Branch `master` und diese
nachträgliche Python-Installation bleiben beweglich; der gesamte Build ist
deshalb nicht allein durch den Container-Digest vollständig reproduzierbar.

## Aktualisierung

1. Den aktuellen Stand des offiziellen QMK-Workflows und seines Images prüfen.
2. `latest` über die Registry auflösen, den Manifest-Digest gegen den Inhalt
   prüfen und die für den Runner passende Plattform bestätigen.
3. Den Digest im Workflow ersetzen und diese Herkunftsdokumentation aktualisieren.
4. Workflow statisch prüfen, den Stand committen und nach beauftragtem Push alle
   vier Varianten ausschließlich in GitHub Actions bauen.
5. Den Digest nach erfolgreicher Prüfung beibehalten; bei Fehlern die Ursache
   klären und nur einen funktionierenden Stand als geprüft ausweisen.

Der Digest wird nicht automatisch bei jedem Lauf aktualisiert. Alle vier
Varianten verwenden dasselbe festgelegte Image; die Firmware folgt weiterhin
dem einmal pro Lauf aufgelösten aktuellen offiziellen QMK-`master`.
