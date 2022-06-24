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
#include "graphic/sprite.h"
#include "ship.h"
#include "alien.h"
#include "missile.h"


/* -------------- message queue ----------------------*/
typedef Invader_event_e event_e;
static QueueHandle_t eventQueue; /* queue handle */
#define EVENT_QUEUE_LENGTH    (5) /* number of elements in queue */
#define EVENT_QUEUE_ELEM_SIZE (sizeof(event_e)) /* size of a queue item */

/* -------------- display stuff ----------------------*/
typedef struct GameData_t {
	  Sprite_t *ship;
	  Sprite_t *missiles;
	  Sprite_t *aliens;
	} GameData_t;
static GameData_t game;


static void CheckOutsideMissiles(void) {
  Sprite_t *s, *next;

	s = game.missiles;

	while (s != NULL) {
		//check hit the boearder
		if (s->posY == 0) {
			next = s->next;
			Sprite_DeleteFromList(&game.missiles, s);
			s = next;
		} else if (s->posY >= 61) {
			next = s->next;
			Sprite_DeleteFromList(&game.missiles, s);
			s = next;
		} else {
			s = s->next;

		}

	}
}

static bool AreaIsClear(Sprite_t *spriteList, int x0, int y0, int x1, int y1) {
  Sprite_t *sprite;

  sprite = spriteList;
  while (sprite!=NULL) {
    if (Sprite_OverlappingAreas(sprite->posX, sprite->posX+sprite->images->image->width, sprite->posY, sprite->posY+sprite->images->image->height, x0, x1, y0, y1)) {
      return false; /* overlap */
    }
    sprite = sprite->next;
  }
  return true; /* no overlap */
}

static void NewMissileFromAlien(Sprite_t *alien) {
  Sprite_t *missile;
  PIMAGE missileImage;

  if (alien!=NULL) {
    /* check if the area below the alien is clear: for this we assume to have one row in front of us */
    if (AreaIsClear(game.aliens, alien->posX, alien->posY+alien->images->image->height+1, alien->posX+alien->images->image->width, alien->posY+2*alien->images->image->height)) {
    /* only if the alien ship does not shoot down another alien ship */
      missileImage = Missile_GetImage();
      missile = Sprite_New(Sprite_NewImage(missileImage), alien->posX + (alien->images->image->width-missileImage->width)/2 + 1, alien->posY + alien->images->image->height);
      missile->move.x = 0;
      missile->move.y = 1; /* moving from top to bottom */
      Sprite_AddToList(&game.missiles, missile);
    }
  }
}

static bool SpriteCollidedWithTarget(Sprite_t *sprite, Sprite_t **targetList) {
  Sprite_t *target, *next;

  /* check if the sprite hits one in the target list: if yes, remove target */
  target = *targetList;
  while (target!=NULL) { /* check all targets, if we have hit one of them */
    next = target->next;
    if (Sprite_Overlap(sprite, target)) { /* hit a target? */
      Sprite_DeleteFromList(targetList, target); /* remove target from list */
      return true; /* yes, sprite has hit a target */
    }
    target = next;
  } /* all targets */
  return false; /* no target hit */
}

static void CheckSpriteCollision(Sprite_t **spriteList, Sprite_t **targetList) {
  Sprite_t *sprite, *next, *newList = NULL;

  sprite = *spriteList;
  while (sprite!=NULL) { /* iterate list */
    next = sprite->next;
    Sprite_UnlinkFromList(spriteList, sprite); /* temporarily, remove current sprite from list, will be re-added later */
    if (SpriteCollidedWithTarget(sprite, targetList)) {
      Sprite_FreeSprite(sprite); /* delete and free memory for sprite */
    } else {
      Sprite_AddToList(&newList, sprite); /* add to temporary list */
    }
    sprite = next; /* next in list */
  } /* while */
  *spriteList = newList;
}

static void getShootAlien(void)	{
	int idx;
	unsigned int nofAliens;
	Sprite_t *sprite;

	/* create random new alien missiles */
	nofAliens = Sprite_NofInList(game.aliens);
	idx = McuUtility_random(0, nofAliens*20); /* pick an alien ship. Larger range to reduce number of picks */
	if (idx<nofAliens) {
		sprite = Sprite_IndexInList(game.aliens, idx);
		NewMissileFromAlien(sprite);
	}
}


static void UpateModel(void) {
	CheckSpriteCollision(&game.missiles, &game.missiles); /* do missiles collide? */
	CheckSpriteCollision(&game.missiles, &game.aliens); /* have we hit aliens? */
	CheckSpriteCollision(&game.missiles, &game.ship); /* have aliens hit the ship? */
	CheckSpriteCollision(&game.ship, &game.aliens); /* does the ship collide with aliens? */
	CheckOutsideMissiles(); /* are missiles going outside the screen? */
	Sprite_AgeAndCheckIfAlive(&game.missiles);
	Sprite_AgeAndCheckIfAlive(&game.aliens);
	Sprite_AgeAndCheckIfAlive(&game.ship);
	getShootAlien();


}








