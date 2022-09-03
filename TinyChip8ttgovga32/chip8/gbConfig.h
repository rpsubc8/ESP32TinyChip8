#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H
 
 //Use board Wemos D1 R32 Joystick ATARI DB9 VGA DAC 1 bit
 //#define use_lib_board_wemos

 #ifdef use_lib_board_wemos
  //Use gamepad ATARI DB9, not use keyboard PS/2
  #define use_lib_not_use_ps2keyboard  
 #endif

 //Corrige teclados que no se inicializan(solucion dcrespo3D)
 //#define FIX_PERIBOARD_NOT_INITING

 //Usa la libreria bitluni modificada en C tiny fast
 #define use_lib_tinybitluni_fast

 //Video colors (8 colores es DAC 3 bits) TTGO VGA32 and Wemos D1 R32
 #define use_lib_vga8colors

 #ifdef use_lib_board_wemos
  #ifndef use_lib_vga8colors
   #define use_lib_vga8colors
  #endif
 #endif

 //Video mode
 //#define use_lib_200x150
 #define use_lib_320x200

 //View logs serial
 #define use_lib_log_serial
 
 


 //Read keyborad poll x millis
 #define gb_ms_keyboard 20 
 //Two Buttons Joystick press 500 ms for view OSD MENU(use_lib_not_use_ps2keyboard)
 #define gb_ms_gamepad_osd_menu 500 
 //First button press joystick to view OSD MENU(use_lib_not_use_ps2keyboard)
 //ATARI_DB9_UP_ID ATARI_DB9_DOWN_ID ATARI_DB9_LEFT_ID ATARI_DB9_RIGHT_ID
 //ATARI_DB9_A_ID ATARI_DB9_B_ID
 #define gb_use_gamepad_osd_menu_button0 ATARI_DB9_UP_ID
 //Second button press joystick to view OSD MENU(use_lib_not_use_ps2keyboard)
 #define gb_use_gamepad_osd_menu_button1 ATARI_DB9_A_ID
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

 //Posicion Teclado virtual
 #define gb_pos_x_virtualKey 4
 #define gb_pos_y_virtualKey 4
#endif
