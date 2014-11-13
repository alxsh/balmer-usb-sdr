#include "waterfall.h"
#include "ili/UTFT.h"

#define WATERFALL_WIDTH 240

static int w_ymin = 160;
static int w_ymax = 320;
static int w_ycur = -1;

static uint16_t w_line[WATERFALL_WIDTH];

void WaterfallDraw()
{
	if(w_ycur<0)
		w_ycur = w_ymin;

    int x = 0;
    int dy = 1;
    int dx = WATERFALL_WIDTH;
    static uint16_t idx=0;
    for(int i=0; i<dx; i++)
    {
        w_line[i] = idx++;
    }

    UTFT_drawBitmap(x, w_ycur, dx, dy, w_line, 1);

    w_ycur++;
    if(w_ycur>=w_ymax)
    	w_ycur = w_ymin;

    for(int i=0; i<dx; i++)
    {
        w_line[i] = VGA_WHITE;
    }

    UTFT_drawBitmap(x, w_ycur, dx, dy, w_line, 1);
}