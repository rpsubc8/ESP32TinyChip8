#ifndef _GB_GLOBALS_H
 #define _GB_GLOBALS_H
 #include "gbConfig.h"
 #include <stdio.h>

 extern unsigned char keymap[256];
 extern unsigned char oldKeymap[256];

 extern unsigned char gb_current_ms_poll_sound; //milisegundos muestreo
 extern unsigned char gb_current_ms_poll_keyboard; //milisegundos muestreo teclado
 extern unsigned char gb_current_frame_crt_skip; //el actual salto de frame
 extern unsigned char gb_current_delay_emulate_ms; //la espera en cada iteracion
 extern unsigned char gb_sdl_blit;
 extern unsigned char gb_screen_xOffset;

 extern unsigned char gb_show_osd_main_menu;

#endif
 
