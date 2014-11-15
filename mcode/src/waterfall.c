#include "waterfall.h"
#include "ili/UTFT.h"


static int w_ymin = 160;
static int w_ymax = 320;
static int w_ycur = -1;

uint16_t w_line[WATERFALL_WIDTH];

void WaterfallInit()
{
    int top  = w_ymin;
    int bottom = 320-w_ymax;
    int center = w_ymax-w_ymin;
    UTFT_verticalScrollDefinition(top, center, bottom);
    //UTFT_verticalScrollDefinition(160, 160, 0);
    //UTFT_verticalScrollDefinition(0, 320, 0);

    for(int i=0; i<WATERFALL_WIDTH; i++)
    {
        w_line[i] = 0xf;
    }
}

void WaterfallDraw()
{
	if(w_ycur<0)
		w_ycur = w_ymin;


    int x = 0;
    int dy = 1;
    int dx = WATERFALL_WIDTH;
    /*
    static uint16_t idx=0;
    for(int i=0; i<dx; i++)
    {
        w_line[i] = idx++;
    }
    */

    uint16_t w_ynext = w_ycur+1;
    if(w_ynext>=w_ymax)
        w_ynext = w_ymin;

    UTFT_verticalScroll(w_ynext);
    UTFT_drawBitmap(x, w_ycur, dx, dy, w_line, 1);

    w_ycur = w_ynext;
}