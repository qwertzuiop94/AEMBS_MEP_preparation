/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Invader.h"
#include "McuRTOS.h"
#include "leds.h"

static Invader_event_e invader_event = Invader_Event_None; /*!< Event set by the debouncing */

void Invader_SendEvent(Invader_event_e event) {
  /* this one gets accessed either by the TmrSrv (Debouncing callback) or by the game task */
  taskENTER_CRITICAL();
  if (invader_event!=Invader_Event_None) { /* event still pending? */
    /* really not ideal to do a delay: a Yield does not work here, as we might be the highest priority task. Wait max for 1 ms, otherwise overwrite event */
    vTaskDelay(pdMS_TO_TICKS(5));
    /* other solutions: Bit-Set (but cannot handle multiple set), or yield with a consumer task at the same prio as the producer, or doing a resume of a suspended (high-prio) consumer task */
  }
  invader_event = event;
  taskEXIT_CRITICAL();
}

static Invader_event_e Invader_ReceiveEvent(void) {
  Invader_event_e event;

  if (invader_event==Invader_Event_None) {
    return Invader_Event_None;
  }
  taskENTER_CRITICAL();
  event = invader_event;
  invader_event = Invader_Event_None; /* clear event */
  taskEXIT_CRITICAL();
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
}
