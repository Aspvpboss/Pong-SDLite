#include "quit.h"

void free_gameplay(Gameplay *gameplay){

    SDLite_DestroyText(gameplay->fps_text);
    SDLite_DestroyText(gameplay->player_one.score.score_text);
    SDLite_DestroyText(gameplay->player_two.score.score_text);
    SDLite_DestroyText(gameplay->speed_multiplier.multiplier_text);
    SDLite_DestroySprite(gameplay->ball.sprite);


}



void free_appstate(Appstate *state){

    SDLite_DestroyDisplay(state->display);
    SDLite_DestroyInput(state->input);
    SDLite_DestroyTime(state->time);

}



void SDL_AppQuit(void *appstate, SDL_AppResult result){

    Appstate *state = (Appstate*)(appstate);

    if(!state)
        return;  

    free_gameplay(state->gameplay);
    free_appstate(state);

    t_free(state);

    SDLite_Quit();

}