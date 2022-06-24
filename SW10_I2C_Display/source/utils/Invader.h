/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INVADER_H_
#define INVADER_H_

typedef enum Invader_event_e {
  Invader_Event_None,

  Invader_Update_View,
  Invader_Game_Lost,
  Invader_Game_Won,

  Invader_Button_Left_Pressed,
  Invader_Button_LeftRepeat_Pressed,
  Invader_Button_Left_Released,

  Invader_Button_Right_Pressed,
  Invader_Button_RightRepeat_Pressed,
  Invader_Button_Right_Released,

  Invader_Button_Up_Pressed,
  Invader_Button_UpRepeat_Pressed,
  Invader_Button_Up_Released,

  Invader_Button_Down_Pressed,
  Invader_Button_DownRepeat_Pressed,
  Invader_Button_Down_Released,

  Invader_Button_Center_Pressed,
  Invader_Button_CenterRepeat_Pressed,
  Invader_Button_Center_Released,
} Invader_event_e;

/*!
 * \brief Used to notify game task about a button event from the debouncing
 * \param event Event from the list of possible events
 */
void Invader_SendEvent(Invader_event_e event);

/*!
 * \brief Module de-initialization
 */
void Invader_Deinit(void);

/*!
 * \brief Module de-initialization
 */
void Invader_Init(void);

#endif /* INVADER_H_ */
