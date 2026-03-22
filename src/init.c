
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include "update.h"
#include "SDL3/SDL_main.h"
#include <time.h>

Gamestate gamestate;


int init_text(Appstate *state){

    int window_width = state->window_width;

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

    update_score(&state->player_one.score, 0, window_width);
    update_score(&state->player_two.score, 244, window_width); 

    update_multiplier(state);

    center_text(state->fps_text, 0, window_width);
    center_text(state->speed_multiplier.multiplier_text, hud_size / 4, window_width);

    return 0;
}


int zeroing_appstate(Appstate *state){


    return 0;
}


int init_appstate(Appstate *state){

    state->fps_text = NULL;
    state->input = NULL;
    state->time = NULL;

    state->display = NULL;
    state->window_height = window_start_height;
    state->window_width = window_start_width;

    return 0;
}



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    if(SDLite_Init(NULL, NULL, true, false)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    int window_width = state->window_width;
    int window_height = state->window_height;

    state->player_one.score.score_text = NULL;
    state->player_two.score.score_text = NULL;
    state->speed_multiplier.multiplier_text = NULL;


    state->ball_arena.x = 0;
    state->ball_arena.y = hud_size + horizontal_bar_height;
    state->ball_arena.w = window_width;
    state->ball_arena.h = window_height - hud_size - horizontal_bar_height;

    state->ball.x_velocity = 1.0f;
    state->ball.y_velocity = 1.0f;  
    state->ball.x_speed = 350.0f;
    state->ball.y_speed = 350.0f;
    state->ball.sprite = NULL;

    state->display = SDLite_CreateDisplay("Pong", window_width, window_height, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Window *window = SDLite_Display_GetSDLWindow(state->display);
    SDL_SetWindowMinimumSize(window, 500, 200);
    SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(display_id, &display_bounds);
    SDL_SetWindowMaximumSize(window, display_bounds.w, display_bounds.h); 

    state->time = SDLite_CreateTime(-1);
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->input = SDLite_CreateInput();
    if(!state->input){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->horizontal_bar = (SDL_FRect){0, hud_size, window_width, horizontal_bar_height};

    state->ball.sprite = SDLite_Create_RectSprite((SDL_FRect){(state->ball_arena.x + state->ball_arena.w) / 2, (state->ball_arena.y + state->ball_arena.h) / 2, 10, 10}, (SDL_Color){255, 255, 255, 255}, true);
    if(!state->ball.sprite){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    if(init_text(state)){
        return SDL_APP_FAILURE;
    }

    srand(time(NULL));

    return SDL_APP_CONTINUE;
}
