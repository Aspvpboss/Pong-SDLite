#include "gamestate_init.h"


Gameplay* init_gameplay(Appstate *state){

    Gameplay *gameplay = t_malloc(sizeof(Gameplay));
    if(!gameplay) return NULL;

    
    int window_width = state->window_width;
    int window_height = state->window_height;

    gameplay->player_one.score.score_text = NULL;
    gameplay->player_two.score.score_text = NULL;
    gameplay->speed_multiplier.multiplier_text = NULL;


    gameplay->ball_arena.x = 0;
    gameplay->ball_arena.y = GAMEPLAY_HUD_SIZE + GAMEPLAY_HORIZONTAL_BAR_HEIGHT;
    gameplay->ball_arena.w = window_width;
    gameplay->ball_arena.h = window_height - GAMEPLAY_HUD_SIZE - GAMEPLAY_HORIZONTAL_BAR_HEIGHT;

    gameplay->ball.x_velocity = 1.0f;
    gameplay->ball.y_velocity = 1.0f;  
    gameplay->ball.x_speed = 350.0f;
    gameplay->ball.y_speed = 350.0f;
    gameplay->ball.sprite = NULL;

    gameplay->player_one.score.score = 0;
    gameplay->player_one.score.text_alignment = TTF_HORIZONTAL_ALIGN_LEFT;
    gameplay->player_two.score.score = 0;
    gameplay->player_two.score.text_alignment = TTF_HORIZONTAL_ALIGN_RIGHT;
    gameplay->speed_multiplier.multiplier = 1.0f;

    gameplay->horizontal_bar = (SDL_FRect){0, GAMEPLAY_HUD_SIZE, window_width, GAMEPLAY_HORIZONTAL_BAR_HEIGHT};

    int random_y_offset;
    random_y_offset = RANDOM_RANGE(-10, 10);
    SDL_FRect ball_position= {};
    ball_position.x = (gameplay->ball_arena.x + gameplay->ball_arena.w) / 2;
    ball_position.y = (gameplay->ball_arena.y + gameplay->ball_arena.h) / 2 + random_y_offset;
    ball_position.w = 10;
    ball_position.h = 10;

    gameplay->ball.sprite = SDLite_Create_RectSprite(ball_position, (SDL_Color){255, 255, 255, 255}, true);
    if(!gameplay->ball.sprite){
        free_gameplay(gameplay); 
        SDL_Log("Error: %s\n", SDL_GetError());
        return NULL;
    }

    
    gameplay->fps_text = SDLite_CreateText(state->display, "FPS: 0", FONT_PATH, GAMEPLAY_HUD_SIZE / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    gameplay->speed_multiplier.multiplier_text = SDLite_CreateText(state->display, "x1.0", FONT_PATH, GAMEPLAY_HUD_SIZE / 2, 0, 0, (SDL_Color){255, 255, 255, 255});
    gameplay->player_one.score.score_text = SDLite_CreateText(state->display, NULL, FONT_PATH, GAMEPLAY_HUD_SIZE, 0, 0, (SDL_Color){255, 255, 255, 255});
    gameplay->player_two.score.score_text = SDLite_CreateText(state->display, NULL, FONT_PATH, GAMEPLAY_HUD_SIZE, window_width / 2 - GAMEPLAY_HUD_SIZE, 0, (SDL_Color){255, 255, 255, 255});


    if(!gameplay->player_one.score.score_text || !gameplay->player_two.score.score_text || !gameplay->speed_multiplier.multiplier_text || !gameplay->fps_text){
        free_gameplay(gameplay); 
        SDL_Log("Error: %s\n", SDL_GetError());
        return NULL;
    }

    update_score(&gameplay->player_one.score, 0, window_width);
    update_score(&gameplay->player_two.score, 244, window_width); 

    update_multiplier(gameplay, window_width);

    center_text(gameplay->fps_text, 0, window_width);
    center_text(gameplay->speed_multiplier.multiplier_text, GAMEPLAY_HUD_SIZE / 4, window_width);



    return gameplay;
}


Main_Menu* init_main_menu(Appstate *state){

    Main_Menu *main_menu = t_malloc(sizeof(Main_Menu));
    if(!main_menu) return NULL;

    main_menu->title_text = SDLite_CreateText(state->display, "PONG", FONT_PATH, 100, 0, 0, (SDL_Color){255, 255, 255, 255});
    if(!main_menu->title_text){
        free_main_menu(main_menu); 
        SDL_Log("Error: %s\n", SDL_GetError());
        return NULL;
    }

    center_text(main_menu->title_text, state->window_height / 4 - 80, state->window_width);

    const char *play_string = "Press Enter to Play";
    main_menu->play_text = SDLite_CreateText(state->display, play_string, FONT_PATH, 50, 0, 0, (SDL_Color){255, 255, 255, 255});
    if(!main_menu->play_text){
        free_main_menu(main_menu); 
        SDL_Log("Error: %s\n", SDL_GetError());
        return NULL;
    }

    center_text(main_menu->play_text, state->window_height / 4 - 20, state->window_width);

    return main_menu;
}