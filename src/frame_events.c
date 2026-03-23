#include "frame_events.h"
#include "update.h"

void handle_speed_multiplier(Gameplay *gameplay, SDLite_Input *input, int window_width){

    if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_LEFT)){

        gameplay->speed_multiplier.multiplier -= 0.5f;
        gameplay->speed_multiplier.multiplier = gameplay->speed_multiplier.multiplier < 0.5f ? 0.5f : gameplay->speed_multiplier.multiplier;
        update_multiplier(gameplay, window_width);
        
    } else if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_RIGHT)){
    
        gameplay->speed_multiplier.multiplier += 0.5f;
        gameplay->speed_multiplier.multiplier = gameplay->speed_multiplier.multiplier > 5.0f ? 5.0f : gameplay->speed_multiplier.multiplier;
        update_multiplier(gameplay, window_width);
        
    }
}



int frame_events(Appstate *state){

    if(SDLite_Input_KeyPressed(state->input, SDL_SCANCODE_ESCAPE)) return 1;
    
    if(gamestate == GAME_PLAYING){

        handle_speed_multiplier(state->gameplay, state->input, state->window_width);

    } else if(gamestate == GAME_MAIN_MENU){



    } else if(gamestate == GAME_SETTINGS){



    }

    return 0;
}