#ifndef NPC_H
#define NPC_H

#define MAX_NPC_NAME_LEN 30

// 1. DEFINIÇÃO COMPLETA DA ESTRUTURA VEM PRIMEIRO
typedef struct {
    char name[MAX_NPC_NAME_LEN];
    int amizade_score;
    int empatia_poder; 
    int health;
    int attack;
} NPC;

// 2. PROTÓTIPOS E VARIÁVEIS EXTERNAS VÊM DEPOIS
NPC* create_npc(const char *name, int amizade_base, int empatia_base);

// 3. DECLARAÇÕES EXTERNAS (se você as moveu para cá)
// Se você está usando essas declarações, elas devem estar aqui.
extern NPC *g_chaol;
extern NPC *g_dorian; 
// ...
#endif // NPC_H