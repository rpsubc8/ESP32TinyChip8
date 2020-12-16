//Port CHIP8(Spittie) emulator to TTGO VGA32 by ackerman:
// Load Roms
// VGA MODE200x150, MODE320x200
// Mode 8 colors RGB 3 bits
// VGA library bitluni 0.3.3 (include)
// gbConfig options configuration compile

#include "Emulator/Keyboard/PS2Kbd.h"
#include <Arduino.h>
#include "gbConfig.h"
#include "chip8.h"
#include "MartianVGA.h"
#include "def/Font.h"
#include "def/hardware.h"
#include "driver/timer.h"
#include "soc/timer_group_struct.h"
#include "gb_globals.h"
#include "dataFlash/gbrom.h"
#include "PS2Boot/PS2KeyCode.h"

VGA3Bit vga;

//Chars
const static unsigned char chip8_fontset[80] =
{ 
 0xF0,0x90,0x90,0x90,0xF0, //0
 0x20,0x60,0x20,0x20,0x70, //1
 0xF0,0x10,0xF0,0x80,0xF0, //2
 0xF0,0x10,0xF0,0x10,0xF0, //3
 0x90,0x90,0xF0,0x10,0x10, //4
 0xF0,0x80,0xF0,0x10,0xF0, //5
 0xF0,0x80,0xF0,0x90,0xF0, //6
 0xF0,0x10,0x20,0x40,0x40, //7
 0xF0,0x90,0xF0,0x90,0xF0, //8
 0xF0,0x90,0xF0,0x10,0xF0, //9
 0xF0,0x90,0xF0,0x90,0x90, //A
 0xE0,0x90,0xE0,0x90,0xE0, //B
 0xF0,0x80,0x80,0x80,0xF0, //C
 0xE0,0x90,0x90,0x90,0xE0, //D
 0xF0,0x80,0xF0,0x80,0xF0, //E
 0xF0,0x80,0xF0,0x80,0x80  //F
};

//CPU Stuff
static unsigned char V[16]; //uint8_t V[16];
static unsigned short int I; //uint16_t I;
static unsigned short int PC; //uint16_t PC;
static unsigned short int SP; //uint16_t SP;
static unsigned short int stack[16]; //uint16_t stack[16];
static unsigned char delay_t; //uint8_t delay_t;
static unsigned char sound_t; //uint8_t sound_t;

//Key
static unsigned char key[16]; //uint8_t key[16];

//Ram
static unsigned char ram[4096]; //uint8_t ram[4096];

// GFX
static unsigned char gfx[64][32]; //uint8_t gfx[64][32];
static unsigned char draw; //uint8_t draw;

static unsigned short int opcode; //uint16_t opcode;

unsigned char quit = 0;

unsigned char gb_run_emulacion = 1; //Ejecuta la emulacion
unsigned char gb_current_ms_poll_sound = gb_ms_sound;
unsigned char gb_screen_xOffset=0;
static unsigned long gb_time_ini_espera;
static unsigned long gb_currentTime;
static unsigned long gb_sdl_time_sound_before;
static unsigned long gb_keyboardTime;
static unsigned long gb_time_ini_beep;
unsigned char gb_current_sel_rom=0;

unsigned char gb_show_osd_main_menu=0;

unsigned char gb_current_delay_emulate_ms= gb_delay_emulate_ms;
unsigned char gb_current_ms_poll_keyboard = gb_ms_keyboard;
unsigned char gb_delay_t=0;
unsigned char gb_delay_sound=0;

static unsigned char gbVolMixer=0; //Beep
static unsigned char gbCont=0;

//Funciones
void ResetEmu(void);
void Setup(void);
void CPU_init(void);
void CPU_loop(void);
void SDL_DumpVGA(void);
void Loadrom2Flash(unsigned char id);
void SDL_keys_poll(void);
void do_tinyOSD(void);
void Beep_poll(void);

#define max_gb_main_menu 5
const char * gb_main_menu[max_gb_main_menu]={
 "Load ROM",
 "Speed",
 "Screen Adjust",
 "Reset",
 "Return"
};

#define max_gb_speed_sound_menu 7
const char * gb_speed_sound_menu[max_gb_speed_sound_menu]={
 "0",
 "1",
 "2",
 "4",
 "8",
 "16",
 "32"
};

