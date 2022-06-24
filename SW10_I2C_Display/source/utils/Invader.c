/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Invader.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "leds.h"
#include "sensor.h"
#include "i2cbus.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"

#include "McuFontDisplay.h"
#include "McuGFont.h"
#include "McuFontCour08Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv18Bold.h"
#include "McuFontHelv12Normal.h"

/* -------------- message queue ----------------------*/
typedef Invader_event_e event_e;
static QueueHandle_t eventQueue; /* queue handle */
#define EVENT_QUEUE_LENGTH    (5) /* number of elements in queue */
#define EVENT_QUEUE_ELEM_SIZE (sizeof(event_e)) /* size of a queue item */

void Invader_SendEvent(Invader_event_e event) {
	if (xQueueSendToBack(eventQueue, &event, pdMS_TO_TICKS(20)) != pdPASS) {
		/* failed to send event after 20 ms? */
	}
}

static Invader_event_e Invader_ReceiveEvent(TickType_t ticks) {
	Invader_event_e event;

	if (xQueueReceive(eventQueue, &event, ticks) != pdPASS) {
		/* failed to receive event after timeout? */
		event = Invader_Event_None;
	}
	return event;
}

static void doGraphic(void) {
	McuGDisplaySSD1306_Clear(); /* clear display buffer */
	//McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1,McuGDisplaySSD1306_GetHeight() - 1, 1,McuGDisplaySSD1306_COLOR_WHITE);
	//McuGDisplaySSD1306_DrawCircle(20 /* x */, 30 /* y */, 5 /* radius */,McuGDisplaySSD1306_COLOR_WHITE);
	//McuGDisplaySSD1306_DrawCircle(40 /* x */, 10 /* y */, 15 /* radius */,McuGDisplaySSD1306_COLOR_WHITE);
	//McuGDisplaySSD1306_DrawCircle(60 /* x */, 20 /* y */, 10 /* radius */,McuGDisplaySSD1306_COLOR_WHITE);
	//McuGDisplaySSD1306_DrawLine(0, McuGDisplaySSD1306_GetHeight() - 1,McuGDisplaySSD1306_GetWidth() - 1, 0,McuGDisplaySSD1306_COLOR_WHITE);

	McuFontDisplay_PixelDim x0, y0, x1, y1;
	x0 = 0;
	y0 = 0;
	x1 = 127;
	y1 = 0;
	McuGDisplaySSD1306_DrawLine(x0, y0, x1, y1, McuGDisplaySSD1306_COLOR_WHITE);
	x0 = 127;
	y0 = 0;
	x1 = 127;
	y1 = 63;
	McuGDisplaySSD1306_DrawLine(x0, y0, x1, y1, McuGDisplaySSD1306_COLOR_WHITE);
	x0 = 127;
	y0 = 63;
	x1 = 0;
	y1 = 63;
	McuGDisplaySSD1306_DrawLine(x0, y0, x1, y1, McuGDisplaySSD1306_COLOR_WHITE);
	x0 = 0;
	y0 = 63;
	x1 = 127;
	y1 = 0;
	McuGDisplaySSD1306_DrawLine(x0, y0, x1, y1, McuGDisplaySSD1306_COLOR_WHITE);

	I2CBus_LockBus();
	McuGDisplaySSD1306_UpdateFull(); /* update display */
	I2CBus_ReleaseBus();
}

void Sensor_ShowTemperature(float value) {
	McuFontDisplay_PixelDim x, y, w, h;
	uint8_t buf[24];

	McuGDisplaySSD1306_Clear();
	McuUtility_NumFloatToStr(buf, sizeof(buf), value, 2);
	McuUtility_chcat(buf, sizeof(buf), 'C');
	w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);
	h = McuFontDisplay_GetStringHeight(buf, McuFontHelv18Bold_GetFont(), NULL);
	x = (McuGDisplaySSD1306_GetWidth() - w) / 2;
	y = (McuGDisplaySSD1306_GetHeight() - h) / 2;
	McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y,
			McuFontHelv18Bold_GetFont());

	McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1,
			McuGDisplaySSD1306_GetHeight() - 1, 1,
			McuGDisplaySSD1306_COLOR_WHITE);
	McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth() - 5,
			McuGDisplaySSD1306_GetHeight() - 5, 1,
			McuGDisplaySSD1306_COLOR_WHITE);

	I2CBus_LockBus();
	McuGDisplaySSD1306_UpdateFull();
	I2CBus_ReleaseBus();
}

static void doSensor(void) {
	Sensor_ShowTemperature(Sensor_GetTemperature());
}

