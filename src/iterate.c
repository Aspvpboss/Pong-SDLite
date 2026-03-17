#include "iterate.h"
#include "render.h"
#include "update.h"
#include "frame_events.h"


SDL_AppResult SDL_AppIterate(void *appstate){

    Appstate *state = (Appstate*)(appstate);

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