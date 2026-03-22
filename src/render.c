#include "render.h"


int render(Appstate *state){

    SDLite_Display *display = state->display;
    SDL_Renderer *renderer = SDLite_Display_GetSDLRenderer(display);

    SDLite_DisplayClear(display);

    if(gamestate == GAME_PLAYING){

        Gameplay *gameplay = state->gameplay;

        SDLite_Render_Text(gameplay->fps_text);
        SDLite_Render_Text(gameplay->player_one.score.score_text);
        SDLite_Render_Text(gameplay->player_two.score.score_text);
        SDLite_Render_Text(gameplay->speed_multiplier.multiplier_text);
        SDLite_Render_Sprite(display, gameplay->ball.sprite);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   
        
        SDL_RenderFillRect(renderer, &gameplay->horizontal_bar);
        
    } else if(gamestate == GAME_MAIN_MENU){



    } else if(gamestate == GAME_SETTINGS){



    }

    
    SDLite_DisplayPresent(display);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    return 0;
}
