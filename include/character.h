#ifndef CHARACTER_H
#define CHARACTER_H

#define MAX_NAME_LEN 50
#define MAX_CLASS_LEN 20

typedef struct {
    char name[MAX_NAME_LEN];
    char class_name[MAX_CLASS_LEN];

    // Atributos Numéricos
    int health;
    int sorte;
    int defesa;
    int attack;
    int forca;
    int level;
    int ouro;
} Character;

Character* create_character();
void display_character_stats(const Character *c);
void free_character(Character *c);

#endif // CHARACTER_H