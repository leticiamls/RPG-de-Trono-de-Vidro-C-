#ifndef MINIGAME_H
#define MINIGAME_H

#include "character.h"
#include "data_structures.h"

// Constantes para tipos de carta
#define CYN "\e[0;36m"
#define PADRAO "\x1b[0m"
#define COR_VERMELHA "\033[31m"
#define COR_VERDE "\033[32m"
#define NEGRITO "\033[1m"

// --- Estrutura da Runa (Carta) ---
typedef struct runa {
    char simbolo[20];
    int ativada;
    struct runa *prox;
} Runa;

// --- Estrutura para o Inventário de Conhecimento ---
typedef struct conhecimento {
    char nome[50];
    int adquirido;
    struct conhecimento *prox;
} Conhecimento;


// --- Protótipos das Funções de Lista (Runas) ---
Runa* criar_runa(const char *simbolo);
Runa* anexar_runa(Runa *head, Runa *nova);
Runa* criar_baralho_runas();
void liberar_baralho(Runa *head);

// --- Protótipos das Funções de Lógica (Blackjack) ---
int calcular_valor_runa(const Runa *runa);
int calcular_pontuacao(const Runa *head);
Runa* distribuir_carta(Runa **baralho);
void imprimir_mao(const char *nome, const Runa *mao, int ocultar_primeira, int pontuacao_revelada);
int jogar_rodada(Runa **baralho, int num_rodada, int *vitorias_celaena, int *vitorias_npc);

// --- Protótipos das Funções de Inventário ---
Conhecimento* criar_conhecimento(const char *nome);
Conhecimento* adicionar_ao_inventario(Conhecimento *head, const char *nome_conhecimento);
void liberar_inventario(Conhecimento *head);
void imprimir_inventario(const Conhecimento *head);


// --- Função Principal do Jogo ---
void blackjack();

#endif // MINIGAME_H