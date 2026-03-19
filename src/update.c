#include "update.h"



void center_text(SDLite_Text *text, int y, int window_width){

    SDL_FRect render_rect = {0};
    SDLite_Text_Get_RenderRect(text, &render_rect);
    SDLite_Text_SetPosition(text, (window_width - render_rect.w) / 4, y);
    
}


void update_fps(Appstate *state, SDLite_Text *text, SDLite_Time *time){

    char fps_string[20];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", SDLite_Time_GetFPS(time));

    SDLite_Text_SetString(text, fps_string);
    center_text(text, 0, state->window_width);
    
}


void update_multiplier(Appstate *state){

    char multiplier_string[20];
    snprintf(multiplier_string, sizeof(multiplier_string), "x%.1f", state->speed_multiplier.multiplier);
    
    SDLite_Text_SetString(state->speed_multiplier.multiplier_text, multiplier_string);

    center_text(state->speed_multiplier.multiplier_text, hud_size / 4, state->window_width); 
}


void update_score(Score *player_score, int new_score, int window_width){

    player_score->score = new_score;

    char score_string[20];
    snprintf(score_string, sizeof(score_string), "%d", player_score->score);
    
    SDLite_Text_SetString(player_score->score_text, score_string);

    if(player_score->text_alignment == TTF_HORIZONTAL_ALIGN_LEFT){

        SDLite_Text_SetPosition(player_score->score_text, 0, 2);

    } else if(player_score->text_alignment == TTF_HORIZONTAL_ALIGN_RIGHT){

        int width;
        TTF_GetStringSize(SDLite_Text_GetTTFFont(player_score->score_text), score_string, 0, &width, NULL);
        SDLite_Text_SetPosition(player_score->score_text, window_width / 2 - width / 2, 2);

    }


}


void update_ball_position(Appstate *state){

    SDL_FRect *arena = &state->ball_arena;
    SDL_FRect current_position;
    SDLite_Sprite_Get_RenderRect(state->ball.sprite, &current_position);

    double delta_time = SDLite_Time_GetDT(state->time);
    double speed_multiplier = state->speed_multiplier.multiplier;

    current_position.x += state->ball.x_velocity * state->ball.x_speed * delta_time * speed_multiplier;
    current_position.y += state->ball.y_velocity * state->ball.y_speed * delta_time * speed_multiplier;

    if(current_position.x < arena->x){
        current_position.x = arena->x;
        state->ball.x_velocity *= -1;
    } else if(current_position.x + current_position.w > arena->x + arena->w){
        current_position.x = arena->x + arena->w - current_position.w;
        state->ball.x_velocity *= -1;
    }   

    if(current_position.y < arena->y){

        current_position.y = arena->y;
        state->ball.y_velocity *= -1;

    } else if(current_position.y + current_position.h > arena->y + arena->h){

        current_position.y = arena->y + arena->h - current_position.h;
        state->ball.y_velocity *= -1;

    }

    SDLite_Sprite_Set_Position(state->ball.sprite, (SDL_FPoint){current_position.x, current_position.y});

}




int update(Appstate *state){

    if(SDLite_Time_Is_FPSUpdated(state->time))
        update_fps(state, state->fps_text, state->time);

    update_ball_position(state);
    
    return 0;
}

