#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "character.h"

#define SAVE_FILE "savegame.dat"
#define CONFIG_FILE "config.txt"

int save_game(const Character *player);
Character* load_game();
int save_config(int volume, int difficulty);
int load_config(int *volume, int *difficulty);

#endif
