#include "render.h"


int render(Appstate *state){

    SDLite_Display *display = state->display;

    SDLite_DisplayClear(display);

    SDLite_Render_Text(state->fps_text);
    SDLite_Render_Text(state->player_one.score_text);
    SDLite_Render_Text(state->player_two.score_text);
    SDLite_Render_Text(state->speed_multiplier.multiplier_text);
    SDLite_Render_Sprite(display, state->horizontal_bar);

    SDLite_DisplayPresent(display);

    return 0;
}
