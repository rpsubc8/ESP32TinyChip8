# Tiny ESP32 Chip8
Port del emulador Chip8 (Spittie) a la placa TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) con ESP32.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/chip8previewgif.gif'></center>
<br>
He realizado varias modificaciones:
<ul>
 <li>Funcionando en ESP32 de 520 KB de RAM (TTGO VGA32)</li>  
 <li>Uso de un sólo core</li>
 <li>OSD de bajos recursos</li>
 <li>Creado proyecto compatible con Arduino IDE y Platform IO</li> 
 <li>Carga de ROMs en Flash progmem</li>    
 <li>Soporte para modo 8 y 64 colores (versión reducida de Ricardo Massaro)</li>  
 <li>Modo de video 200x150 y 320x200</li>
 <li>Ajuste de pantalla X</li>
 <li>Beeper audio (500 Hz)</li>
 <li>Versión precompilada modo de video 320x200</li>
 <li>Versión reducida (DAC 1 bit) placa Wemos D1 R32 joystick norma ATARI DB9</li>
</ul>

<br><br>
<h1>Versión precompilada</h1>
En la carpeta precompile se encuentra una versión ya compilada para poder ser grabada con el flash download tool 3.9.2. Se trata de una versión con resolución 320x200 con los juegos de demostración en FLASH para la TTGO VGA32 v1.x y la Wemos D1 R32.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyChip8/tree/main/precompile'>https://github.com/rpsubc8/ESP32TinyChip8/tree/main/precompile</a>
<br><br>
Debemos de elegir el tipo ESP32:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/flash00.gif'></center>
Posteriormente, seleccionaremos los archivos tal y como la captura adjunta, con los mismos valores de offset:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/flash01.gif'></center>
Y le daremos a start. Si todo ha sido correcto, sólo tendremos que reiniciar el ESP32.

<br><br>
<h1>Requerimientos</h1>
Se requiere:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4)</li>
  <li>Placa Wemos D1 R32 VGA (DAC 1 bit) joystick ATARI DB9</li>
  <li>Visual Studio 1.66.1 PLATFORMIO 2.5.0 Espressif32 v3.5.0</li>
  <li>Arduino IDE 1.8.11 Espressif System 1.0.6</li>
  <li>Librería reducida Arduino bitluni 0.3.3 (incluida en proyecto)</li>  
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/ttgovga32v12.jpg'></center>




<br><br>
<h1>PlatformIO</h1>
Se debe instalar el PLATFORMIO 2.5.0 desde las extensiones del Visual Studio. Se requiere también Espressif32 v3.5.0. 
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIOinstall.gif'></center>
Luego se seleccionará el directorio de trabajo <b>TinyChip8ttgovga32</b>.
Debemos modificar el fichero <b>platformio.ini</b> la opción <b>upload_port</b> para seleccionar el puerto COM donde tenemos nuestra placa TTGO VGA32.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIO.gif'></center>
Luego procederemos a compilar y subir a la placa. No se usa particiones, así que debemos subir todo el binario compilado.
Está todo preparado para no tener que instalar las librerias de bitluni.


<br><br>
<h1>Arduino IDE</h1>
Todo el proyecto es compatible con la estructura de Arduino 1.8.11.
Tan sólo tenemos que abrir el <b>chip8.ino</b> del directorio <b>chip8</b>.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewArduinoIDEpreferences.gif'></center>
Debemos instalar las extensiones de spressif (v1.0.6) en el gestor de urls adicionales de tarjetas <b>https://dl.espressif.com/dl/package_esp32_index.json</b>
Para el modo normal, ya está preparado el proyecto, de forma que no se necesita ninguna librería de bitluni.
Lo podemos hacer desde el administrador de bibliotecas.
Debemos desactivar la opción de PSRAM, y en caso de superar 1 MB de binario, seleccionar 4 MB de partición a la hora de subir. Aunque el código no use PSRAM, si la opción está activa y nuestro ESP32 no dispone de ella, se generará una excepción y reinicio del mismo en modo bucle.


