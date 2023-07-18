# SDK für TM4C Tiva

Das Tiva-SDK ermöglicht das plattformunabhängige Erstellen von Firmware für den TI TM4C123 Tiva ARM Cortex M4F Microcontroller. Enthalten sind ein CMake-Basierter Buildprozess, Projekt-Templates und Beispiele, die Tiva Driverlib, sowie eine Konfiguration für die Entwicklung und das Debugging in Visual Studio Code.

## Klonen des Repositories

__Wichtig:__ Das Repository enthält die TI Driverlib als Submodule (=Link auf ein Separates Repository). Um alles zu klonen, muss das Argument `--recurse-submodules` mitgegeben werden:

```
git clone --recurse-submodules https://gitlab.oth-regensburg.de/EI/LV/mc/tiva-sdk-mc-reia.git
```
Nur dann wird auch das TivaWare-Repo mitgeklont!

Hat man das vergessen, kann das Submodul auch nachträglich mit 
```
git submodule init
git submodule update
```
geklont werden.

## Voraussetzungen

Um mit dem SDK wie in der Vorlesung arbeiten zu können, müssen die folgenden Tools vorab installiert werden.

### Visual Studio Code
Visual Studio Code kann von hier heruntergeladen und installiert werden: https://code.visualstudio.com/

In VSCode werden die folgenden Extensions benötigt:
* Cortex Debug (marus25.cortex-debug)
* ARM (dan-c-underwood.arm)
* C/C++ (ms-vscode.cpptools)
* CMake Tools (ms-vscode.cmake-tools)

Diese können über das Seitenpanel im Abschnitt "Erweiterungen" einfach installiert werden.

### Build-Tools

Die folgenden Build-Programme von von https://github.com/xpack-dev-tools werden benötigt:

* GCC-Compiler für ARM (arm-none-eabi-gcc): https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/
* CMake: https://github.com/xpack-dev-tools/cmake-xpack/releases/
* GNU Make (Windows Build Tools): https://github.com/xpack-dev-tools/windows-build-tools-xpack/releases/
* OpenOCD: https://github.com/xpack-dev-tools/openocd-xpack/releases/

__Bitte beachten__: Je nach OS (Windows, Mac, Linux) die richtige Version auswählen (Win32-64, darwin, Linux). Ggf. muss "Show all Assets" angeklickt werden, um die richtige Version zu finden.

Zur Installation alle Tools in einem Ordner (möglichst keine Leer- und Sonderzeichen im Pfad) entpacken (z.B. C:\Tools\...). Die Pfade zu den bin-Verzeichnissen der Tools müssen in den Systempfad (PATH-Umgebungsvariable) eingetragen werden.

### Stellaris ICDI-Treiber
Der USB-Treiber von Texas Instruments wird unter Windows benötigt, um den Debugger ansprechen zu können. 

Bitte von hier: https://www.ti.com/tool/STELLARIS_ICDI_DRIVERS herunterladen. Alternativ liegt der Treiber auch auf dem ELO-Laufwerk.

Zur Installation entpacken und im Gerätemanager bei angeschlossenem Board den Treiber für die beiden ICDI-Devices aktualisieren und das entpackte Verzeichnis auswählen.

In den Laboren S-128 und S-133 sind die Tools installiert und das SDK kann direkt verwendet werden.

## Projekte öffnen und konfigurieren
Alle Projekte und Vorlagen liegen im Ordner `projects`. Das zugehörige Verzeichnis (z.B. `projects/playground`) muss in VS Code als _Ordner_ geöffnet werden (Datei -> Ordner öffnen).

VSCode fragt beim erstmaligen Öffnen, ob CMake das Projekt konfigurieren soll. Bitte bestätigen. Dann muss ein CMake-Kit ausgewählt werden. In der Liste __Toolchain File for ARM GCC__ auswählen. Dann sollte ohne Fehler ein Ordner namens `build` im Projektverzeichnis auftauchen.

## Build
Hat CMake das Projekt erfolgreich konfiguriert, kann mit Klick auf den Button __BUILD__ in der Fußleiste der Build gestartet werden. 

## Flashen und Debuggen
Im Seitenpanel von VSCode im Abschnitt "Run and Debug" oben auf das kleine, grüne Play-Symbol klicken. Dann wird das Binary auf den Chip geflasht und der Debugger gestartet.

## Neues Projekt erstellen
Um ein neues Projekt zu erstellen, kann ein vorhandenes (oder eines der beiden Templates) kopiert und umbenannt werden. Den evtl. vorhandenen Unterordner `build` bitte löschen.

# Troubleshooting

## Die CMake-Konfiguration schlägt fehl
Bitte überprüfen, ob die Programme cmake, make und arm-none-eabi-gcc installiert sind und in PATH stehen. Dazu kann man ein Terminal (CMD) öffnen, und eingeben:

```
make --version
```
```
cmake --version
```
```
arm-none-eabi-gcc --version
```

Sollte einer der drei Aufrufe mit einer Fehlermeldung fehlschlagen, ist das entsprechende Tool nicht korrekt installiert und in PATH eingetragen.

Wenn das passt, stellen Sie bitte sicher, dass in ihrem Projekt in der Datei `.vscode/settings.json` die folgende Zeile enthalten ist:

``` JSON
"cmake.generator": "Unix Makefiles"
```



