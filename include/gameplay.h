#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "SDLite.h"

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

    Player player_one;
    Player player_two;

    SDL_FRect horizontal_bar;
    SDLite_Text *fps_text;
    Speed_Multiplier speed_multiplier;
    
    SDL_FRect ball_arena;
    Pong_Ball ball;

} Gameplay;


#endif