#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 5
#define OLED_RESET 17

extern const unsigned char epd_bitmap_josh_hutcherson_whistle[] PROGMEM;
extern const unsigned char epd_bitmap_Alfredo[] PROGMEM;
extern const unsigned char epd_bitmap_Rick[] PROGMEM;

void startDisplay();
void displayText(String text);
void showImage(const unsigned char*);

#endif