#define max_gb_speed_videoaudio_options_menu 3
const char * gb_speed_videoaudio_options_menu[max_gb_speed_videoaudio_options_menu]={
 "Audio poll",
 "Video delay",
 "Keyboard poll"
};

#define max_gb_osd_screen 1
const char * gb_osd_screen[max_gb_osd_screen]={
 "Pixels Left"
};

#define max_gb_osd_screen_values 5
const char * gb_osd_screen_values[max_gb_osd_screen_values]={
 "0",
 "2",
 "4", 
 "8", 
 "16"
};

#ifdef use_lib_200x150
 #define gb_pos_x_menu 50
 #define gb_pos_y_menu 20
#else
 #define gb_pos_x_menu 100
 #define gb_pos_y_menu 40
#endif

#define gb_osd_max_rows 10


void OSDMenuRowsDisplayScroll(const char **ptrValue,unsigned char currentId,unsigned char aMax)
{//Dibuja varias lineas
 vga.setTextColor(WHITE,BLACK);
 for (int i=0;i<gb_osd_max_rows;i++)
 {
  vga.setCursor(gb_pos_x_menu, gb_pos_y_menu+8+(i<<3));
  vga.print("                    ");
 }
 
 for (int i=0;i<gb_osd_max_rows;i++)
 {
  if (currentId >= aMax)
   break;
  if (i == 0)
   vga.setTextColor(CYAN,BLUE);
  else
   vga.setTextColor(WHITE,BLACK);
  vga.setCursor(gb_pos_x_menu, gb_pos_y_menu+8+(i<<3));
  vga.print(ptrValue[currentId]);
  currentId++;
 }     
}

//Maximo 256 elementos
unsigned char ShowTinyMenu(const char *cadTitle,const char **ptrValue,unsigned char aMax,short int aSel)
{
 unsigned char aReturn=0;
 unsigned char salir=0;
 #ifdef use_lib_200x150
  vga.fillRect(0,0,200,150,BLACK);
  vga.fillRect(0,0,200,150,BLACK);//Repeat Fix visual defect
 #else
  vga.fillRect(0,0,320,200,BLACK);
  vga.fillRect(0,0,320,200,BLACK);//Repeat Fix visual defect    
 #endif
 vTaskDelay(2);
 vga.setTextColor(WHITE,BLACK);
 vga.setCursor((gb_pos_x_menu-(48)), gb_pos_y_menu-16);
 vga.print("Port Chip8(Spittie) by Ackerman");

 vga.setTextColor(BLACK,WHITE); 
 for (int i=0;i<12;i++)
 {  
  vga.setCursor((gb_pos_x_menu+(i*6)), gb_pos_y_menu);
  vga.print(" ");
 }
  
 vga.setCursor(gb_pos_x_menu,gb_pos_y_menu);
 vga.print(cadTitle);

 aReturn = (aSel!=-1)?aSel:0;
 OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
 
 while (salir == 0)
 {    
  if (checkAndCleanKey(KEY_CURSOR_LEFT))
  {
   if (aReturn>10) aReturn-=10;
   OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
  }
  if (checkAndCleanKey(KEY_CURSOR_RIGHT))
  {
   if (aReturn<(aMax-10)) aReturn+=10;
   OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
  }     

  //case SDLK_UP:
  if (checkAndCleanKey(KEY_CURSOR_UP))
  {
   if (aReturn>0) aReturn--;
   OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
  }
  if (checkAndCleanKey(KEY_CURSOR_DOWN))
  {
   if (aReturn < (aMax-1)) aReturn++;
   OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
  }
  if (checkAndCleanKey(KEY_ENTER))
  {
   salir= 1;
  }
  //case SDLK_KP_ENTER: case SDLK_RETURN: salir= 1;break;
  if (checkAndCleanKey(KEY_ESC))
  {
   salir=1; aReturn= 255;    
  }      
 } 
 gb_show_osd_main_menu= 0;

 #ifdef use_lib_200x150
  vga.fillRect(0,0,200,150,BLACK);
  vga.fillRect(0,0,200,150,BLACK);//Repeat Fix visual defect
 #else
  vga.fillRect(0,0,320,200,BLACK);
  vga.fillRect(0,0,320,200,BLACK);//Repeat Fix visual defect    
 #endif
 vTaskDelay(2);

 return aReturn;
}

