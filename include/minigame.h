#ifndef MINIGAME_H
#define MINIGAME_H

#include "character.h"
#include "data_structures.h"
#include "inventario.h"

// ========== Cores ===========
#define CYN "\e[0;36m"
#define PADRAO "\x1b[0m"
#define COR_VERMELHA "\033[31m"
#define COR_VERDE "\033[32m"
#define NEGRITO "\033[1m"

// ========== Protótipos das Funções de Lógica ==========
int calcular_valor_runa(const Runa *runa);
int calcular_pontuacao(const Runa *head);
Runa* distribuir_carta(Runa **baralho);
void imprimir_mao(const char *nome, const Runa *mao, int ocultar_primeira, int pontuacao_revelada);
int jogar_rodada(Runa **baralho, int num_rodada, int *vitorias_celaena, int *vitorias_npc);

void blackjack();

#endif