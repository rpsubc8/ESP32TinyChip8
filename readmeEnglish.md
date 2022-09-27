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
 <li>Reduced version (DAC 1 bit) Wemos D1 R32 joystick board standard ATARI DB9</li>
 <li>CVBS support (PAL,NTSC) on WEMOS D1 R32 (pin 26) and TTGO VGA32 v1.x (GPIO 26 CLK mouse)</li>
</ul>

<br><br>
<h1>Precompiled version</h1>
In the precompile folder there is a version already compiled to be saved with the flash download tool 3.9.2. It is a 320x200 resolution version with the demo games in FLASH for the TTGO VGA32 v1.x and the Wemos D1 R32.<br><br>
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
  <li>Wemos D1 R32 VGA (DAC 1 bit) ATARI DB9 joystick board</li>
  <li>Visual Studio 1.66.1 PLATFORMIO 2.5.0 Espressif32 v3.5.0</li>
  <li>Arduino IDE 1.8.11 Espressif System 1.0.6</li>
  <li>Arduino bitluni 0.3.3 reduced library (included in project)</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/ttgovga32v12.jpg'></center>

 
<br><br>
<h1>PlatformIO</h1>
PLATFORMIO 2.5.0 must be installed from the Visual Studio extensions. Espressif32 v3.5.0 is also required. 
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIOinstall.gif'></center>
Then the working directory <b>TinyChip8ttgovga32</b> will be selected.
We must modify the file <b>platformio.ini</b> the option <b>upload_port</b> to select the COM port where we have our TTGO VGA32 board.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIO.gif'></center>
Then we will proceed to compile and upload to the board. No partitions are used, so we must upload all the compiled binary.
Everything is prepared so we don't have to install the bitluni libraries.


<br><br>
<h1>Arduino IDE</h1>
The whole project is compatible with the structure of Arduino 1.8.11.
We only have to open the <b>chip8.ino</b> of the <b>chip8</b> directory.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewArduinoIDEpreferences.gif'></center>
We must install the spressif (v1.0.6) extensions in the additional card url manager <b>https://dl.espressif.com/dl/package_esp32_index.json</b>
For the normal mode, the project is already prepared, so that no bitluni library is needed.
We can do it from the library manager.
We must deactivate the PSRAM option, and in case of exceeding 1 MB of binary, select 4 MB of partition when uploading. Although the code does not use PSRAM, if the option is active and our ESP32 does not have it, an exception will be generated and it will be restarted in loop mode.


<br><br>
<h1>Usability</h1>
Loading is allowed:
 <ul>
  <li>ROMS</li>
 </ul>
 There is a basic OSD of low resources, that is to say, very simple, that is visualized by pressing the key <b>F1</b>.
 <center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSD.gif'></center>  
  If we use the <b>Wemos D1 R32</b> board, activating this option in the compilation, the OSD will be displayed according to the milliseconds chosen in the <b>gbConfig.h</b> when pressing 2 configurable buttons, which by default will be Up and A, according to the <b>gb_use_gamepad_osd_menu_button0</b> and <b>gb_use_gamepad_osd_menu_button1</b>.<br>  
 You can choose the <b>rom</b> by moving with the cursors <b>up</b> and <b>down</b>.<br>
 We can also move faster with the <b>left</b> and <b>right</b>.<br>
 The files must be converted to .h in hexadecimal. You can use the online tool:<br>
 <a href='http://tomeko.net/online_tools/file_to_hex.php?lang=en'>http://tomeko.net/online_tools/file_to_hex.php?lang=en</a>


<br><br>
<h1>Keyboard Remapping</h1>
The TTGO VGA32 board allows both the use of a virtual keyboard and the possibility of remapping (gamepad remap) the keyboard cursors to the 4x4 keyboard:
<ul>
 <li>Up, down, left, right</li>
 <li>0 and .</li>
</ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSDkeyboardvirtual.gif'></center>
For the case of the WEMOS D1 R32 board, the same is allowed, but the remapping is not of the keyboard, but of the gamepad connected to the DB9, of the possible 6 buttons.
<ul>
 <li>Up, down, left, right</li>
 <li>A y B</li>
</ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSDremap.gif'></center>
The remapping allows to associate any (only 6) of the keys of the 4x4 keyboard of the Chip8 to one of the keys of the motion keyboard, as well as the <b>0</b> and <b>.</b>, for the case of the TTGO VGA32 board, while for the WEMOS D1 R32, it would be of the 6 possible buttons of the gamepad.

 
<br><br>
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
 <li><b>gb_ms_gamepad_osd_menu:</b> Milliseconds to hold down the <b>gb_use_gamepad_osd_menu_button0</b> and <b>gb_use_gamepad_osd_menu_button1</b> buttons to display the OSD from a Wemos D1 R32 board, when replacing the PS/2 keyboard support with an ATARI standard gamepad.</li>  
 <li><b>use_lib_board_wemos:</b> If this line is uncommented, the Wemos D1 R32 board will be used, replacing the PS/2 keyboard support with the 5-button ATARI DB9 gamepad, or 6-button CPC AMSTRAD. A 1-bit DAC, which generates black and white, will also be used.</li>
 <li><b>gb_use_gamepad_osd_menu_button0:</b> One of the buttons that together with the <b>gb_use_gamepad_osd_menu_button1</b> pressed during the time <b>use_lib_board_wemos</b> allows to display the OSD menu. The allowed options are ATARI_DB9_UP_ID, ATARI_DB9_DOWN_ID, ATARI_DB9_LEFT_ID, ATARI_DB9_RIGHT_ID, ATARI_DB9_A_ID, ATARI_DB9_B_ID.</li>
 <li><b>gb_use_gamepad_osd_menu_button1:</b> Together with the <b>gb_use_gamepad_osd_menu_button0</b> it allows to display the OSD menu.</li> 
</ul>

<br><br>
<h1>Test applications</h1>
Multiple test roms have been left, both games, demos and applications.

<br><br>
<h1>DIY circuit</h1>
If we don't want to use a TTGO VGA32 v1.x board, we can build it following fabgl's schematic:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/fabglcircuit.gif'></center>


<br><br>
<h1>DIY Wemos D1 R32</h1>
A minimalist version has been made with a simple 1-bit VGA passive DAC, as well as a 5-button ATARI DB9 or 6-button AMSTRAD CPC controller.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/PlacaWemosD1R32mod.gif'></center>
The <b>use_lib_board_wemos</b> must be enabled in the <b>gbConfig.h</b> to be able to use this board with the unique support of the ATARI DB9 gamepad, without the need of the PS/2 keyboard.<br>
The <b>hardware.h</b> file contains the entire GPIO (pinout).
<ul>
 <li>25 - Sound</li>
 <li>26 - Up gamepad</li>
 <li>16 - Down gamepad</li>
 <li>27 - Left gamepad</li>
 <li>14 - Right gamepad</li>
 <li> 4 - Button A</li>
 <li> 0 - Button B</li>
 <li> 5 - VGA color</li>
 <li>23 - VGA HSYNC</li>
 <li>17 - VGA VSYNC</li>
</ul>
The resistor value (metal film) for the VGA DAC, as well as the logarithmic potentiometer for the audio, is variable, and different values may be needed, depending on the VGA monitor, as well as the headphone line. If you do not connect the headphone output to a preamplifier, it is a good idea to use a passive low pass filter with resistors and capacitors, although given the quality of the CHIP 8, it is not necessary.<br>
The ATARI DB9 standard uses the internal <b>Pullup</b> resistor, hence GPIO 31 to 39 cannot be used.<br>
On very old VGA monitors, a 75 Ohm resistor may have to be placed in parallel to match impedances.<br>
In exceptional cases, it is recommended to put a very low protection resistor on the VGA HSYNC and VGA VSYNC lines to protect the pin. It is possible that for external reasons (error), the VGA monitor introduces voltage.<br>
The VGA connector is female, while the DB9 joystick connector is male.

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
