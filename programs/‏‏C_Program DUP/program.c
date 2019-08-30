typedef unsigned char uint8_t; typedef signed char int8_t;
typedef unsigned int uint16_t; typedef signed int int16_t;
typedef unsigned long uint32_t; typedef signed long int32_t;
typedef unsigned long long uint64_t; typedef signed long long int64_t;

#include "screen.h"

void screen_string(int x, int y, char *str){
  int i=0;
  while(*str){
    screen_letter(x+10*i,y,*str);
    i++;
  }
}

uint16_t main(){
  screen_init();
  screen_fill_black();

  screen_string(0,0,"Hello World!");
  while(1);

  while(1){
    screen_rect(0,0,120,160,RED);
    screen_rect(120,0,240,160,GREEN);
    screen_rect(0,160,120,320,BLUE);
    screen_rect(120,160,240,320,WHITE);

  }

  return(1);
}
