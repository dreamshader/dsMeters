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
 * This library needs the Adafruit GFX library!
 *
 *********************************************************************

 * at this time the following meters are realized:
 *
 * dsBattStatus: this can be used as a status display for
 *               e.g. accu batteries
 *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * history:
 *  
 *********************************************************************
*/




#include <dsMeters.h>


dsBattStatus::dsBattStatus(void)
{
    _xCenter        = 0;
    _yCenter        = 0;
    _bgColor        = 0;
    _terminalWidth  = DSBATTSTATUS_TERMINAL_WIDTH;
    _terminalHeight = DSBATTSTATUS_TERMINAL_HEIGHT;
    _width          = DSBATTSTATUS_WIDTH;
    _height         = DSBATTSTATUS_HEIGHT;
    _borderWidth    = DSBATTSTATUS_BORDER_WIDTH;
    _fontSize       = DSBATTSTATUS_FONT_SIZE;
    _redLimit       = DSBATTSTATUS_RED_LIMIT;
    _yellowLimit    = DSBATTSTATUS_YELLOW_LIMIT;
    _style          = DSBATTSTATUS_STYLE;
    _scale          = DSBATTSTATUS_SCALE_FACTOR;
    _textPos        = DSBATTSTATUS_TEXT_POS;
}

// bool dsBattStatus::init( int16_t xCenter, int16_t yCenter, uint16_t bgColor,
//         uint8_t fontSize = DSBATTSTATUS_FONT_SIZE, 
//         int style = DSBATTSTATUS_STYLE, 
//         int scale = DSBATTSTATUS_SCALE_FACTOR, 
//         _statusTextPos textPos  = DSBATTSTATUS_TEXT_POS )

bool dsBattStatus::init( Adafruit_GFX *gfx, int16_t xCenter, 
        int16_t yCenter, uint16_t bgColor, uint8_t fontSize, 
        int style, int scale, _statusTextPos textPos )
{

    int xPos, yPos;
    int width, height;
    _gfx      = gfx;
    _xCenter  = xCenter;
    _yCenter  = yCenter;
    _bgColor  = bgColor;
    _fontSize = fontSize;
    _style    = style;
    _scale    = scale;
    _textPos  = textPos;

// tft.drawFastHLine(0, 50, tft.width()-50, ILI9341_GREEN);
// tft.drawFastVLine(50, 0, tft.height()-50, ILI9341_GREEN);


    // left upper corner ...
    xPos = _xCenter - (_width/2);
    yPos = _yCenter - (_height/2);

    _gfx->fillRect( xPos - _terminalWidth,
                  yPos + ((_height - _terminalHeight) / 2),
                  _terminalWidth, _terminalHeight, DSMETER_COLOR_BLACK );

    _gfx->fillRect( xPos, yPos, _width, _height, DSMETER_COLOR_BLACK );

    update(0);

    return(true);
}


void dsBattStatus::update( int percentLoad )
{
    int16_t  xPos,   yPos;
    int16_t  xBound, yBound; 
    uint16_t wBound, hBound;
    uint16_t color, pixels;
    float    percentage;
    int      entry2Use;


    if( percentLoad > 100 )
    {
        percentLoad = 100;
    }
    else
    {
        if( percentLoad < 0 )
        {
            percentLoad = 0;
        }
    }

    // left upper corner ...
    xPos = _xCenter - (_width/2);
    yPos = _xCenter - (_height/2);


    _gfx->setTextSize( _fontSize );
    _gfx->setTextColor( ~_bgColor );

    sprintf(_label, "%d%%", percentLoad );

    _gfx->getTextBounds( _label, 0, 0, 
                       &xBound, &yBound, &wBound, &hBound );
 
    wBound = 4 * 8;
                       
 
    _gfx->fillRect(  _xCenter - (wBound/2) - 1,
                  yPos - (hBound + 2), 
                  wBound + 2, hBound, _bgColor );
                  
    wBound = strlen(_label) * 8;

// Serial.print("wBound adjusted: ");
// Serial.println(wBound);

    _gfx->setCursor( _xCenter - (wBound/2),
                   yPos - (hBound + 2) );

    _gfx->print( _label );

    _gfx->fillRect( xPos + _borderWidth,
                  yPos + _borderWidth,
                  _width - (2 * _borderWidth),
                  _height - (2 * _borderWidth), 
                  DSMETER_COLOR_WHITE);

    if( percentLoad > 0 )
    {

typedef struct _rgb_gradient_ {
    uint16_t startR;
    uint16_t startG;
    uint16_t startB;
    uint16_t endR;
    uint16_t endG;
    uint16_t endB;
};

struct _rgb_gradient_ chargeColor [] {
    { 253,  11, 22, 253, 238, 11 },
    { 253, 238, 11,  37, 253, 11 },
    { 253,  11, 22, 37, 253, 11 }    // combination of 0 and 1
};


//    entry2Use = 0;
//
//    if( percentLoad >= 50 )
//    {
//        entry2Use = 1;
//    }
 
// looks ok, too:
entry2Use = 2;

    float factor = (float) percentLoad / 100;

    int16_t diffR = chargeColor[entry2Use].endR - chargeColor[entry2Use].startR;
    int16_t diffG = chargeColor[entry2Use].endG - chargeColor[entry2Use].startG;
    int16_t diffB = chargeColor[entry2Use].endB - chargeColor[entry2Use].startB;

    uint16_t nextR = chargeColor[entry2Use].startR + ( diffR * factor );
    uint16_t nextG = chargeColor[entry2Use].startG + ( diffG * factor );
    uint16_t nextB = chargeColor[entry2Use].startB + ( diffB * factor );

    color  = (nextR & 0xF8) << 8;  // 5 bits
    color |= (nextG & 0xFC) << 3;  // 6 bits
    color |= (nextB & 0xF8) >> 3;  // 5 bits

// Serial.print("nextR/nextG/nextB = ");
// Serial.print(nextR & 0xF8);
// Serial.print(" / ");
// Serial.print(nextG & 0xFC);
// Serial.print(" / ");
// Serial.println(nextB & 0xF8);
// Serial.print("color = ");
// Serial.println(color, HEX);

        percentage = percentLoad/100.0;

// Serial.print("percentage: ");
// Serial.println(percentage);
        
        pixels = (percentage * (float) ( _width - (2 * _borderWidth)));

// Serial.print("pixels: ");
// Serial.println(pixels);
// Serial.print("xPos = ");
// Serial.print( xPos );
// Serial.print(" X-Pos = ");
// Serial.println( xPos + (_width - (2 * _borderWidth)) - pixels );


        _gfx->fillRect( xPos + _width - _borderWidth - pixels,
                       yPos + _borderWidth,
                       pixels,
                       _height - (2 * _borderWidth), 
                       color);
    }
}




