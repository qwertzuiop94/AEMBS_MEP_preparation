// Display Stuff

//breite x = 0 bis 127
//hoehe y = 0 bis 63


/* Init */
McuSSD1306_Init();
McuGDisplaySSD1306_Init();
I2CBus_Init();
Sensor_Init();
// im Task
I2CBus_LockBus();
McuSSD1306_Init();
I2CBus_ReleaseBus();
McuGDisplaySSD1306_Init();


// clear Dispaly
McuGDisplaySSD1306_Clear();

// draw line
McuFontDisplay_PixelDim x0, y0, x1, y1;
x0 = 0;
y0 = 0;
x1 = 80;
y1 = 0;
McuGDisplaySSD1306_DrawLine(x0, y0, x1, y1, McuGDisplaySSD1306_COLOR_WHITE);
McuGDisplaySSD1306_UpdateFull(); /* update display */

// draw circle
McuGDisplaySSD1306_DrawCircle(20 /* x */, 30 /* y */, 5 /* radius */,McuGDisplaySSD1306_COLOR_WHITE);
McuGDisplaySSD1306_UpdateFull(); /* update display */

// draw box
McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1,McuGDisplaySSD1306_GetHeight() - 1, 1 /*dicke*/ ,McuGDisplaySSD1306_COLOR_WHITE);
McuGDisplaySSD1306_UpdateFull(); /* update display */

// Text Schreiben
McuUtility_NumFloatToStr(buf, sizeof(buf), value, 2);
McuUtility_chcat(buf, sizeof(buf), 'C');
w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);

//zwei Zeilen schreiben Funktion

static void Show2Liner(const unsigned char *text0, const unsigned char *text1) {
	PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
	McuFontDisplay_PixelDim x, y;
	McuFontDisplay_PixelDim charHeight, totalHeight;

	McuGDisplaySSD1306_Clear();
	McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

	x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char*) text0, font, NULL)/ 2;
	y = McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2; /* 2 lines */
	McuFontDisplay_WriteString((unsigned char*) text0,McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

	x = McuGDisplaySSD1306_GetWidth() / 2- McuFontDisplay_GetStringWidth((unsigned char*) text1, font, NULL)/ 2;
	y += McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2;
	McuFontDisplay_WriteString((unsigned char*) text1,McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

	McuGDisplaySSD1306_UpdateFull();
}

static void GameIntro(void) {
	Show2Liner((const unsigned char*) "Space",(const unsigned char*) "Invader");
	vTaskDelay(pdMS_TO_TICKS(3000));
	Show2Liner((const unsigned char*) "Press button",(const unsigned char*) "to start");
}

// bild zeichnen
Sprite_t *spriteShip;

static void drawShip(void){
	PIMAGE ship = ship_GetImage();
	McuGDisplaySSD1306_Clear();
	SpriteImage_t *image = Sprite_NewImage(ship);
	spriteShip = Sprite_New(image, 62, 55);
	Sprite_Paint(spriteShip);
	McuGDisplaySSD1306_UpdateFull();
}

	