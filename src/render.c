#include "render.h"


int render(Appstate *state){

    SDLite_Display *display = state->display;
    SDL_Renderer *renderer = SDLite_Display_GetSDLRenderer(display);

    SDLite_DisplayClear(display);

    SDLite_Render_Text(state->fps_text);
    SDLite_Render_Text(state->player_one.score.score_text);
    SDLite_Render_Text(state->player_two.score.score_text);
    SDLite_Render_Text(state->speed_multiplier.multiplier_text);
    SDLite_Render_Sprite(display, state->ball.sprite);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   
    
    SDL_RenderFillRect(renderer, &state->horizontal_bar);
    
    SDLite_DisplayPresent(display);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    return 0;
}
