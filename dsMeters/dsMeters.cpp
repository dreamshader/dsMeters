

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
    float percentage;

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
        color = DSMETER_COLOR_RED;
        if( percentLoad > _redLimit )
        {
            color = DSMETER_COLOR_YELLOW;
            if( percentLoad > _yellowLimit )
            {
                color = DSMETER_COLOR_GREEN;
            }
        }
        
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




