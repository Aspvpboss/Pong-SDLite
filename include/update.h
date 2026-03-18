#pragma once

#include "appstate.h"

int update(Appstate *state);


void center_text(SDLite_Text *text, int y);
void update_score(Score *player_score, int new_score);
void update_multiplier(Appstate *state);