static void ShootMissile(void) {
  PIMAGE missileImage;
  Sprite_t *missile;

  missileImage = Missile_GetImage();
  missile = Sprite_New(
      Sprite_NewImage(missileImage),  /* image of missile */
      game.ship->posX + (game.ship->images->image->width - missileImage->width)/2, game.ship->posY - missileImage->height
	  );
  missile->move.x = 0;
  missile->move.y = -1; /* moving from bottom to top */
  Sprite_AddToList(&game.missiles, missile);
}

static void UpdateView(void) {
	/* update buffer */
	  McuGDisplaySSD1306_Clear();
	  Sprite_Paint(game.ship);
	  Sprite_PaintList(game.aliens);
	  Sprite_PaintList(game.missiles);
	  /* update screen */
	  I2CBus_LockBus();
	  McuGDisplaySSD1306_UpdateFull(); /* update display */
	  I2CBus_ReleaseBus();
}



static void CreateGameAliens(void) {
  McuGDisplaySSD1306_PixelDim x, y;
  PIMAGE bitmap = alien_GetImage();
  SpriteImage_t *image;

  for(y=0; y<20; y+=bitmap->height+2) {
    for(x=0; x<McuGDisplaySSD1306_GetWidth()-bitmap->width; x += bitmap->width+2) {
      image = Sprite_NewImage(bitmap);
      Sprite_AddToList(&game.aliens, Sprite_New(image, x, y));
    }

  }
}

static void CleanupGame(void) {
  Sprite_DeleteList(&game.ship);
  Sprite_DeleteList(&game.aliens);
  Sprite_DeleteList(&game.missiles);
}

static void CreatGameShip(void){
	  PIMAGE ship = ship_GetImage();
	  SpriteImage_t *image = Sprite_NewImage(ship);
	  game.ship = Sprite_New(image, 63, 55);
}

static void CreateGame(void) {
	CreatGameShip();
	CreateGameAliens();
}

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


static bool CheckWonOrLost(void) {
  if (game.ship==NULL) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    Show2Liner((const unsigned char*)"Game", (const unsigned char*)"Lost :-(");
    vTaskDelay(pdMS_TO_TICKS(3000));
    Show2Liner((const unsigned char*)"Press button", (const unsigned char*)"to start");
    WaitForKeyPress();
    return true; /* lost */
  } else if (game.aliens==NULL) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    Show2Liner((const unsigned char*)"Victory!", (const unsigned char*)":-)");
    vTaskDelay(pdMS_TO_TICKS(3000));
    Show2Liner((const unsigned char*)"Press button", (const unsigned char*)"to start");
    WaitForKeyPress();
    return true; /* victory! */
  }
  return false;
}


static void GameIntro(void) {
	Show2Liner((const unsigned char*) "Space",(const unsigned char*) "Invader");
	vTaskDelay(pdMS_TO_TICKS(3000));
	Show2Liner((const unsigned char*) "Press button",(const unsigned char*) "to start");
	WaitForKeyPress();
}


static void gameTask(void *pv) {  Invader_event_e event;

	I2CBus_LockBus();
	McuSSD1306_Init();
	I2CBus_ReleaseBus();
	McuGDisplaySSD1306_Init();

	GameIntro();
	CreateGame();
	UpdateView();

	for (;;) {
		event = Invader_ReceiveEvent(20);
	    UpateModel();
		if (event != Invader_Event_None) {
			switch (event) {
			case Invader_Button_Left_Pressed:
				LEDS_On(LEDS_RED);
				Sprite_MoveLimitedDisplay(game.ship, -1, 0);
				break;
			case Invader_Button_LeftRepeat_Pressed:
				break;
			case Invader_Button_Left_Released:
				LEDS_Off(LEDS_RED);
				break;

			case Invader_Button_Right_Pressed:
				LEDS_On(LEDS_GREEN);
				Sprite_MoveLimitedDisplay(game.ship, 1, 0);
				break;
			case Invader_Button_RightRepeat_Pressed:
				break;
			case Invader_Button_Right_Released:
				LEDS_Off(LEDS_GREEN);
				break;

			case Invader_Button_Up_Pressed:
				LEDS_On(LEDS_ORANGE);
				Sprite_MoveLimitedDisplay(game.ship, 0, -1);
				break;
			case Invader_Button_UpRepeat_Pressed:
				break;
			case Invader_Button_Up_Released:
				LEDS_Off(LEDS_ORANGE);
				break;

			case Invader_Button_Down_Pressed:
				Sprite_MoveLimitedDisplay(game.ship, 0, 1);
				LEDS_On(LEDS_TINY_BLUE);
				break;
			case Invader_Button_DownRepeat_Pressed:
				break;
			case Invader_Button_Down_Released:
				LEDS_Off(LEDS_TINY_BLUE);
				break;

			case Invader_Button_Center_Pressed:
		          ShootMissile();
		          LEDS_On(LEDS_RED);
				break;
			case Invader_Button_CenterRepeat_Pressed:
				break;
			case Invader_Button_Center_Released:
		          LEDS_Off(LEDS_RED);
				break;
			default:
				break;
			}
		    UpdateView();
		} else {
			vTaskDelay(pdMS_TO_TICKS(2));
		      UpdateView();
		      if (CheckWonOrLost()) {
		          CleanupGame();
		          CreateGame();
		        }
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
