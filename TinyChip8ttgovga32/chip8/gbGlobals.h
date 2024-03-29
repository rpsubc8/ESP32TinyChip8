#ifndef _GB_GLOBALS_H
 #define _GB_GLOBALS_H
 #include "gbConfig.h"
 #include <stdio.h>

 extern volatile unsigned char keymap[256];
 extern volatile unsigned char oldKeymap[256];

 #ifdef use_lib_not_use_ps2keyboard
  extern unsigned char gb_atari_db9;
  extern unsigned char gb_atari_db9_prev;
  extern unsigned char gb_ini_osd_main_menu;
  extern unsigned int gb_ini_osd_main_menu_time;
 #endif

 extern unsigned char gb_current_ms_poll_sound; //milisegundos muestreo
 extern unsigned char gb_current_ms_poll_keyboard; //milisegundos muestreo teclado
 extern unsigned char gb_current_frame_crt_skip; //el actual salto de frame
 extern unsigned char gb_current_delay_emulate_ms; //la espera en cada iteracion
 extern unsigned char gb_sdl_blit;
 extern unsigned char gb_screen_xOffset;

 extern unsigned char gb_show_osd_main_menu;

#endif
 
