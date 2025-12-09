#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/npc.h"

// Implementação da função create_npc
// Aloca memória para um novo NPC e inicializa seus atributos de relacionamento e combate.
NPC* create_npc(const char *name, int amizade_base, int empatia_base) {
    // 1. Aloca memória para a nova estrutura NPC
    NPC *new_npc = (NPC *)malloc(sizeof(NPC));
    
    // Verifica se a alocação de memória falhou
    if (new_npc == NULL) {
        perror("Erro ao alocar memoria para o NPC");
        return NULL;
    }
    
    // 2. Inicializa os campos de string
    
    // Copia o nome, garantindo que nao exceda o buffer (MAX_NPC_NAME_LEN)
    strncpy(new_npc->name, name, MAX_NPC_NAME_LEN - 1);
    new_npc->name[MAX_NPC_NAME_LEN - 1] = '\0';
    
    // 3. Inicializa os atributos de Relacionamento/Status
    new_npc->amizade_score = amizade_base;
    new_npc->empatia_poder = empatia_base;
    
    // 4. Inicializa os atributos de Combate (Valores base, podem ser ajustados por NPC)
    new_npc->health = 100; // Valor padrao para NPCs
    new_npc->attack = 10;  // Valor padrao para NPCs
    
    return new_npc;
}

// Certifique-se de que os ponteiros globais e as cores estão acessíveis
// (ex: extern NPC *g_chaol; e #define PADRAO "\033[0m")

void display_npc_stats() {
    printf("\n%s--- Status de Relacionamento ---%s\n", COR_LARANJA, PADRAO);
    
    // Verificação de inicialização básica (idealmente, eles são inicializados em initialize_game)
    if (g_chaol == NULL || g_dorian == NULL || g_nehemia == NULL) {
        printf("Ainda nao houve interacao com os personagens chave.\n");
        printf("----------------------------------\n");
        return;
    }

    // Exibindo os atributos corretamente através dos ponteiros globais
    printf("Chaol Westfall (Amizade): \t%d/100\n", g_chaol->amizade_score);
    printf("Dorian Havilliard (Empatia): \t%d/100\n", g_dorian->empatia_poder);
    // Para Nehemia, você pode escolher mostrar Amizade ou Empatia, dependendo do foco narrativo
    printf("Nehemia Ytger (Amizade): \t%d/100\n", g_nehemia->amizade_score);
    
    printf("%s----------------------------------%s\n",  COR_LARANJA, PADRAO);
}