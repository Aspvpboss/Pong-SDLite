#include "update.h"



void center_text(SDLite_Text *text, int y){

    SDL_FRect render_rect = {0};
    SDLite_Text_Get_RenderRect(text, &render_rect);
    SDLite_Text_SetPosition(text, (window_width - render_rect.w) / 4, y);
    
}


void update_fps(SDLite_Text *text, SDLite_Time *time){

    char fps_string[20];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.0f", SDLite_Time_GetFPS(time));

    SDLite_Text_SetString(text, fps_string);
    center_text(text, 0);
    
}


void update_multiplier(Appstate *state){

    char multiplier_string[20];
    snprintf(multiplier_string, sizeof(multiplier_string), "x%.1f", state->speed_multiplier.multiplier);
    
    SDLite_Text_SetString(state->speed_multiplier.multiplier_text, multiplier_string);

    center_text(state->speed_multiplier.multiplier_text, hud_size / 4); 
}


int update(Appstate *state){

    if(SDLite_Time_Is_FPSUpdated(state->time))
        update_fps(state->fps_text, state->time);

    update_multiplier(state);

    return 0;
}

