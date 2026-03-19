#pragma once

#include "SDLite.h"
#include <math.h>

#define window_start_width 1000
#define window_start_height 800
#define hud_size 40
#define horizontal_bar_height 5



typedef struct{

    SDLite_Text *score_text; 
    int score;
    TTF_HorizontalAlignment text_alignment;
    
} Score;

typedef struct{

    char filler;

} Paddle;


typedef struct{

    Score score;
    Paddle paddle; 

} Player;


typedef struct{

    SDLite_Text *multiplier_text;
    float multiplier;

} Speed_Multiplier;

typedef struct{

    SDLite_Sprite *sprite;
    double x_velocity;
    double y_velocity;
    double x_speed;
    double y_speed;

} Pong_Ball;



typedef struct{

    int window_width, window_height;
    SDLite_Display *display;
    SDLite_Time *time;
    SDLite_Input *input;

    Player player_one;
    Player player_two;

    SDL_FRect horizontal_bar;
    SDLite_Text *fps_text;
    Speed_Multiplier speed_multiplier;
    
    SDL_FRect ball_arena;
    Pong_Ball ball;

} Appstate;
