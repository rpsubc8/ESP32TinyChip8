#ifndef _HARDWARE_H
 #define _HARDWARE_H

 #include "gbConfig.h"

 #ifdef use_lib_not_use_ps2keyboard
  //Board WEMOS D1 R32 Joystick Gamepad ATARI
  #define ATARI_DB9_UP_PIN 26    //Up(1)    - 39
  #define ATARI_DB9_DOWN_PIN 16  //Down(2)  - 38
  #define ATARI_DB9_LEFT_PIN 27  //Left(3)  - 34
  #define ATARI_DB9_RIGHT_PIN 14 //Right(4) - 36
  #define ATARI_DB9_A_PIN 4      //A (6)    - 4
  #define ATARI_DB9_B_PIN 0      //B (7)    - 2
                                 //GND (8)
 #else
  //Keyboard                              
  #define KEYBOARD_DATA 32
  #define KEYBOARD_CLK 33 
 #endif                                 

 //Sound
 #define SPEAKER_PIN 25



 //3 bit pins No se usa
 //#define RED_PIN_3B 22
 //#define GRE_PIN_3B 19
 //#define BLU_PIN_3B 5

 //VGA sync pins No se usa
 //#define HSYNC_PIN 23
 //#define VSYNC_PIN 15


 //Colores Indices en CHIP8
 #define ID_COLOR_BLACK 0 //Negro
 #define ID_COLOR_WHITE 1 //Blanco
 //#define ID_COLOR_VIOLETA 1 //Violeta tambien blanco

 //Section Tiny Fast Bitluni
 // VGA output pins  
 #ifdef use_lib_board_wemos
  //WEMOS (255 value = not pin)
  #define PIN_RED_LOW    255
  #define PIN_RED_HIGH   255
  #define PIN_GREEN_LOW  255
  #define PIN_GREEN_HIGH 255
  #define PIN_BLUE_LOW   5
  #define PIN_BLUE_HIGH  255
  #define PIN_HSYNC      23
  #define PIN_VSYNC      17
  //FIN WEMOS
 #else
  // VGA output pins
  #define PIN_RED_LOW    21
  #define PIN_RED_HIGH   22
  #define PIN_GREEN_LOW  18
  #define PIN_GREEN_HIGH 19
  #define PIN_BLUE_LOW   4
  #define PIN_BLUE_HIGH  5
  #define PIN_HSYNC      23
  #define PIN_VSYNC      15
 #endif

 #define BLACK   0x08      // 0000 1000
 #define BLUE    0x0C      // 0000 1100
 #define RED     0x09      // 0000 1001
 #define MAGENTA 0x0D      // 0000 1101
 #define GREEN   0x0A      // 0000 1010
 #define CYAN    0x0E      // 0000 1110
 #define YELLOW  0x0B      // 0000 1011
 #define WHITE   0x0F      // 0000 1111
#endif