static void WaitForKeyPress(void) {
	Invader_event_e event;

	for (;;) {
		event = Invader_ReceiveEvent(portMAX_DELAY);
		switch (event) {
		case Invader_Button_Left_Pressed:
		case Invader_Button_LeftRepeat_Pressed:
		case Invader_Button_Right_Pressed:
		case Invader_Button_RightRepeat_Pressed:
		case Invader_Button_Up_Pressed:
		case Invader_Button_UpRepeat_Pressed:
		case Invader_Button_Down_Pressed:
		case Invader_Button_DownRepeat_Pressed:
		case Invader_Button_Center_Pressed:
		case Invader_Button_CenterRepeat_Pressed:
			return; /* stop waiting */

		default: /* continue waiting */
			break;
		} /* switch */
	}
}

static void Show2Liner(const unsigned char *text0, const unsigned char *text1) {
	PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
	McuFontDisplay_PixelDim x, y;
	McuFontDisplay_PixelDim charHeight, totalHeight;

	McuGDisplaySSD1306_Clear();
	McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

	x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char*) text0, font, NULL)/ 2;
	y = McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2; /* 2 lines */
	McuFontDisplay_WriteString((unsigned char*) text0,McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

	x = McuGDisplaySSD1306_GetWidth() / 2- McuFontDisplay_GetStringWidth((unsigned char*) text1, font, NULL)
					/ 2;
	y += McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2;
	McuFontDisplay_WriteString((unsigned char*) text1,McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

	McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1,McuGDisplaySSD1306_GetHeight() - 1, 1,McuGDisplaySSD1306_COLOR_WHITE);
	McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth() - 1 - 4,McuGDisplaySSD1306_GetHeight() - 1 - 4, 1,McuGDisplaySSD1306_COLOR_WHITE);
	McuGDisplaySSD1306_UpdateFull();
}

static void GameIntro(void) {
	Show2Liner((const unsigned char*) "Space",(const unsigned char*) "Invader");
	vTaskDelay(pdMS_TO_TICKS(3000));
	Show2Liner((const unsigned char*) "Press button",(const unsigned char*) "to start");
	WaitForKeyPress();
}

static void gameTask(void *pv) {
	Invader_event_e event;

	I2CBus_LockBus();
	McuSSD1306_Init();
	I2CBus_ReleaseBus();
	McuGDisplaySSD1306_Init();

	doGraphic();
	doSensor();
	GameIntro();

	for (;;) {
		event = Invader_ReceiveEvent(20);
		if (event != Invader_Event_None) {
			switch (event) {
			case Invader_Button_Left_Pressed:
				LEDS_On(LEDS_RED);
				break;
			case Invader_Button_LeftRepeat_Pressed:
				break;
			case Invader_Button_Left_Released:
				LEDS_Off(LEDS_RED);
				break;

			case Invader_Button_Right_Pressed:
				LEDS_On(LEDS_GREEN);
				break;
			case Invader_Button_RightRepeat_Pressed:
				break;
			case Invader_Button_Right_Released:
				LEDS_Off(LEDS_GREEN);
				break;

			case Invader_Button_Up_Pressed:
				LEDS_On(LEDS_ORANGE);
				break;
			case Invader_Button_UpRepeat_Pressed:
				break;
			case Invader_Button_Up_Released:
				LEDS_Off(LEDS_ORANGE);
				break;

			case Invader_Button_Down_Pressed:
				LEDS_On(LEDS_TINY_BLUE);
				break;
			case Invader_Button_DownRepeat_Pressed:
				break;
			case Invader_Button_Down_Released:
				LEDS_Off(LEDS_TINY_BLUE);
				break;

			case Invader_Button_Center_Pressed:
				LEDS_On(LEDS_RED);
				LEDS_On(LEDS_GREEN);
				break;
			case Invader_Button_CenterRepeat_Pressed:
				break;
			case Invader_Button_Center_Released:
				LEDS_Off(LEDS_RED);
				LEDS_Off(LEDS_GREEN);
				break;
			default:
				break;
			}
		} else {
			vTaskDelay(pdMS_TO_TICKS(2));
		}
	}
}

void Invader_Init(void) {
	BaseType_t res;

	res = xTaskCreate(gameTask, "game", 600 / sizeof(StackType_t), NULL,
			tskIDLE_PRIORITY + 1, NULL);
	if (res != pdPASS) {
		for (;;) {
		} /* error! */
	}

	eventQueue = xQueueCreate(EVENT_QUEUE_LENGTH, EVENT_QUEUE_ELEM_SIZE);
	if (eventQueue == NULL) {
		for (;;) {
		} /* out of memory? */
	}
	vQueueAddToRegistry(eventQueue, "eventQueue");

}
