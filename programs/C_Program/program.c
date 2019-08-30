typedef unsigned char uint8_t; typedef signed char int8_t;
typedef unsigned int uint16_t; typedef signed int int16_t;
typedef unsigned long uint32_t; typedef signed long int32_t;
typedef unsigned long long uint64_t; typedef signed long long int64_t;

#include "screen.h"
#include "font.h"

void screen_string(int x, int y, char *str){
  int spacing_x = 9, spacing_y = 13;
  int letter=0, line = 0;
  while(*str){
    if(((line==0) ? x : 0) + spacing_x*letter + 8 > 240){ line++; letter=0;}
    //screen_letter(((line==0) ? x : 0) + 10*letter,y + 15*line,*str);
    screen_bitmap(((line==0) ? x : 0) + spacing_x*letter,y + spacing_y*line,((line==0) ? x : 0) + spacing_x*letter+7,y + spacing_y*line+12,font_8x13[*str-' ']);
    letter++;
    str++;
  }
}

void screen_string_2(int x, int y, char *str){
  int spacing_x = 9, spacing_y = 9;
  int letter=0, line = 0;
  while(*str){
    if(((line==0) ? x : 0) + spacing_x*letter + 8 > 240){ line++; letter=0;}
    //screen_letter(((line==0) ? x : 0) + 10*letter,y + 15*line,*str);
    screen_bitmap_far(((line==0) ? x : 0) + spacing_x*letter,y + spacing_y*line,((line==0) ? x : 0) + spacing_x*letter+7,y + spacing_y*line+7,font_8x8[*str-' '],0);
    letter++;
    str++;
  }
}

uint16_t main(){
  screen_init();
  ///////screen_fill_black();

  /*screen_string(0,0,"Hello World!");
  screen_string(0,20,"an even more complicated string will continue in the next line");
  screen_string(100,100,"even if it starts in the middle of one line");

  screen_string_2(0,140,"Hello World!");
  screen_string_2(0,160,"an even more complicated string will continue in the next line");
  screen_string_2(100,260,"even if it starts in the middle of one line");*/
  //char *s = "Hello world! this is a very long string to test multiple line write to screen, in order to see the size difference between screen_string() and screen_string_2(), and how much space they each take to print this line, and the size difference and readabilty of each one of this functions";
  ///////////char *s = "Hello world!";
  ///////////screen_string(0,0,s);
  ///////////screen_string_2(0,200,s);
  //return(1);

  while(1){
    screen_rect(0,0,120,160,RED);
    screen_rect(121,0,240,160,GREEN);
    screen_rect(0,161,120,320,BLUE);
    screen_rect(121,161,240,320,WHITE);

  }

  return(1);
}
