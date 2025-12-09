#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "character.h"
#include "data_structures.h"

// Funções de lógica do jogo
void handle_narrative(const char *title, Character *player);
void handle_combat(Character *player);
void handle_minigame(Character *player, Runa *runa);

#endif // GAME_LOGIC_H
