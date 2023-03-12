@echo off
echo Convert ANDROID PROJECT DATA (WIN32)
echo Delete dataFlash (Borrar dataFlash)
pause
echo Process gbrom.h (Procesar gbrom.h)
fart dataFlash\gbrom.h "roms/rom" "rom"
ping -n 2 127.0.0.1>nul
echo Copy gbrom.h (Copiar gbrom.h)
copy/Y dataFlash\gbrom.h
ping -n 2 127.0.0.1>nul
echo Copy roms (Copiar roms)
copy/Y dataFlash\roms\*.h
ping -n 2 127.0.0.1>nul
echo Process chip8.ino (Procesar chip8.ino)
fart chip8.ino "dataFlash/gbrom.h" "gbrom.h"
ping -n 2 127.0.0.1>nul
echo Delete dataFlash (Borrar dataFlash)
rmdir /S /Q dataFlash
pause