//Menu velocidad emulador
void ShowTinySpeedMenu()
{
 unsigned char aSelNum,aSelNumSpeed;
 aSelNum = ShowTinyMenu("SPEED VIDEO AUDIO",gb_speed_videoaudio_options_menu,max_gb_speed_videoaudio_options_menu,-1);
 if (aSelNum == 255)
  return;
 switch (aSelNum)
 {
  case 0: aSelNumSpeed= ShowTinyMenu("AUDIO Poll ms",gb_speed_sound_menu,max_gb_speed_sound_menu,-1);
   if (aSelNumSpeed == 255)
    return;
   gb_current_ms_poll_sound= (aSelNumSpeed<<1); //Multiplico x2
   break;
  case 1: aSelNumSpeed= ShowTinyMenu("Video DELAY ms",gb_speed_sound_menu,max_gb_speed_sound_menu,-1);
   if (aSelNumSpeed == 255)
    return;
   gb_current_delay_emulate_ms = (aSelNumSpeed<<1);
   break;
  case 2: aSelNumSpeed= ShowTinyMenu("Keyboard Poll ms",gb_speed_sound_menu,max_gb_speed_sound_menu,-1);
   if (aSelNumSpeed == 255)
    return;
   gb_current_ms_poll_keyboard= (aSelNumSpeed<<1);
   break;   
  default: break;
 }
}


//Menu ROM
void ShowTinyROMMenu()
{
 unsigned char aSelNum;   
 aSelNum = ShowTinyMenu("LOAD ROM",gb_list_rom_title,max_list_rom,gb_current_sel_rom);  
 CPU_init();
 ResetEmu();
 gb_current_sel_rom = aSelNum;
 Loadrom2Flash(aSelNum);  
 //SDLClear(screen);
}

//Ajustar pantalla
void ShowTinyScreenAdjustMenu()
{
 unsigned char aSelNum, auxCol; 
 aSelNum= ShowTinyMenu("Screen Adjust",gb_osd_screen,max_gb_osd_screen,-1);
 auxCol= ShowTinyMenu("Pixels",gb_osd_screen_values,max_gb_osd_screen_values,-1);
 auxCol = auxCol<<1; //x2
 gb_screen_xOffset = auxCol;
}

#define max_gb_reset_menu 2
const char * gb_reset_menu[max_gb_reset_menu]={
 "Soft",
 "Hard"
};

//Menu resetear
void ShowTinyResetMenu()
{
 unsigned char aSelNum;
 aSelNum= ShowTinyMenu("Reset",gb_reset_menu,max_gb_reset_menu,0);   
 CPU_init();
 ResetEmu();
 Loadrom2Flash(gb_current_sel_rom);
 if (aSelNum == 1)
  ESP.restart(); 
}

//Very small tiny osd
void do_tinyOSD() 
{
 unsigned char aSelNum;
 if (checkAndCleanKey(KEY_F1))
 {
  gb_show_osd_main_menu= 1;
  return;
 }

 if (gb_show_osd_main_menu == 1)
 {
  aSelNum = ShowTinyMenu("MAIN MENU",gb_main_menu,max_gb_main_menu,-1);
  switch (aSelNum)
  {
   case 0: ShowTinyROMMenu(); break;
   case 1: ShowTinySpeedMenu(); break;
   case 2: ShowTinyScreenAdjustMenu(); break;
   case 3: ShowTinyResetMenu(); break;
   default: break;
  }
  //SDLClear(screen); //Borramos pantalla
 }
}

//Lectura teclado
void SDL_keys_poll()
{
	key[0x02] = (keymap[PS2_KC_2] == 0)?1:0; //2
  key[0x01] = (keymap[PS2_KC_1] == 0)?1:0; //1
	key[0x03] = (keymap[PS2_KC_3] == 0)?1:0; //3
	key[0x0C] = (keymap[PS2_KC_4] == 0)?1:0; //4
  key[0x04] = (keymap[PS2_KC_Q] == 0)?1:0; //q
  key[0x05] = (keymap[PS2_KC_W] == 0)?1:0; //w
  key[0x06] = (keymap[PS2_KC_E] == 0)?1:0; //e  
  key[0x0D] = (keymap[PS2_KC_R] == 0)?1:0; //r
  key[0x07] = (keymap[PS2_KC_A] == 0)?1:0; //a
  key[0x08] = (keymap[PS2_KC_S] == 0)?1:0; //s
  key[0x09] = (keymap[PS2_KC_D] == 0)?1:0; //d
  key[0x0E] = (keymap[PS2_KC_F] == 0)?1:0; //f
  key[0x0A] = (keymap[PS2_KC_Z] == 0)?1:0; //z
  key[0x00] = (keymap[PS2_KC_X] == 0)?1:0; //x
  key[0x0B] = (keymap[PS2_KC_C] == 0)?1:0; //c
  key[0x0F] = (keymap[PS2_KC_V] == 0)?1:0; //v  

  if (keymap[KEY_CURSOR_LEFT] == 0)
   key[0x04] = 1;
  if (keymap[KEY_CURSOR_UP] == 0)
   key[0x05] = 1;
  if (keymap[KEY_CURSOR_RIGHT] == 0)
   key[0x06] = 1;
  if (keymap[KEY_CURSOR_DOWN] == 0)
   key[0x08] = 1; 
  if (keymap[KEY_BACKSPACE] == 0)
   key[0x0F] = 1;
}


