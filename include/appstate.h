#ifndef APPSTATE_PONG_H
#define APPSTATE_PONG_H

#include "gameplay.h"
#include <math.h>


#define window_start_width 1000
#define window_start_height 800
#define hud_size 40
#define horizontal_bar_height 5

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


} Appstate;


#endif