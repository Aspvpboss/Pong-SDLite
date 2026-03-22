
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
   
    
    state->fps_text = SDLite_CreateText(state->display, "FPS: 0", "assets/default.ttf", GAMEPLAY_HUD_SIZE / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->speed_multiplier.multiplier_text = SDLite_CreateText(state->display, "x1.0", "assets/default.ttf", GAMEPLAY_HUD_SIZE / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->player_one.score.score_text = SDLite_CreateText(state->display, NULL, "assets/default.ttf", GAMEPLAY_HUD_SIZE, 0, 0, (SDL_Color){255, 255, 255, 255});
    state->player_two.score.score_text = SDLite_CreateText(state->display, NULL, "assets/default.ttf", GAMEPLAY_HUD_SIZE, window_width / 2 - GAMEPLAY_HUD_SIZE, 0, (SDL_Color){255, 255, 255, 255});


    if(!state->player_one.score.score_text || !state->player_two.score.score_text || !state->speed_multiplier.multiplier_text || !state->fps_text){
        SDL_Log("Error: %s\n", SDL_GetError());
        return 1;
    }

    update_score(&state->player_one.score, 0, window_width);
    update_score(&state->player_two.score, 244, window_width); 

    update_multiplier(state);

    center_text(state->fps_text, 0, window_width);
    center_text(state->speed_multiplier.multiplier_text, GAMEPLAY_HUD_SIZE / 4, window_width);

    return 0;
}


int init_appstate(Appstate *state){

    state->gameplay = NULL;
    state->input = NULL;
    state->time = NULL;
    state->display = NULL;
    state->window_height = WINDOW_START_HEIGHT;
    state->window_width = WINDOW_START_WIDTH;

    state->display = 
        SDLite_CreateDisplay("Pong", state->window_width, state->window_height, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return 1;
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
        return 1;
    }

    state->input = SDLite_CreateInput();
    if(!state->input){
        SDL_Log("Error: %s\n", SDL_GetError());
        return 1;
    }

    
    return 0;
}


Gameplay* init_gameplay(Appstate *state){

    Gameplay *gameplay = t_malloc(sizeof(Gameplay));
    if(!gameplay) return NULL;

    int window_width = state->window_width;
    int window_height = state->window_height;

    gameplay->player_one.score.score_text = NULL;
    gameplay->player_two.score.score_text = NULL;
    gameplay->speed_multiplier.multiplier_text = NULL;


    gameplay->ball_arena.x = 0;
    gameplay->ball_arena.y = GAMEPLAY_HUD_SIZE + GAMEPLAY_HORIZONTAL_BAR_HEIGHT;
    gameplay->ball_arena.w = window_width;
    gameplay->ball_arena.h = window_height - GAMEPLAY_HUD_SIZE - GAMEPLAY_HORIZONTAL_BAR_HEIGHT;

    gameplay->ball.x_velocity = 1.0f;
    gameplay->ball.y_velocity = 1.0f;  
    gameplay->ball.x_speed = 350.0f;
    gameplay->ball.y_speed = 350.0f;
    gameplay->ball.sprite = NULL;


    gameplay->horizontal_bar = (SDL_FRect){0, GAMEPLAY_HUD_SIZE, window_width, GAMEPLAY_HORIZONTAL_BAR_HEIGHT};

    gameplay->ball.sprite = SDLite_Create_RectSprite((SDL_FRect){(gameplay->ball_arena.x + gameplay->ball_arena.w) / 2, (gameplay->ball_arena.y + gameplay->ball_arena.h) / 2, 10, 10}, (SDL_Color){255, 255, 255, 255}, true);
    if(!gameplay->ball.sprite){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    if(init_text(state)){
        return SDL_APP_FAILURE;
    }


    return gameplay;
}


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    if(SDLite_Init(NULL, NULL, true, false)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);
    if(!state){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(init_appstate(state)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    } 


    srand(time(NULL));

    return SDL_APP_CONTINUE;
}
