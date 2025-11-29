#ifndef CHARACTER_H
#define CHARACTER_H
#define MAX_NAME_LENGTH 50
#define MAX_CLASS_LENGTH 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    char class_name[MAX_CLASS_LENGTH];
    int health;
    int sorte; // Adicionado para o minigame
    int defesa; // Adicionado para o minigame
    int attack;
    int defense;
    int level;
    int ouro;
} Character;

// Funções do Personagem
Character* create_character(const char *name, const char *class_name);
void display_character_stats(const Character *c);
void free_character(Character *c);

#endif // CHARACTER_H
