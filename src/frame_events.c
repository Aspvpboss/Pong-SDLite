#include "frame_events.h"
#include "update.h"

void handle_speed_multiplier(Appstate *state){

    if(SDLite_Input_KeyJustPressed(state->input, SDL_SCANCODE_LEFT)){

        state->speed_multiplier.multiplier -= 0.5f;
        state->speed_multiplier.multiplier = state->speed_multiplier.multiplier < 0.5f ? 0.5f : state->speed_multiplier.multiplier;
        update_multiplier(state);
        
    } else if(SDLite_Input_KeyJustPressed(state->input, SDL_SCANCODE_RIGHT)){
    
        state->speed_multiplier.multiplier += 0.5f;
        state->speed_multiplier.multiplier = state->speed_multiplier.multiplier > 5.0f ? 5.0f : state->speed_multiplier.multiplier;
        update_multiplier(state);
        
    }
}



int frame_events(Appstate *state){

    if(SDLite_Input_KeyPressed(state->input, SDL_SCANCODE_ESCAPE)) return 1;

    handle_speed_multiplier(state);

    return 0;
}