#include "quit.h"





void SDL_AppQuit(void *appstate, SDL_AppResult result){

    Appstate *state = (Appstate*)(appstate);

    if(!state)
        return;  

    SDLite_DestroyDisplay(state->display);
    SDLite_DestroyInput(state->input);
    SDLite_DestroyTime(state->time);
    SDLite_DestroyText(state->fps_text);
    SDLite_DestroyText(state->player_one.score.score_text);
    SDLite_DestroyText(state->player_two.score.score_text);
    SDLite_DestroyText(state->speed_multiplier.multiplier_text);
    SDLite_DestroySprite(state->horizontal_bar);
    SDLite_DestroySprite(state->ball.sprite);

    t_free(state);

    SDLite_Quit();

}