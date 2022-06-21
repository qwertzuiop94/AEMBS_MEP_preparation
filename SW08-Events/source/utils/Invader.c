/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Invader.h"
#include "McuRTOS.h"
#include "leds.h"

/* -------------- message queue ----------------------*/
typedef Invader_event_e event_e;
static QueueHandle_t eventQueue; /* queue handle */
#define EVENT_QUEUE_LENGTH    (5) /* number of elements in queue */
#define EVENT_QUEUE_ELEM_SIZE (sizeof(event_e)) /* size of a queue item */

void Invader_SendEvent(Invader_event_e event) {
  if (xQueueSendToBack(eventQueue, &event, pdMS_TO_TICKS(20))!=pdPASS) {
    /* failed to send event after 20 ms? */
  }
}

static Invader_event_e Invader_ReceiveEvent(void) {
  Invader_event_e event;

  if (xQueueReceive(eventQueue, &event, portMAX_DELAY)!=pdPASS) {
    /* failed to receive event after timeout? */
    event = Invader_Event_None;
  }
  return event;
}

static void gameTask(void *pv) {
  Invader_event_e event;

  for(;;) {
    event = Invader_ReceiveEvent();
    if (event!=Invader_Event_None) {
      switch(event) {
        case Invader_Button_Left_Pressed: LEDS_On(LEDS_RED); break;
        case Invader_Button_LeftRepeat_Pressed: break;
        case Invader_Button_Left_Released: LEDS_Off(LEDS_RED); break;

        case Invader_Button_Right_Pressed: LEDS_On(LEDS_GREEN); break;
        case Invader_Button_RightRepeat_Pressed: break;
        case Invader_Button_Right_Released: LEDS_Off(LEDS_GREEN); break;

        case Invader_Button_Up_Pressed: LEDS_On(LEDS_ORANGE); break;
        case Invader_Button_UpRepeat_Pressed: break;
        case Invader_Button_Up_Released: LEDS_Off(LEDS_ORANGE); break;

        case Invader_Button_Down_Pressed: LEDS_On(LEDS_TINY_BLUE); break;
        case Invader_Button_DownRepeat_Pressed: break;
        case Invader_Button_Down_Released: LEDS_Off(LEDS_TINY_BLUE); break;

        case Invader_Button_Center_Pressed: LEDS_On(LEDS_RED); LEDS_On(LEDS_GREEN); break;
        case Invader_Button_CenterRepeat_Pressed: break;
        case Invader_Button_Center_Released: LEDS_Off(LEDS_RED); LEDS_Off(LEDS_GREEN); break;
        default: break;
      }
    } else {
      vTaskDelay(pdMS_TO_TICKS(2));
    }
  }
}

void Invader_Init(void) {
  BaseType_t res;

  res = xTaskCreate(gameTask, "game", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }

  eventQueue = xQueueCreate(EVENT_QUEUE_LENGTH, EVENT_QUEUE_ELEM_SIZE);
  if (eventQueue==NULL) {
    for(;;){} /* out of memory? */
  }
  vQueueAddToRegistry(eventQueue, "eventQueue");

}