//*****************************
void ResetEmu()
{
 memset(V,0,16);
 memset(stack,0,16);
 memset(key,0,16);
 memset(ram,0,4096);
 memset(gfx,0,sizeof gfx);
 memcpy(ram,chip8_fontset,80);
}

//Init
void CPU_init()
{//Initialize 
 PC = 0x200;
 opcode = 0;
 I = 0;
 SP = 0;
 draw = 0;
 delay_t = 0;
 sound_t = 0;
}

//*********************************************
void CPU_loop()
{
 opcode = ram[PC + 0];
 opcode <<= 8;
 opcode |= ram[PC + 1];

 switch(opcode & 0xF000)
 {			
  case 0x0000:
   {
    switch(opcode & 0x00FF) 
    {
     case 0x00E0: 
      {                         
       memset(gfx,0,sizeof gfx);
	     draw = 1;
	     PC += 2;
	    }
	    break;
		
	 case 0X00EE:
      {
 	   SP--;
	   PC = stack[SP];
	   PC += 2;
	  }
	  break;
					
 	 default:
      {
	   printf("Unknown opcode\n");				
 	  }
	  break;
    }
   }
   break;
			
  case 0x1000: 
   {
	PC = opcode & 0X0FFF;
   }
   break;
			
  case 0x2000:
   {
	stack[SP] = PC;
	SP++;
	PC = opcode & 0x0FFF;
   }
   break;

  case 0x3000:
   {
	if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
 	 PC += 4;
	} 
    else {
	 PC += 2;
	}
   }
   break;
			
  case 0x4000:
   {
 	if (V[(opcode & 0x0F00) >> 8] != ((opcode & 0x00FF))) {
	 PC += 4;
	}
    else {
 	 PC += 2;
	}
   }
   break;
			
  case 0x5000: 
   {
	if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
 	 PC += 4;
	}
    else {
	 PC += 2;
	}
   }
   break;
			
  case 0x6000: 
   {
	V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
	PC += 2;
   }
   break;
		
  case 0x7000: 
   {
	V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
	PC += 2;
   }
   break;
			
  case 0x8000: 
   {
	switch(opcode & 0x000F) {
 	 case 0x0000:
      {
	   V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
	   PC += 2;
	  }
	  break;
					
	 case 0x0001:
      {
	   V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
	   PC += 2;
	  }
	  break;
					
	 case 0x0002:
      {
	   V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
	   PC += 2;
	  }
	  break;
					
	 case 0x0003:
      {
	   V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
	   PC += 2;
	  }
	  break;
				
	 case 0x0004:
      {
	   if (V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])) {
		V[0xF] = 1;
	   }
       else {
		V[0xF] = 0;
	   }
	   V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
	   PC += 2;
	  }
	  break;
					
	 case 0x0005:
      {
	   if (V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8]) {
		V[0xF] = 0;
	   }
       else {
		V[0xF] = 1;
	   }
	   V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
	   PC += 2;
      }
	  break;
					
					case 0x0006: {
						V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
						V[(opcode & 0x0F00) >> 8] >>= 1;
						PC += 2;
					}
					break;
					
					case 0x0007: {
						if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
							V[0xF] = 0;	
						} else {
							V[0xF] = 1;
						}
						V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
						PC += 2;
					}
					break;
					
					case 0x000E: {
						V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
						V[(opcode & 0x0F00) >> 8] <<= 1;
						PC += 2;
					}
					break;
					
					default: {
						printf("Unknown opcode\n");
						
					}
					break;
				}
			}
			break;
			
			case 0x9000: {
				if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
					PC += 4;
				} else {
					PC += 2;
				}
			}
			break;
			
			case 0xA000: {
				I = opcode & 0x0FFF;
				PC += 2;
			}
			break;
			
			case 0xB000: {
				PC = (opcode & 0x0FFF) + V[0x0];
			}
			break;
			
			case 0xC000: {
				V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
				PC += 2;
			}
			break;
			
			case 0xD000: {
				uint8_t x = V[(opcode & 0x0F00) >> 8];
				uint8_t y = V[(opcode & 0x00F0) >> 4];
				uint8_t n = opcode & 0x000F;
				uint8_t pixel;
				
				V[0xF] = 0;			
				
				for(int i=0; i < n; i++) {
					pixel = ram[I + i];
					for(int j=0; j < 8; j++) {
						if((pixel & (0x80 >> j)) != 0) {
							if(gfx[x+j][y+i] == 1) {
								V[0xF] = 1;	
							}
						gfx[x+j][y+i] ^= 1;
						}
					}
				}
				
				draw = 1;
				PC += 2;
			}
			break;
			
			case 0xE000: {
				switch(opcode & 0x00FF) {
					case 0x009E: {
						if (key[V[(opcode & 0x0F00) >> 8]] == 1) {
							key[V[(opcode & 0x0F00) >> 8]] = 0;
							PC += 4;
						} else {
							PC += 2;
						}
					}
					break;
						
					case 0x00A1 : {
						if (key[V[(opcode & 0x0F00) >> 8]] != 1) {
							PC += 4;
						} else {
							PC += 2;
						}
					}
					break;
					
					default: {
						printf("Unknown opcode\n");
						
					}
					break;
				}
			}
			break;
			
			
			case 0xF000: {
				switch(opcode & 0x00FF) {
					case 0x0007: {
						V[(opcode & 0x0F00) >> 8] = delay_t;
						PC += 2;
					}
					break;
					
					case 0x000A: {
						int keypress = 0;
						
						for (int i=0; i < 16; ++i) {
							if (key[i] != 0) {
								key[i] = 0;
								V[(opcode & 0x0F00) >> 8] = i;
								keypress = 1;
							}
						}
						
						if (keypress == 0) {
							break;
						}
						
						PC += 2;
					}
					break;
					
					case 0x0015: {
						delay_t = V[(opcode & 0x0F00) >> 8];
						PC += 2;
					}
					break;
					
					case 0x0018: {
						sound_t = V[(opcode & 0x0F00) >> 8];
						PC += 2;
					}
					break;
					
					case 0x001E: {
						if(I + V[(opcode & 0x0F00) >> 8] > 0xFFF) {
							V[0xF] = 1;
						} else {
							V[0xF] = 0;
						}
						I += V[(opcode & 0x0F00) >> 8];
						PC += 2;
					}
					break;
					
					case 0x0029: {
						I = V[(opcode & 0x0F00) >> 8] * 0x5;
						PC += 2;
					}
					break;
					
					case 0x0033: {
						ram[I] = V[(opcode & 0x0F00) >> 8] / 100;
						ram[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
						ram[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
						PC += 2;
					}
					break;
					
					case 0x0055: {
						for (int i=0; i<=((opcode & 0x0F00) >> 8); ++i) {
							ram[I + i] = V[i];
						}
						// Original interpreter?
						I += ((opcode & 0x0F00) >> 8) + 1;
						PC += 2;
					}
					break;
					
					case 0x0065: {
						for (int i=0; i<=((opcode & 0x0F00) >> 8); ++i) {
							V[i] = ram[I + i];
						}
						// Original interpreter?
						I += ((opcode & 0x0F00) >> 8) + 1;
						PC += 2;
					}
					break;
					
					default: {
						printf("Unknown opcode\n");
						
					}
					break;
				}
			}	
			break;
			
			default: {
				printf("Unknown opcode\n");
 				
			}
			break;
		}
}

