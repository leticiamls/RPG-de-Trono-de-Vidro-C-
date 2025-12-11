#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/npc.h"

NPC* create_npc(const char *name, int amizade_base, int empatia_base) {
    NPC *new_npc = (NPC *)malloc(sizeof(NPC));
    
    if (new_npc == NULL) {
        perror("Erro ao alocar memoria para o NPC");
        return NULL;
    }
    
    strncpy(new_npc->name, name, MAX_NPC_NAME_LEN - 1);
    new_npc->name[MAX_NPC_NAME_LEN - 1] = '\0';
    
    new_npc->amizade_score = amizade_base;
    new_npc->empatia_poder = empatia_base;
    
    new_npc->health = 100;
    new_npc->attack = 10;  
    
    return new_npc;
}


void display_npc_stats() {
    printf("\n%s--- Status de Relacionamento ---%s\n", COR_LARANJA, PADRAO);
    
    if (g_chaol == NULL || g_dorian == NULL || g_nehemia == NULL) {
        printf("Ainda nao houve interacao com os personagens chave.\n");
        printf("----------------------------------\n");
        return;
    }

    printf("Chaol Westfall (Amizade): \t%d/100\n", g_chaol->amizade_score);
    printf("Dorian Havilliard (Empatia): \t%d/100\n", g_dorian->empatia_poder);
    printf("Nehemia Ytger (Amizade): \t%d/100\n", g_nehemia->amizade_score);
    
    printf("%s----------------------------------%s\n",  COR_LARANJA, PADRAO);
}