//#pragma once
#include "gbConfig.h"

#ifdef use_lib_cvbs_bitluni

class CompositeGraphics
{ 
  public:
  int xres;
  int yres;
  char **frame;
  char **backbuffer;
  char **zbuffer;
  
  CompositeGraphics(int w, int h, int initialTrinagleBufferSize = 0)
    :xres(w), 
    yres(h)
  {
  }
  
  void init()
  {
    frame = (char**)malloc(yres * sizeof(char*));
    backbuffer = (char**)malloc(yres * sizeof(char*));
    //not enough memory for z-buffer implementation
    //zbuffer = (char**)malloc(yres * sizeof(char*));
    for(int y = 0; y < yres; y++)
    {
      frame[y] = (char*)malloc(xres);
      backbuffer[y] = (char*)malloc(xres);
      //zbuffer[y] = (char*)malloc(xres);
    }
  }


  inline void begin(int clear = -1, bool clearZ = true)
  {
    if(clear > -1)
      for(int y = 0; y < yres; y++)
        for(int x = 0; x < xres; x++)
          backbuffer[y][x] = clear;
  }

  inline void end()
  {
    char **b = backbuffer;
    backbuffer = frame;
    frame = b;    
  }
 
  void fillRect(int x, int y, int w, int h, int color)
  {
    if(x < 0)
    {
      w += x;
      x = 0;
    }
    if(y < 0)
    {
      h += y;
      y = 0;
    }
    if(x + w > xres)
      w = xres - x;
    if(y + h > yres)
      h = yres - y;
    for(int j = y; j < y + h; j++)
    {
     for(int i = x; i < x + w; i++)
     {      
      backbuffer[j][i] = color;
     }
    }
  }

};

#endif