<br><br>
<h1>Usabilidad</h1>
Se permite cargar:
 <ul>
  <li>ROMS</li>
 </ul>
 Se dispone de un OSD básico de bajos recursos, es decir, muy simple, que se visualiza pulsando la tecla <b>F1</b>.
 <center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSD.gif'></center>
 Si usamos la placa <b>Wemos D1 R32</b>, activando dicha opción en la compilación, el OSD se mostrará según los milisegundos elegidos en el <b>gbConfig.h</b> al apretar 2 botones configurables, que por defecto serán <b>Arriba</b> y <b>A</b>, según el <b>gb_use_gamepad_osd_menu_button0</b> y <b>gb_use_gamepad_osd_menu_button1</b>.
 Se puede elegir la <b>rom</b> moviéndonos con los cursores <b>arriba</b> y <b>abajo</b>. También podemos movernos más rápido con la <b>izquierda</b> y <b>derecha</b>.
 Los ficheros deben ser convertidos a .h en hexadecimal. Puede usarse la herramienta online:<br>
 <a href='http://tomeko.net/online_tools/file_to_hex.php?lang=en'>http://tomeko.net/online_tools/file_to_hex.php?lang=en</a>



<br><br>
<h1>Remapear Teclado</h1>
En la placa TTGO VGA32 se permite tanto el uso de un teclado virtual (keyboard virtual), así como la posibilidad de remapear (gamepad remap) los cursores del teclado por el teclado de 4x4:
<ul>
 <li>Arriba, abajo, izquierda, derecha</li>
 <li>0 y .</li>
</ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSDkeyboardvirtual.gif'></center>
Para el caso de la placa WEMOS D1 R32, se permite lo mismo, pero el remapeo no es del teclado, sino del gamepad conectado al DB9, de los posibles 6 botones.
<ul>
 <li>Arriba, abajo, izquierda, derecha</li>
 <li>A y B</li>
</ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSDremap.gif'></center>
El remapeo permite asociar cualquiera (sólo 6) de las teclas del teclado 4x4 del Chip8 a una de las del teclado de movimiento, así como el <b>0</b> y el <b>.</b>, para el caso de la placa TTGO VGA32, mientras que para la WEMOS D1 R32, sería de los 6 posibles botones del gamepad.




<br><br>
<h1>Opciones</h1>
El archivo <b>gbConfig.h</b> se seleccionan las opciones:
<ul>  
 <li><b>use_lib_200x150:</b> Modo 200x150</li>  
 <li><b>use_lib_320x200:</b> Modo 320x200</li>
 <li><b>use_lib_vga8colors:</b> Modo 8 colores (3 bits RGB) o 64 colores (6 bits RRGGBB)
 <li><b>use_lib_log_serial:</b> Se envian logs por puerto serie usb</li>
 <li><b>FIX_PERIBOARD_NOT_INITING:</b> Solución de David Crespo Tascón para teclados que no se inicializan.</li>
 <li><b>gb_ms_keyboard:</b> Se debe especificar el número de milisegundos de polling para el teclado.</li>  
 <li><b>gb_delay_emulate_ms:</b> Milisegundos de espera por cada frame completado.</li>
 <li><b>gb_ms_gamepad_osd_menu:</b> Milisegundos que hay que tener pulsado los botones <b>gb_use_gamepad_osd_menu_button0</b> y <b>gb_use_gamepad_osd_menu_button1</b> para que se muestre el OSD desde una placa Wemos D1 R32, al sustituir el soporte de teclado PS/2 por un gamepad de norma ATARI.</li>
 <li><b>use_lib_board_wemos:</b> Si se descomenta esta linea, se usará la placa Wemos D1 R32, sustituyendo el soporte de teclado PS/2 por el gamepad ATARI DB9 de 5 botones, o CPC AMSTRAD de 6. También se usará un DAC de 1 bit, que genera blanco y negro.</li>
 <li><b>gb_use_gamepad_osd_menu_button0</b> Uno de los botones que junto con el <b>gb_use_gamepad_osd_menu_button1</b> presionado durante el tiempo <b>use_lib_board_wemos</b> permite mostrar el menú OSD. Las opciones permitidas son ATARI_DB9_UP_ID, ATARI_DB9_DOWN_IDm ATARI_DB9_LEFT_IDm ATARI_DB9_RIGHT_ID, ATARI_DB9_A_ID, ATARI_DB9_B_ID.</li>
 <li><b>gb_use_gamepad_osd_menu_button1</b> Juntándolo con el <b>gb_use_gamepad_osd_menu_button0</b> permite mostrar el menú OSD.</li>