//****************************
void SDL_DumpVGA(void)
{
 unsigned char aux;
 unsigned char ofsX,ofsY;
 //SDLClear(screen);
 ofsY= gb_add_offset_y;
 for (int j=0; j<32; j++)
 {
  ofsX= gb_screen_xOffset + gb_add_offset_x;
  for (int i=0; i<64; i++)
  {
   aux= (gfx[i][j] == 1)?255:0;
   vga.dotFast((ofsX+i),(ofsY+j),aux);  //x
   vga.dotFast((ofsX+i+1),(ofsY+j),aux);//x+1
   vga.dotFast((ofsX+i),ofsY+j+1,aux);  //x, y
   vga.dotFast((ofsX+i+1),ofsY+j+1,aux);//x+1,y+1   
   ofsX+= 2;
  }
  ofsY+=2;
 }
}

//*************************************
void Loadrom2Flash(unsigned char id)
{//Solo lee 256 roms
 memcpy(&ram[0x200],gb_list_rom_data[id],gb_list_rom_size[id]);
}

//**************************
 inline void Beep_poll()
{//Genera tono aproximado 500 Hz
 if (gbVolMixer == 1)
 {
  gb_currentTime = millis();
  if ((gb_currentTime - gb_time_ini_beep) >= 1)
  {
   gb_time_ini_beep = gb_currentTime;
   gbCont++;
  }
  if ((gbCont & 0x01)==0x01)
   digitalWrite(SPEAKER_PIN, HIGH);
  else 
   digitalWrite(SPEAKER_PIN, LOW);
 }
 else
 {
  digitalWrite(SPEAKER_PIN, LOW);
 }
}

