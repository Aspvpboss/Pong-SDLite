#include "iterate.h"
#include "render.h"
#include "update.h"
#include "frame_events.h"
#include "gamestate_init.h"
#include "quit.h"


SDL_AppResult SDL_AppIterate(void *appstate){

    Appstate *state = (Appstate*)(appstate);

    switch(gamestate){

        case GAME_PLAYING:
            if(!state->gameplay){
                state->gameplay = init_gameplay(state);
                if(!state->gameplay)
                    return SDL_APP_FAILURE;
            }
            if(state->main_menu){
                free_main_menu(state->main_menu);
                state->main_menu = NULL; 
            }
            
            break;

        case GAME_MAIN_MENU:
            if(!state->main_menu){
                state->main_menu = init_main_menu(state);
                if(!state->main_menu)
                    return SDL_APP_FAILURE;
            }
            if(state->gameplay){
                free_gameplay(state->gameplay);
                state->gameplay = NULL; 
            }
            break;

        default:
            break;

    }

    if(frame_events(state))
        return SDL_APP_SUCCESS;   

    if(update(state))
        return SDL_APP_FAILURE; 

    if(render(state))
        return SDL_APP_FAILURE;


    SDLite_Input_UpdateAllPrev(state->input);
    SDLite_TimeFunctions(state->time);

    return SDL_APP_CONTINUE;
}