</ul>


<br><br>
<h1>Aplicaciones Test</h1>
Se han dejado múltiples roms de pruebas, tanto juegos, como demos y aplicaciones.


<br><br>
<h1>DIY circuito</h1>
Si no queremos usar una placa TTGO VGA32 v1.x, podemos construirla siguiendo el esquema de <b>fabgl</b>:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/fabglcircuit.gif'></center>


<br><br>
<h1>DIY Wemos D1 R32</h1>
Se ha realizado una versión minimalista con un DAC pasivo simple de 1 bit VGA, así como un mando ATARI DB9 con 5 botones, o AMSTRAD CPC de 6.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/PlacaWemosD1R32mod.gif'></center>
Se debe activar en el <b>gbConfig.h</b> el <b>use_lib_board_wemos</b> para poder usar dicha placa con el soporte único del gamepad ATARI DB9, sin necesidad del teclado PS/2.<br>
En el archivo <b>hardware.h</b> se encuentra todo el GPIO (pinout).
<ul>
 <li>25 - Sonido</li>
 <li>26 - Arriba gamepad</li>
 <li>16 - Abajo gamepad</li>
 <li>27 - Izquierda gamepad</li>
 <li>14 - Derecha gamepad</li>
 <li> 4 - Boton A</li>
 <li> 0 - Botón B</li>
 <li> 5 - VGA color</li>
 <li>23 - VGA HSYNC</li>
 <li>17 - VGA VSYNC</li>
</ul>
El valor de la resistencia (metal film) para el DAC VGA, así como el potenciómetro logarítmico para el audio, es variable, y puede que se necesiten diferentes valores, en función del monitor VGA, así como de la línea de auriculares. Si no conectamos la salida de auriculares a un preamplificador, es buena idea usar un filtro pasivo paso bajo con resistencias y condensadores, aunque dado la calidad del CHIP 8, no es necesario.<br>
La norma ATARI DB9, usa la resistencia interna <b>Pullup</b>, de ahi que los GPIO 31 al 39 no se puedan usar.<br>
En monitores VGA muy antigüos, es posible que se deba poner una resistencia de 75 Ohmios en paralelo para adaptar impedancias.<br>
En casos excepcionales, se recomienda poner en las lineas de VGA HSYNC y VGA VSYNC una resistencia de protección de valor muy bajo, para proteger el pin. Es posible que por motivos externos (error), el monitor VGA introduzca voltaje.<br>



<br><br>
<h1>Tool rom2h</h1>
He creado una herramienta muy básica, para convertir los archivos <b>.rom</b>, en modo lista para ser procesados por el emulador. Tan sólo tenemos que dejar los archivos en la carpeta <b>input/roms</b> y ejecutar el archivo <b>rom2h.exe</b>, de forma que se generará una salida en el directorio <b>output/dataFlash</b>. Para pruebas, se han dejado varios archivos en cada directorio, que se recomienda borrar en caso de realizar una nueva lista personalizada.También se recomienda borrar los archivos del directorio <b>ESP32TinyChip8\chip8\dataFlash\</b> para tener un proyecto limpio.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyChip8/tree/main/tools/rom2h'>Tool rom2h</a>
<br><br>
<pre>
 input/
  roms/
   15PUZZLE
   BRIX
</pre>
Se recomienda limpiar el proyecto y volver a compilar.<br>
Esta herramienta es muy simple, y no controla los errores, por lo que se recomienda dejarle los archivos con nombres muy simples y lo más sencillo posible.<br>
El proyecto en PLATFORM.IO está preparado para 4 MB de Flash.
<pre>board_build.partitions = huge_app.csv</pre>
En el Arduino IDE, debemos elegir la opción <b>Partition Scheme (Huge APP)</b>.
