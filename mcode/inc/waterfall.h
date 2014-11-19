
/*
	Init waterfall & entter scroll mode
*/
void WaterfallInit();
void WaterfallDraw();

uint16_t AmplitudeToColor(uint16_t amp);

#define WATERFALL_WIDTH 240
extern uint16_t w_line[WATERFALL_WIDTH];
