#include "sdl_events.h"
#include "update.h"

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    Appstate *state = (Appstate*)(appstate);

    if(event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    if(event->type == SDL_EVENT_WINDOW_RESIZED){

        state->window_width = event->window.data1;
        state->window_height = event->window.data2;

        state->ball_arena.w = state->window_width;
        state->ball_arena.h = state->window_height - hud_size - horizontal_bar_height;

        update_fps(state, state->fps_text, state->time);
        update_multiplier(state); 
        update_score(&state->player_one.score, state->player_one.score.score, state->window_width);
        update_score(&state->player_two.score, state->player_two.score.score, state->window_width);
        state->horizontal_bar.w = state->window_width;

    }

    return SDL_APP_CONTINUE;
}