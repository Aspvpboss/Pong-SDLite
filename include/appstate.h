#pragma once

#include "SDLite.h"
#include <math.h>


#define window_width 1000
#define window_height 800
#define hud_size 40
#define horizontal_bar_height 5



typedef struct{

    SDLite_Text *score_text; 
    int score;
    
} Score;

typedef struct{

    SDLite_Text *multiplier_text;
    float multiplier;

} Speed_Multiplier;

typedef struct{

    int scale;
    SDL_Rect ball_arena;

    SDLite_Display *display;
    SDLite_Time *time;
    SDLite_Input *input;

    SDLite_Text *fps_text;
    Score player_one;
    Score player_two;
    Speed_Multiplier speed_multiplier;

    SDLite_Sprite *horizontal_bar; 
    

} Appstate;
