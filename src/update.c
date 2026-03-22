#include "update.h"



void center_text(SDLite_Text *text, int y, int window_width){

    SDL_FRect render_rect = {0};
    SDLite_Text_Get_RenderRect(text, &render_rect);
    SDLite_Text_SetPosition(text, (window_width - render_rect.w) / 4, y);
    
}


void update_fps(SDLite_Text *text, SDLite_Time *time){

    char fps_string[20];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", SDLite_Time_GetFPS(time));

    SDLite_Text_SetString(text, fps_string);
    
}


void update_multiplier(Gameplay *gameplay, int window_width){

    char multiplier_string[20];
    snprintf(multiplier_string, sizeof(multiplier_string), "x%.1f", gameplay->speed_multiplier.multiplier);
    
    SDLite_Text_SetString(gameplay->speed_multiplier.multiplier_text, multiplier_string);

    center_text(gameplay->speed_multiplier.multiplier_text, GAMEPLAY_HUD_SIZE / 4, window_width); 
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


void update_ball_position(Gameplay *gameplay, SDLite_Time *time){

    SDL_FRect *arena = &gameplay->ball_arena;
    SDL_FRect current_position;
    SDLite_Sprite_Get_RenderRect(gameplay->ball.sprite, &current_position);

    double delta_time = SDLite_Time_GetDT(time);
    double speed_multiplier = gameplay->speed_multiplier.multiplier;

    current_position.x += gameplay->ball.x_velocity * gameplay->ball.x_speed * delta_time * speed_multiplier;
    current_position.y += gameplay->ball.y_velocity * gameplay->ball.y_speed * delta_time * speed_multiplier;

    if(current_position.x < arena->x){
        current_position.x = arena->x;
        gameplay->ball.x_velocity *= -1;
    } else if(current_position.x + current_position.w > arena->x + arena->w){
        current_position.x = arena->x + arena->w - current_position.w;
        gameplay->ball.x_velocity *= -1;
    }   

    if(current_position.y < arena->y){

        current_position.y = arena->y;
        gameplay->ball.y_velocity *= -1;

    } else if(current_position.y + current_position.h > arena->y + arena->h){

        current_position.y = arena->y + arena->h - current_position.h;
        gameplay->ball.y_velocity *= -1;

    }

    SDLite_Sprite_Set_Position(gameplay->ball.sprite, (SDL_FPoint){current_position.x, current_position.y});

}




int update(Appstate *state){

    Gameplay *gameplay = state->gameplay;

    if(gamestate == GAME_PLAYING){

        if(SDLite_Time_Is_FPSUpdated(state->time)){
            update_fps(gameplay->fps_text, state->time);
            center_text(gameplay->fps_text, 0, state->window_width);
        }

        update_ball_position(state, state->time);

    }

    
    return 0;
}

