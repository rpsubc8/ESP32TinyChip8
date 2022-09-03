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
En la carpeta precompile se encuentra una versión ya compilada para poder ser grabada con el flash download tool 3.9.2. Se trata de una versión con resolución 320x200 con los juegos de demostración en FLASH.<br><br>
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
<br>
 
 
<br><br>
<h1>Placa Wemos D1 R32</h1>
Se ha realizado una versión minimalista con un DAC pasivo simple de 1 bit VGA, así como un mando ATARI DB9 con 5 botones, o AMSTRAD CPC de 6.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/PlacaWemosD1R32mod.gif'></center>

<br>

<h1>PlatformIO</h1>
Se debe instalar el PLATFORMIO 2.5.0 desde las extensiones del Visual Studio. Se requiere también Espressif32 v3.5.0. 
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIOinstall.gif'></center>
Luego se seleccionará el directorio de trabajo <b>TinyChip8ttgovga32</b>.
Debemos modificar el fichero <b>platformio.ini</b> la opción <b>upload_port</b> para seleccionar el puerto COM donde tenemos nuestra placa TTGO VGA32.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewPlatformIO.gif'></center>
Luego procederemos a compilar y subir a la placa. No se usa particiones, así que debemos subir todo el binario compilado.
Está todo preparado para no tener que instalar las librerias de bitluni.


<br>
<h1>Arduino IDE</h1>
Todo el proyecto es compatible con la estructura de Arduino 1.8.11.
Tan sólo tenemos que abrir el <b>chip8.ino</b> del directorio <b>chip8</b>.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewArduinoIDEpreferences.gif'></center>
Debemos instalar las extensiones de spressif (v1.0.6) en el gestor de urls adicionales de tarjetas <b>https://dl.espressif.com/dl/package_esp32_index.json</b>
Para el modo normal, ya está preparado el proyecto, de forma que no se necesita ninguna librería de bitluni.
Lo podemos hacer desde el administrador de bibliotecas.
Debemos desactivar la opción de PSRAM, y en caso de superar 1 MB de binario, seleccionar 4 MB de partición a la hora de subir. Aunque el código no use PSRAM, si la opción está activa y nuestro ESP32 no dispone de ella, se generará una excepción y reinicio del mismo en modo bucle.


<br>
<h1>Usabilidad</h1>
Se permite cargar:
 <ul>
  <li>ROMS</li>
 </ul>
 Se dispone de un OSD básico de bajos recursos, es decir, muy simple, que se visualiza pulsando la tecla <b>F1</b>.
 <center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/previewOSD.gif'></center>
 Se puede elegir la <b>rom</b> moviéndonos con los cursores <b>arriba</b> y <b>abajo</b>. También podemos movernos más rápido con la <b>izquierda</b> y <b>derecha</b>.
 Los ficheros deben ser convertidos a .h en hexadecimal. Puede usarse la herramienta online:<br>
 <a href='http://tomeko.net/online_tools/file_to_hex.php?lang=en'>http://tomeko.net/online_tools/file_to_hex.php?lang=en</a>
 
 
<br>
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
</ul>


<br>
<h1>Aplicaciones Test</h1>
Se han dejado múltiples roms de pruebas, tanto juegos, como demos y aplicaciones.


<br><br>
<h1>DIY circuito</h1>
Si no queremos usar una placa TTGO VGA32 v1.x, podemos construirla siguiendo el esquema de <b>fabgl</b>:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyChip8/main/preview/fabglcircuit.gif'></center>


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
