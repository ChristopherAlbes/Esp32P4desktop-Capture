# Esp32P4desktop-Capture

ESP32-P4 JPEG Network Display Receiver
Dieses Projekt ermöglicht es einem ESP32-P4 Nano, JPEG-Bilder über eine WiFi-Verbindung zu empfangen und diese mit hoher Geschwindigkeit auf einem ILI9486 Display darzustellen. Durch die Implementierung eines Double Buffering Systems (2x 256 KB) wird eine flüssige Anzeige mit FPS-Anzeige erreicht.

🚀 Features
Hardware: Optimiert für ESP32-P4 (360 MHz CPU Frequenz).

Double Buffering: Verwendet zwei 256 KB Puffer (insgesamt 512 KB), um Daten zu empfangen, während das vorherige Bild noch verarbeitet wird (Ping-Pong-Prinzip).

Netzwerk: Startet einen TCP-Server auf Port 8888.

JPEG Decoding: Nutzt die TJpg_Decoder Bibliothek für schnelles Hardware-nahes Rendering.

Live-Statistik: Echtzeit-Anzeige der Frames per Second (FPS) direkt auf dem Display.

🛠 Hardware-Konfiguration
Display: ILI9486 (8-Bit Parallel Bus).

Bus-Anbindung: Arduino_ESP32PAR8 (Pins 26, 32, 27 etc.).

WiFi: Verbindet sich mit dem konfigurierten lokalen Netzwerk.

📁 Protokoll-Details
Der Server erwartet Datenpakete in folgendem Format:

Header: SNAP (4 Bytes)

Größe: Bildgröße in Bytes (4 Bytes, Little Endian)

Payload: Die JPEG-Rohdaten

Antwort: Der ESP32 sendet nach erfolgreichem Empfang ein OK zurück, um das nächste Bild anzufordern.

📋 Installation
Stelle sicher, dass die folgenden Bibliotheken in der Arduino IDE installiert sind:

WiFi.h

Arduino_GFX_Library

TJpg_Decoder

Passe die ssid und das password im Code an.

Wähle das richtige Board (ESP32-P4) und lade den Code hoch.

⚙️ Technische Details (Code-Auszug)
C++
#define BUF_SIZE 262144 // 256 KB pro Puffer
uint8_t* buffer1;
uint8_t* buffer2;
uint8_t* activeBuffer; // Zeigt immer auf den aktuell zu beschreibenden Puffer
Durch das Umschalten von activeBuffer zwischen buffer1 und buffer2 wird verhindert, dass der Netzwerk-Stack den Zeichenvorgang blockiert.

Was du noch beachten solltest:
Sicherheit: Dein WLAN-Passwort steht aktuell im Klartext im Code. Wenn du das Repository öffentlich machst, solltest du diese Daten entfernen oder eine credentials.h nutzen, die in der .gitignore steht.

Display-Pins: Überprüfe, ob die Pin-Belegung (26, 32, 27...) exakt deinem Shield/Verkabelung entspricht.


Info zum Anklemmen des ESP32P4 Nano 

Display Funktion,ESP32-P4 Pin (Code),Hardware GPIO,Beschreibung
DC / RS,26,GPIO 26,Data/Command Selection
WR,32,GPIO 32,Write Clock
RD,27,GPIO 27,Read (Lese-Signal)
CS,33,GPIO 33,Chip Select (Aktivierung)
RESET,9,GPIO 9,Reset (Vorschlag: Nicht Pin 3!)
---,---,---,---
D0,1,GPIO 1,Datenleitung Bit 0
D1,2,GPIO 2,Datenleitung Bit 1
D2,3,GPIO 3,Datenleitung Bit 2
D3,4,GPIO 4,Datenleitung Bit 3
D4,5,GPIO 5,Datenleitung Bit 4
D5,6,GPIO 6,Datenleitung Bit 5
D6,7,GPIO 7,Datenleitung Bit 6
D7,8,GPIO 8,Datenleitung Bit 7



