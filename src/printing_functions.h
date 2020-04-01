#include "Nokia_5110_lcd.h"

#define OBJECT_TEMP_COL 10
#define OBJECT_TEMP_LINE 2

void printAmbient() {
  printChar(0x7e, 0x11, 0x11, 0x11, 0x7e); // print A char
  printChar(0x7c, 0x04, 0x18, 0x04, 0x78); // print m char
  printChar(0x7f, 0x48, 0x44, 0x44, 0x38); // print b char
  //printChar(0x00, 0x44, 0x7d, 0x40, 0x00); // print i char
  //printChar(0x38, 0x54, 0x54, 0x54, 0x18); // print e char
  //printChar(0x7c, 0x08, 0x04, 0x04, 0x78); // print n char
  //printChar(0x04, 0x3f, 0x44, 0x40, 0x20); // print t char
}

void printDistance() {
  printChar(0x7f, 0x41, 0x41, 0x22, 0x1c); // print D char
  printChar(0x00, 0x44, 0x7d, 0x40, 0x00); // print i char
  printChar(0x48, 0x54, 0x54, 0x54, 0x20); // print s char
  printChar(0x04, 0x3f, 0x44, 0x40, 0x20); // print t char
  printChar(0x20, 0x54, 0x54, 0x54, 0x78); // print a char
  printChar(0x7c, 0x08, 0x04, 0x04, 0x78); // print n char
  printChar(0x38, 0x44, 0x44, 0x44, 0x20); // print c char
  printChar(0x38, 0x54, 0x54, 0x54, 0x18); // print e char
}

void printFloatNumber(float deg, bool is_deg=false) {
  deg *= 100;
  byte cpt = 0;
  while(deg >= 10000) {
      deg -= 10000;
      cpt++;
  }
  if(cpt != 0) printSimpleNumber(cpt);
  cpt = 0;
  while(deg >= 1000) {
      deg -= 1000;
      cpt++;
  }
  if(cpt != 0) printSimpleNumber(cpt);
  cpt = 0;
  while(deg >= 100) {
      deg -= 100;
      cpt++;
  }
  printSimpleNumber(cpt);
  // print cents (num on the right of decimal)
  cpt = 0;
  while(deg >= 10) {
      deg -= 10;
      cpt++;
  }
  printChar(0x00, 0x60, 0x60, 0x00, 0x00); // print . char
  printSimpleNumber(cpt);
  printSimpleNumber(deg);
  if(is_deg) {
  printChar(0x00, 0x00, 0x02, 0x05, 0x02); // print ° (deg)
  printChar(0x3e, 0x41, 0x41, 0x41, 0x22); // print C char
  }
}

void printObjectDeg(float deg) {
  deg *= 100;
  byte cpt = 0;
  while(deg >= 10000) {
      deg -= 10000;
      cpt++;
  }
  if(cpt != 0) printGrandNumber(cpt, OBJECT_TEMP_COL, OBJECT_TEMP_LINE);
  cpt = 0;
  while(deg >= 1000) {
      deg -= 1000;
      cpt++;
  }
  if(cpt != 0) printGrandNumber(cpt, (OBJECT_TEMP_COL + 11), OBJECT_TEMP_LINE);
  cpt = 0;
  while(deg >= 100) {
      deg -= 100;
      cpt++;
  }
  printGrandNumber(cpt, (OBJECT_TEMP_COL + 22), OBJECT_TEMP_LINE);
  // print cents (num on the right of decimal)
  cpt = 0;
  while(deg >= 10) {
      deg -= 10;
      cpt++;
  }
  setCursor((OBJECT_TEMP_COL + 32), OBJECT_TEMP_LINE+1);
  printChar(0x00, 0x00, 0xC0, 0xC0, 0x00); // print . char
  printGrandNumber(cpt, (OBJECT_TEMP_COL + 37), OBJECT_TEMP_LINE);
  printGrandNumber(deg, (OBJECT_TEMP_COL + 48), OBJECT_TEMP_LINE);
  setCursor((OBJECT_TEMP_COL + 57), OBJECT_TEMP_LINE);
  printChar(0x00, 0x06, 0x09, 0x09, 0x06); // print ° char (deg)
  printChar(0x3e, 0x41, 0x41, 0x41, 0x22); // print C char
}
