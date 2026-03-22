#ifndef APPSTATE_PONG_H
#define APPSTATE_PONG_H

#include "gameplay.h"
#include <math.h>


#define WINDOW_START_WIDTH 1000
#define WINDOW_START_HEIGHT 800


typedef struct{

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