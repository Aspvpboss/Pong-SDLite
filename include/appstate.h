#ifndef APPSTATE_PONG_H
#define APPSTATE_PONG_H

#include "main_menu.h"
#include "gameplay.h"
#include "SDLite.h"
#include <math.h>


#define WINDOW_START_WIDTH 1000
#define WINDOW_START_HEIGHT 800
#define FONT_PATH "assets/default.ttf"
#define RANDOM_RANGE(min, max) (rand() % ((max) - (min) + 1) + (min))

typedef enum{

    GAME_PLAYING,
    GAME_MAIN_MENU,
    GAME_SETTINGS
    
} Gamestate;

extern Gamestate gamestate;


typedef struct{

    int window_width, window_height;
    SDLite_Display *display;
    SDLite_Time *time;
    SDLite_Input *input;

    Gameplay *gameplay;

} Appstate;


#endif