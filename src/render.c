#include "render.h"


int render(Appstate *state){

    SDLite_Display *display = state->display;

    SDLite_DisplayClear(display);

    SDLite_Render_Text(state->fps_text);
    SDLite_Render_Text(state->player_one.score.score_text);
    SDLite_Render_Text(state->player_two.score.score_text);
    SDLite_Render_Text(state->speed_multiplier.multiplier_text);
    SDLite_Render_Sprite(display, state->horizontal_bar);
    SDLite_Render_Sprite(display, state->ball.sprite);

    // SDL_SetRenderDrawColor(SDLite_Display_GetSDLRenderer(display), 255, 0, 0, 255);   
    // SDL_RenderFillRect(SDLite_Display_GetSDLRenderer(display), &state->ball_arena);
    // SDL_SetRenderDrawColor(SDLite_Display_GetSDLRenderer(display), 0, 0, 0, 0);

    SDLite_DisplayPresent(display);

    return 0;
}
