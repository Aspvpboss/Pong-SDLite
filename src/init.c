
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include "update.h"
#include "SDL3/SDL_main.h"





int init_text(Appstate *state){


    state->player_one.score.score = 0;
    state->player_one.score.text_alignment = TTF_HORIZONTAL_ALIGN_LEFT;
    state->player_two.score.score = 0;
    state->player_two.score.text_alignment = TTF_HORIZONTAL_ALIGN_RIGHT;
    state->speed_multiplier.multiplier = 1.0f;
   
    
    state->fps_text = SDLite_CreateText(state->display, "FPS: 0", "assets/default.ttf", hud_size / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->speed_multiplier.multiplier_text = SDLite_CreateText(state->display, "x1.0", "assets/default.ttf", hud_size / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->player_one.score.score_text = SDLite_CreateText(state->display, NULL, "assets/default.ttf", hud_size, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->player_two.score.score_text = SDLite_CreateText(state->display, NULL, "assets/default.ttf", hud_size, window_width / 2 - hud_size, 0, (SDL_Color){255, 255, 255, 255});


    if(!state->player_one.score.score_text || !state->player_two.score.score_text || !state->speed_multiplier.multiplier_text || !state->fps_text){
        SDL_Log("Error: %s\n", SDL_GetError());
        return 1;
    }

    update_score(&state->player_one.score, 0);
    update_score(&state->player_two.score, 244); 

    update_multiplier(state);

    center_text(state->fps_text, 0);
    center_text(state->speed_multiplier.multiplier_text, hud_size / 4);

    return 0;
}



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    if(SDLite_Init(NULL, NULL, true, false)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    state->fps_text = NULL;
    state->input = NULL;
    state->time = NULL;
    state->display = NULL;
    state->player_one.score.score_text = NULL;
    state->player_two.score.score_text = NULL;
    state->speed_multiplier.multiplier_text = NULL;
    state->horizontal_bar = NULL;



    state->ball_arena.x = 0;
    state->ball_arena.y = hud_size + horizontal_bar_height;
    state->ball_arena.w = window_width;
    state->ball_arena.h = window_height - hud_size - horizontal_bar_height;

    state->ball.x_velocity = 1.0f;
    state->ball.y_velocity = 1.0f;  
    state->ball.x_speed = 350.0f;
    state->ball.y_speed = 350.0f;
    state->ball.sprite = NULL;

    state->display = SDLite_CreateDisplay("Pong", window_width, window_height, SDL_WINDOW_MAXIMIZED);
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    state->time = SDLite_CreateTime(144);
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->input = SDLite_CreateInput();
    if(!state->input){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->horizontal_bar = SDLite_Create_RectSprite((SDL_FRect){0, hud_size, window_width, horizontal_bar_height}, (SDL_Color){255, 255, 255, 255}, true);
    if(!state->horizontal_bar){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->ball.sprite = SDLite_Create_RectSprite((SDL_FRect){(state->ball_arena.x + state->ball_arena.w) / 2, (state->ball_arena.y + state->ball_arena.h) / 2, 10, 10}, (SDL_Color){255, 255, 255, 255}, true);
    if(!state->ball.sprite){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    if(init_text(state)){
        return SDL_APP_FAILURE;
    }

    srand(time());

    return SDL_APP_CONTINUE;
}
