# Tiny ESP32 Chip8
Chip8 (Spittie) emulator port to TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) board with ESP32.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/chip8previewgif.gif'></center>
<br>
I have made several modifications:
<ul>
 <li>Running on ESP32 with 520 KB of RAM (TTGO VGA32)</li>
 <li>Use of a single core</li>
 <li>Low-income OSD</li>
 <li>Created project compatible with Arduino IDE and Platform IO</li>
 <li>Loading ROMs in Flash progmem</li>
 <li>8 and 64 color mode support (reduced version by Ricardo Massaro)</li>
 <li>Video mode 200x150 and 320x200</li>
 <li>Screen adjustment X</li>
 <li>Beeper audio (500 Hz)</li>
 <li>Precompiled version (flash download 3.9.2) 320x200</li>
</ul>

<br><br>
<h1>Precompiled version</h1>
In the precompile folder there is a version already compiled to be saved with the flash download tool 3.9.2. It is a version with 320x200 resolution with the demo games in FLASH.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyChip8/tree/main/precompile'>https://github.com/rpsubc8/ESP32TinyChip8/tree/main/precompile</a>
<br><br>
We must choose the ESP32 type:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/flash00.gif'></center>
Subsequently, select the files as shown in the attached screenshot, with the same offset values:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/flash01.gif'></center>
And we will press start. If everything has been correct, we will only have to restart the ESP32.


<br><br>
<h1>Requirements</h1>
Required:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4)</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.1 Espressif32 v3.3.2</li>
  <li>Arduino IDE 1.8.11 Espressif System 1.0.6</li>
  <li>Arduino bitluni 0.3.3 reduced library (included in project)</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/ttgovga32v12.jpg'></center>
<br>
 

<h1>PlatformIO</h1>
PLATFORMIO 2.2.1 must be installed from the Visual Studio extensions. Espressif32 v3.3.2 is also required. 
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIOinstall.gif'></center>
Then the working directory <b>TinyChip8ttgovga32</b> will be selected.
We must modify the file <b>platformio.ini</b> the option <b>upload_port</b> to select the COM port where we have our TTGO VGA32 board.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIO.gif'></center>
Then we will proceed to compile and upload to the board. No partitions are used, so we must upload all the compiled binary.
Everything is prepared so we don't have to install the bitluni libraries.


<br>
<h1>Arduino IDE</h1>
The whole project is compatible with the structure of Arduino 1.8.11.
We only have to open the <b>chip8.ino</b> of the <b>chip8</b> directory.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewArduinoIDEpreferences.gif'></center>
We must install the spressif (v1.0.6) extensions in the additional card url manager <b>https://dl.espressif.com/dl/package_esp32_index.json</b>
For the normal mode, the project is already prepared, so that no bitluni library is needed.
We can do it from the library manager.
We must deactivate the PSRAM option, and in case of exceeding 1 MB of binary, select 4 MB of partition when uploading. Although the code does not use PSRAM, if the option is active and our ESP32 does not have it, an exception will be generated and it will be restarted in loop mode.


<br>
<h1>Usability</h1>
Loading is allowed:
 <ul>
  <li>ROMS</li>
 </ul>
 There is a basic OSD of low resources, that is to say, very simple, that is visualized by pressing the key <b>F1</b>.
 <center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSD.gif'></center>
 You can choose the <b>rom</b> by moving with the cursors <b>up</b> and <b>down</b>. We can also move faster with the <b>left</b> and <b>right</b>.
 The files must be converted to .h in hexadecimal. You can use the online tool:<br>
 <a href='http://tomeko.net/online_tools/file_to_hex.php?lang=en'>http://tomeko.net/online_tools/file_to_hex.php?lang=en</a>
 
 
<br>
<h1>Options</h1>
The file <b>gbConfig.h</b> options are selected:
<ul>  
 <li><b>use_lib_200x150:</b> 200x150 mode</li>  
 <li><b>use_lib_320x200:</b> 320x200 mode</li>
 <li><b>use_lib_vga8colors:</b> 8-color (3-bit RGB) or 64-color (6-bit RRGGBB) mode</li>
 <li><b>use_lib_log_serial:</b> Logs are sent by serial port usb</li>
 <li><b>FIX_PERIBOARD_NOT_INITING:</b> David Crespo Tascón's solution for keyboards that do not initialize.</li>
 <li><b>gb_ms_keyboard:</b> You must specify the number of milliseconds of polling for the keyboard.</li>  
 <li><b>gb_delay_emulate_ms:</b> Millisecond wait for each completed frame.</li>
</ul>

<br>
<h1>Test applications</h1>
Multiple test roms have been left, both games, demos and applications.

<br><br>
<h1>DIY circuito</h1>
If we don't want to use a TTGO VGA32 v1.x board, we can build it following fabgl's schematic:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/fabglcircuit.gif'></center>

<br><br>
<h1>Tool rom2h</h1>
I have created a very basic tool, to convert the files <b>.rom</b>, in ready mode to be processed by the emulator. We only have to leave the files in the folder <b>input/roms</b> and execute the file <b>rom2h.exe</b>, so that an output will be generated in the directory <b>output/dataFlash</b>. For testing purposes, several files have been left in each directory, which it is recommended to delete in case of making a new custom list. It is also recommended to delete the files in the <b>ESP32TinyChip8\chip8\dataFlash\</b> directory to have a clean project.
<a href='https://github.com/rpsubc8/ESP32TinyChip8/tree/main/tools/rom2h'>Tool rom2h</a>
<br><br>
<pre>
 input/
  roms/
   15PUZZLE
   BRIX
</pre>
It is recommended to clean the project and recompile it.<br>
This tool is very simple, and does not control errors, so it is recommended to leave you the files with very simple names and as simple as possible.<br>
The project in PLATFORM.IO is prepared for 4 MB of Flash.
<pre>board_build.partitions = huge_app.csv</pre>
In the Arduino IDE, we must choose the option <b>Partition Scheme (Huge APP)</b>.
