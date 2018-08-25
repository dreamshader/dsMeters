/* 
 ********************************************************************
 * ESP8266 several graphical meters
 *
 *   Copyright (C) 2018 Dreamshader (aka Dirk Schanz)
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *********************************************************************
 *
 * These are several graphical meters for the ESP8266
 *
 * This library needs the Adafruit GFX library!
 *  
 *--------------------------------------------------------------------
 *
 * History:
 *
 *********************************************************************
*/


#ifndef _DS_METERS_H_
#define _DS_METERS_H_

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
#include <SPI.h>
#include <Adafruit_GFX.h>
#ifdef ESP8266
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
 

#define DSMETER_COLOR_WHITE   0xFFFF
#define DSMETER_COLOR_BLACK   0x0000
#define DSMETER_COLOR_YELLOW  0xFFE0
#define DSMETER_COLOR_BLUE    0x001F
#define DSMETER_COLOR_RED     0xF800
#define DSMETER_COLOR_GREEN   0x07E0
#define DSMETER_COLOR_CYAN    0x07FF
#define DSMETER_COLOR_MAGENTA 0xF81F

#define DSBATTSTATUS_STYLE_CANDYBAR        0

#define DSBATTSTATUS_MIN_FONT_SIZE         1
#define DSBATTSTATUS_MIN_FONT_SIZE         3
#define DSBATTSTATUS_DEFAULT_FONT_SIZE     1
#define DSBATTSTATUS_DEFAULT_RED_LIMIT    30
#define DSBATTSTATUS_DEFAULT_YELLOW_LIMIT 60
#define DSBATTSTATUS_DEFAULT_STYLE        DSBATTSTATUS_STYLE_CANDYBAR
#define DSBATTSTATUS_DEFAULT_SCALE_FACTOR  1
#define DSBATTSTATUS_DEFAULT_TEXT_POS     textAbove

#define DSBATTSTATUS_TERMINAL_WIDTH    4
#define DSBATTSTATUS_TERMINAL_HEIGHT   9
#define DSBATTSTATUS_WIDTH            37
#define DSBATTSTATUS_HEIGHT           15
#define DSBATTSTATUS_BORDER_WIDTH      2
#define DSBATTSTATUS_FONT_SIZE         DSBATTSTATUS_DEFAULT_FONT_SIZE
#define DSBATTSTATUS_RED_LIMIT         DSBATTSTATUS_DEFAULT_RED_LIMIT
#define DSBATTSTATUS_YELLOW_LIMIT      DSBATTSTATUS_DEFAULT_YELLOW_LIMIT
#define DSBATTSTATUS_STYLE             DSBATTSTATUS_DEFAULT_STYLE
#define DSBATTSTATUS_SCALE_FACTOR      DSBATTSTATUS_DEFAULT_SCALE_FACTOR
#define DSBATTSTATUS_TEXT_POS          DSBATTSTATUS_DEFAULT_TEXT_POS
#define DSBATTSTATUS_RED_LIMIT         DSBATTSTATUS_DEFAULT_RED_LIMIT
#define DSBATTSTATUS_YELLOW_LIMIT      DSBATTSTATUS_DEFAULT_YELLOW_LIMIT


typedef enum _statusTextPos { textWithin,
                              textAbove,
                              textBelow,
                              textLeft,
                              textRight,
                              textNone
                            };

class dsBattStatus {

 public:
    dsBattStatus(void);
//    bool init( int16_t xCenter, int16_t yCenter, uint16_t bgColor, 
//               uint8_t fontSize, int style, int scale, 
//               _statusTextPos textPos );

bool init( Adafruit_GFX *gfx, int16_t xCenter, int16_t yCenter, 
        uint16_t bgColor,
        uint8_t fontSize = DSBATTSTATUS_FONT_SIZE, 
        int style = DSBATTSTATUS_STYLE, 
        int scale = DSBATTSTATUS_SCALE_FACTOR, 
        _statusTextPos textPos  = DSBATTSTATUS_TEXT_POS );

    void update( int percentLoad );

private:
    Adafruit_GFX  *_gfx;
    int16_t        _xCenter;
    int16_t        _yCenter;
    int16_t        _bgColor;
    int16_t        _terminalWidth;
    int16_t        _terminalHeight;
    int16_t        _width;
    int16_t        _height;
    int16_t        _borderWidth;
    uint8_t        _fontSize;
    int            _redLimit;
    int            _yellowLimit;
    int            _style;
    int            _scale;
    _statusTextPos _textPos;
    char           _label[5];

};


#ifdef __cplusplus
}
#endif


#endif // _DS_METERS_H_
