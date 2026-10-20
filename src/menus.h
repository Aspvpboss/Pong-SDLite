#ifndef MENUS_H
#define MENUS_H

#include <SDLite/SDLite.h>

typedef struct{

    SDLite_Text *title_text;
    SDLite_Text *play_text;
    SDLite_Text_Font *font;

} Main_Menu;


typedef struct{

    SDLite_Text *title_text;
    SDLite_Text_Font *font;
    double seconds_elapsed;
    double seconds_duration;

} Win_Menu;



#endif