#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/character.h"
#include "../include/data_structures.h"

Character* create_character() {
    Character *new_char = (Character *)malloc(sizeof(Character));
    if (new_char == NULL) {
        perror("Erro ao alocar memória para o personagem");
        return NULL;
    }

    strncpy(new_char->name, "Celaena Sardothien", MAX_NAME_LEN - 1);
    new_char->name[MAX_NAME_LEN - 1] = '\0';
    
    // Inicializa a classe: Assassina
    strncpy(new_char->class_name, "Assassina", MAX_CLASS_LEN - 1);
    new_char->class_name[MAX_CLASS_LEN - 1] = '\0';

    // Inicializa o inventario
    init_inventory(&new_char->inventory);

    // Atributos base
    new_char->health = 100;
    new_char->attack = 10;
    new_char->defesa = 5;
    new_char->forca = 5;
    new_char->sorte = 10;
    new_char->level = 1;
    new_char->ouro = 100;

    return new_char;
}

Character* create_enemy(char* name, int hp, int atk, int def) {
    Character *enemy = (Character *)malloc(sizeof(Character));
    if (!enemy) return NULL;
    strncpy(enemy->name, name, MAX_NAME_LEN - 1);
    enemy->name[MAX_NAME_LEN - 1] = '\0';
    strncpy(enemy->class_name, "Inimigo", MAX_CLASS_LEN - 1);
    
    enemy->health = hp;
    enemy->attack = atk;
    enemy->defesa = def;
    enemy->forca = 5;
    return enemy;
}

void display_character_stats(const Character *c) {
    if (c == NULL) {
        printf("Personagem não existe.\n");
        return;
    }
    printf("%s--- Status de Celaena ---%s\n", COR_LARANJA, PADRAO);
    printf("Nivel: %d\n", c->level);
    printf("Vida: %d\n", c->health);
    printf("Ataque: %d\n", c->attack);
    printf("Defesa: %d\n", c->defesa);
    printf("Forca: %d\n", c->forca);
    printf("Sorte: %d\n", c->sorte);
    printf("Ouro: %d\n", c->ouro);
    printf("%s----------------------%s\n", COR_LARANJA, PADRAO);
}

void free_character(Character *c) {
    if (c != NULL) {
        free(c);
    }
}
