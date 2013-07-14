#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Mega 2560 or Mega ADK
#define __AVR_ATmega2560__
#define ARDUINO 105
#define __AVR__
#define F_CPU 16000000L
#define __cplusplus
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__
#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define prog_void
#define PGM_VOID_P int
#define NOINLINE __attribute__((noinline))

typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

void abort();
void blinkLight(long del, int light);
boolean wait(long t);
void Read();
void lightsOn(int from, int to, int red, int green, int blue);
void lightsOn(int from, int to, uint16_t color);
void lightOn(int LED, int red, int green, int blue);
void lightOn(int LED, uint16_t color);
void lightOff(int LED);
void allLightsOff(int LEDs);
int getSensor(int sensor);
int getSensors(int from, int to);
unsigned int color(byte r, byte g, byte b);
unsigned int Colors(int s);
//
//
void FourWins();
void LightTest_1();
void ReactionF();
void ReactionT();
void Screensaver();
void TicTacToe();

#include "D:\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "D:\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\libraries\TimerOne\TimerOne.h"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\libraries\SensorNew\SensorNew.h"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\libraries\LPD6803_original\LPD6803.h"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\Games.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\FourWins.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\Programs.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\ReactionF.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\ReactionT.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\Screensaver.ino"
#include "C:\Users\Matthias\Documents\Programmieren\Git\reaktionswand\Games\TicTacToe.ino"
#endif
