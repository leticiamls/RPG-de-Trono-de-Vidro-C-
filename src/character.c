#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/character.h"

Character* create_character(const char *name, const char *class_name) {
    Character *new_char = (Character *)malloc(sizeof(Character));
    if (new_char == NULL) {
        perror("Erro ao alocar memória para o personagem");
        return NULL;
    }

        char* newline = strchr(name, '\\');
    if (newline) *newline = '\0';
    strncpy(new_char->name, name, MAX_NAME_LENGTH - 1);
    new_char->name[MAX_NAME_LENGTH - 1] = '\0';
    
    strncpy(new_char->class_name, class_name, MAX_CLASS_LENGTH - 1);
    new_char->class_name[MAX_CLASS_LENGTH - 1] = '\0';

    // Atributos base
    new_char->health = 100;
    new_char->attack = 10;
    new_char->defense = 5;
    new_char->sorte = 10;// Valor inicial para defesa (mantendo a original)
    new_char->level = 1;
    new_char->ouro = 100;

    return new_char;
}

void display_character_stats(const Character *c) {
    if (c == NULL) {
        printf("Personagem não existe.\n");
        return;
    }
    printf("--- Status de %s ---\n", c->name);
    printf("Classe: %s\n", c->class_name);
    printf("Nível: %d\n", c->level);
    printf("Vida: %d\n", c->health);
    printf("Ataque: %d\n", c->attack);
    printf("Defesa: %d\n", c->defense);
    printf("Sorte: %d\n", c->sorte);
    printf("Ouro: %d\n", c->ouro);
    printf("----------------------\n");
}

void free_character(Character *c) {
    if (c != NULL) {
        free(c);
    }
}
