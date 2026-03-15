
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include "SDL3/SDL_main.h"


const int window_width = 1000;
const int window_height = 800;
const int hud_size = 40;
const int horizontal_bar_height = 10;



int init_text(Appstate *state, int hud_size){


    state->player_one.score = 0;
    state->player_two.score = 0;
    state->speed_multiplier.multiplier = 1.0f;
   
    
    state->fps_text = SDLite_CreateText(
        state->display, "FPS: 0", "assets/default.ttf", hud_size / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    
    state->speed_multiplier.multiplier_text = SDLite_CreateText(
        state->display, "x1.0", "assets/default.ttf", hud_size / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    
    state->player_one.score_text = SDLite_CreateText(
        state->display, NULL, "assets/default.ttf", hud_size, 0, 0, (SDL_Color){255, 255, 255, 255});
    
    state->player_two.score_text = SDLite_CreateText(
        state->display, NULL, "assets/default.ttf", hud_size, 0, 0, (SDL_Color){255, 255, 255, 255});


    if(!state->player_one.score_text || !state->player_two.score_text || !state->speed_multiplier.multiplier_text || !state->fps_text){
        SDL_Log("Error: %s\n", SDL_GetError());
        return 1;
    }
       
    SDL_FRect render_rect = {0};
    SDLite_Text_Get_RenderRect(state->fps_text, &render_rect);
    SDLite_Text_SetPosition(state->fps_text, (window_width - render_rect.w) / 4, 0);
    SDLite_Text_Get_RenderRect(state->speed_multiplier.multiplier_text, &render_rect);
    SDLite_Text_SetPosition(state->speed_multiplier.multiplier_text, (window_width - render_rect.w) / 4, 0);

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
    state->player_one.score_text = NULL;
    state->player_two.score_text = NULL;
    state->speed_multiplier.multiplier_text = NULL;
    state->horizontal_bar = NULL;



    state->ball_arena.x = 0;
    state->ball_arena.y = hud_size + horizontal_bar_height;
    state->ball_arena.w = window_width;
    state->ball_arena.h = window_height - hud_size - horizontal_bar_height;

    
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


    if(init_text(state, hud_size)){
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}