//Setup principal
void setup()
{ 
 pinMode(SPEAKER_PIN, OUTPUT);
 digitalWrite(SPEAKER_PIN, LOW);  

 #ifdef use_lib_log_serial
  Serial.begin(115200);         
  Serial.printf("HEAP BEGIN %d\n", ESP.getFreeHeap()); 
 #endif
 
 #ifdef use_lib_200x150
  vga.init(vga.MODE200x150, RED_PIN_3B, GRE_PIN_3B, BLU_PIN_3B, HSYNC_PIN, VSYNC_PIN);       
 #else
  vga.init(vga.MODE320x200, RED_PIN_3B, GRE_PIN_3B, BLU_PIN_3B, HSYNC_PIN, VSYNC_PIN);    
 #endif
 
 vga.setFont(Font6x8);
 vga.clear(BLACK);
 
 #ifdef use_lib_200x150
  vga.fillRect(0,0,200,150,BLACK);
  vga.fillRect(0,0,200,150,BLACK);//fix mode fast video
 #else
  vga.fillRect(0,0,320,200,BLACK);
  vga.fillRect(0,0,320,200,BLACK);//fix mode fast video
 #endif
 
 #ifdef use_lib_log_serial
  Serial.printf("VGA %d\n", ESP.getFreeHeap()); 
 #endif

 kb_begin();

 CPU_init();
 ResetEmu();
 Loadrom2Flash(0);
 gb_keyboardTime = gb_currentTime = gb_sdl_time_sound_before= gb_time_ini_beep = millis();
 srand(time(NULL)); //Random
 #ifdef use_lib_log_serial  
  Serial.printf("END SETUP %d\n", ESP.getFreeHeap()); 
 #endif 
}


//Loop main
void loop() 
{ 
 if (gb_run_emulacion == 1)
 {                 
  CPU_loop();
 }

 gb_currentTime = millis();
 if ((gb_currentTime-gb_keyboardTime) >= gb_current_ms_poll_keyboard)
 {  
  gb_keyboardTime = gb_currentTime;
  SDL_keys_poll();
 }

 do_tinyOSD();

 if (draw == 1)
 {
  SDL_DumpVGA();   
  draw = 0;
   
  gb_run_emulacion= 0;
  gb_time_ini_espera = millis();
 }


 if (gb_run_emulacion == 1)
 {
  if(delay_t > 0){    
   delay_t--;
   gb_run_emulacion=0;
   gb_delay_t = 16;
   gb_time_ini_espera = millis();
  }
  else
  {
   gb_delay_t = 0;
  }
  if(sound_t > 0) {    
   sound_t--;
   gb_run_emulacion=0;    
   gb_time_ini_espera = millis();
   gbVolMixer= 1;
   gb_time_ini_beep = gb_time_ini_espera;
  }
  else
  {    
   gbVolMixer= 0;   
  }   
 }  


 gb_currentTime = millis();
 if (gb_run_emulacion == 0)
 {
  if ((gb_currentTime - gb_time_ini_espera) >= (16+gb_delay_t+gb_delay_sound+gb_current_delay_emulate_ms))
  {
   gb_run_emulacion = 1;  
  }
 }
 
 Beep_poll();
}
