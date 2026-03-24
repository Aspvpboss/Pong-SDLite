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

    SDLite_Input *input = state->input;

    if(SDLite_Input_KeyPressed(input, SDL_SCANCODE_ESCAPE)) return 1;

    if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_M)){
        
        const char *gamestate_str = NULL;
        if(gamestate == GAME_PLAYING) gamestate_str = "GAME_PLAYING";
        if(gamestate == GAME_MAIN_MENU) gamestate_str = "GAME_MAIN_MENU";
        if(gamestate == GAME_SETTINGS) gamestate_str = "GAME_SETTINGS";
       
        SDL_Log("Debug Info:\n");
        SDL_Log("Total heap usage: %lld bytes\n", check_memory_usage());
        SDL_Log("Gamestate %s", gamestate_str);
    }
    
    switch(gamestate){
        case GAME_PLAYING:
            handle_speed_multiplier(state->gameplay, input, state->window_width);
            if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_Q)){
                gamestate = GAME_MAIN_MENU;        
                return -1;
            }
            break;

        case GAME_MAIN_MENU:
            if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_RETURN)){
                gamestate = GAME_PLAYING;
                return -1;
            }
            break;

        case GAME_SETTINGS:
            break;

        default:
            break;
    }

    return 0;
}