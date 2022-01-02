#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H
 
 //Corrige teclados que no se inicializan(solucion dcrespo3D)
 //#define FIX_PERIBOARD_NOT_INITING

 //Usa la libreria bitluni modificada en C tiny fast
 #define use_lib_tinybitluni_fast

 //Video colors (8 colores es DAC 3 bits)
 #define use_lib_vga8colors

 //Video mode
 //#define use_lib_200x150
 #define use_lib_320x200

 //Logs
 //#define use_lib_log_serial
 
 


 //Read keyborad poll x millis
 #define gb_ms_keyboard 20
 //Read sound poll x millis
 #define gb_ms_sound 1
 //Skip x frames
 #define gb_frame_crt_skip 0
 //Delay millis iteration emulate
 #define gb_delay_emulate_ms 0



 #ifdef use_lib_200x150
  #define gb_add_offset_x 0
  #define gb_add_offset_y 0
  #define gb_topeX 200
  #define gb_topeY 150
  #define gb_topeX_div4 50
 #else
  #define gb_add_offset_x 60 
  #define gb_add_offset_y 40
  #define gb_topeX 320
  #define gb_topeY 200
  #define gb_topeX_div4 80  
 #endif

#endif
