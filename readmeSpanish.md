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
 <li>Soporte CVBS (PAL,NTSC) en WEMOS D1 R32 (GPIO 26) y TTGO VGA32 v1.x (GPIO 26 CLK mouse). Prestar atención a que la salida de video de la placa TTGO VGA32 trabaja con 5v, mientras que en Wemos D1 R32 es de 3v. Con la reducción del DAC, en la Wemos se limita a 1 voltios, pero la TTGO, no, salvo que se elija en el <b>gbConfig.h</b></li>
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
 Si usamos la placa <b>Wemos D1 R32</b>, activando dicha opción en la compilación, el OSD se mostrará según los milisegundos elegidos en el <b>gbConfig.h</b> al apretar 2 botones configurables, que por defecto serán <b>Arriba</b> y <b>A</b>, según el <b>gb_use_gamepad_osd_menu_button0</b> y <b>gb_use_gamepad_osd_menu_button1</b>.<br>
 Se puede elegir la <b>rom</b> moviéndonos con los cursores <b>arriba</b> y <b>abajo</b>. También podemos movernos más rápido con la <b>izquierda</b> y <b>derecha</b>.<br>
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
 <li><b>gb_use_gamepad_osd_menu_button0:</b> Uno de los botones que junto con el <b>gb_use_gamepad_osd_menu_button1</b> presionado durante el tiempo <b>use_lib_board_wemos</b> permite mostrar el menú OSD. Las opciones permitidas son ATARI_DB9_UP_ID, ATARI_DB9_DOWN_ID, ATARI_DB9_LEFT_ID, ATARI_DB9_RIGHT_ID, ATARI_DB9_A_ID, ATARI_DB9_B_ID.</li>
 <li><b>gb_use_gamepad_osd_menu_button1:</b> Juntándolo con el <b>gb_use_gamepad_osd_menu_button0</b> permite mostrar el menú OSD.</li>
 <li><b>use_lib_cvbs_bitluni:</b> Activa la salida CVBS en blanco y negro en la placa TTGO VGA32 v1.x (GPIO 26). En el caso de usar la WEMOS, dado que el GPIO26 se usa para el gamepad (botón arriba), se debe sustituir el cable que antes se encargaba de dicho botón al GPIO 12. La placa TTGO VGA32 usa un DAC con salida 5v por el mosfet, mientras que la WEMOS es 3.2v. Asegurarse de elegir la opción use_lib_cvbs_ttgo_vga32.</li>
 <li><b>use_lib_cvbs_pal:</b> Por defecto en el modo CVBS se usa salida NTSC. Si se descomenta, se activará la salida PAL.</li>
 <li><b>use_lib_cvbs_ttgo_vga32:</b> En la placa TTGO VGA32 la salida del GPIO 26 utiliza un mosfet con 5v, por lo que el DAC a medio valor supero el pico de 1v. Si se activa esta opción, necesaria en la placa TTGO VGA32, permitirá salida de 1v.</li>
</ul>


<br><br>
<h1>Aplicaciones Test</h1>
Se han dejado múltiples roms de pruebas, tanto juegos, como demos y aplicaciones.


<br><br>
<h1>DIY circuito</h1>
Si no queremos usar una placa TTGO VGA32 v1.x, podemos construirla siguiendo el esquema de <b>fabgl</b>:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/fabglcircuit.gif'></center>
Para el caso de querer salida de video cvbs, en lugar de VGA, debemos de sacar un cable directo del pin 26 del conector PS/2 del ratón, activando la opción <b>use_lib_cvbs_pal</b>, así como <b>use_lib_cvbs_ttgo_vga32</b> del <b>gbConfig.h</b>. Si no activamos dicha opción, la salida será de más de 1 voltio, teniendo que ser reducida con un reductor de voltaje (potenciómetro).
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/ps2.gif'></center>
El conector de PS/2 es visto desde el propio jack de la placa, es decir, jack hembra. El pin en PS/2 es el CLK, es decir, el 5.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/ttgops2cvbs.gif'></center>
En esta imagen se puede ver el mosfet SOT23 interno de la placa TTGO VGA32, de manera, que la salida en CLK (pin 5) es 5 voltios.

<br><br>
<h1>DIY Wemos D1 R32</h1>
Se ha realizado una versión minimalista con un DAC pasivo simple de 1 bit VGA, así como un mando ATARI DB9 con 5 botones, o AMSTRAD CPC de 6.<br>
Para el caso del soporte VGA, nos quedaría:
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

Para el caso del soporte cvbs, nos quedaría:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/PlacaWemosD1R32cvbsmod.gif'></center>
Se debe activar en el <b>gbConfig.h</b> el <b>use_lib_board_wemos</b> para poder usar dicha placa con el soporte único del gamepad ATARI DB9, sin necesidad del teclado PS/2.<br>
Debemos activar la opción cvbs con <b>use_lib_cvbs_bitluni</b> en lugar de VGA, pudiendo elegir PAL o NTSC con <b>use_lib_cvbs_pal</b>. En caso de usar la placa TTGO VGA32, prestar atención al <b>use_lib_cvbs_ttgo_vga32</b> para no superar 1v de salida de video.<br>
En el archivo <b>hardware.h</b> se encuentra todo el GPIO (pinout).
<ul>
 <li>25 - Sonido</li>
 <li>12 - Arriba gamepad</li>
 <li>16 - Abajo gamepad</li>
 <li>27 - Izquierda gamepad</li>
 <li>14 - Derecha gamepad</li>
 <li> 4 - Boton A</li>
 <li> 0 - Botón B</li>
 <li>26 - cvbs</li>
</ul>



El valor de la resistencia (metal film) para el DAC VGA, así como el potenciómetro logarítmico para el audio, es variable, y puede que se necesiten diferentes valores, en función del monitor VGA, así como de la línea de auriculares. Si no conectamos la salida de auriculares a un preamplificador, es buena idea usar un filtro pasivo paso bajo con resistencias y condensadores, aunque dado la calidad del CHIP 8, no es necesario.<br>
La norma ATARI DB9, usa la resistencia interna <b>Pullup</b>, de ahi que los GPIO 31 al 39 no se puedan usar.<br>
En monitores VGA muy antigüos, es posible que se deba poner una resistencia de 75 Ohmios en paralelo para adaptar impedancias.<br>
En casos excepcionales, se recomienda poner en las lineas de VGA HSYNC y VGA VSYNC una resistencia de protección de valor muy bajo, para proteger el pin. Es posible que por motivos externos (error), el monitor VGA introduzca voltaje.<br>
El conector VGA es femenino, mientras que el DB9 del joystick es masculino.



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
