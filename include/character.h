#ifndef CHARACTER_H
#define CHARACTER_H

#include "inventario.h"

#define MAX_NAME_LEN 50
#define MAX_CLASS_LEN 20

typedef struct {
    char name[MAX_NAME_LEN];
    char class_name[MAX_CLASS_LEN];

    // Atributos Numéricos
    int health;
    int max_health;
    int sorte;
    int defesa;
    int attack;
    int forca;
    int level;
    int ouro;
    Inventory inventory;
} Character;

Character* create_character();
Character* create_enemy(char* name, int hp, int atk, int def);
void display_character_stats(const Character *c);
void free_character(Character *c);

#endif // CHARACTER_H