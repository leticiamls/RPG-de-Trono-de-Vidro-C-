#ifndef MINIGAME_H
#define MINIGAME_H

#include "character.h"
#include "data_structures.h"

// Constantes para tipos de carta
#define CARD_TYPE_ATAQUE 1
#define CARD_TYPE_DEFESA 2
#define CARD_TYPE_SORTE 3

// Protótipo da função com o tipo corrigido
void comecarJogoCorte(Character *player, Deck *deck);

#endif // MINIGAME_H
