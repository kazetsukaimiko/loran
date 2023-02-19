# Programming Nuvoton MCUs
The Loran board is equipped with a pair of Nuvoton $NUVOTON_MCU_PART MCUs. These have been programmed with the firmware in this repo.

## WARNING!
Flashing the MCUs can cause them to be unreachable by the ESP32, in which case the MCU-related functions on the board will no longer work.
The MCUs must be flashed with the same firmware, but their pinouts are different. It is assumed to be the responsibility of the ESP32 to handle these differences.

## Hardware Requirements
You will need a Nuvoton Nu-Link-Pro in order to program the MCUs. Normal serial adapters will not work.


## Dependencies

For programming the Nuvos, you'll need to install SDCC (Small Device C Compiler), and a modified nuvoprog (Linux, provided), or the Nu link programming software for Windows.

### SDCC - Small Device C Compiler

#### Sourceforge Link
https://sdcc.sourceforge.net/

#### Installation: Ubuntu
```bash
sudo apt-get install sdcc
```

### Installation: Arch Linux
```bash
sudo pacman -Syyu sdcc
```
