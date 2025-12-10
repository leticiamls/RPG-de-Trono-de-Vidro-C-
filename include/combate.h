// include/combate.h
#ifndef COMBATE_H
#define COMBATE_H

#include "character.h" // Necessário para definir o tipo Character*

// ====================== CONSTANTES DE AÇÃO ============================
#define LEVE 1
#define PESADO 2
#define DEFENDER 3
#define ESQUIVAR 4

// ====================== STRUCT QUEUE (Fila de Turnos) ============================

// Definição da struct Node (O que estava faltando no seu processo de modularização)
typedef struct Node {
    int action;
    Character* ref; // Referência ao personagem (Jogador ou Inimigo)
    struct Node* next;
} Node;

// Definição da struct Queue (O cabeçalho da fila)
typedef struct {
    Node* front;
    Node* rear;
} QueueCombate;

// ====================== PROTÓTIPOS ============================

// Funções de Gerenciamento da Fila de Combate (Renomeadas para evitar conflito)
void push_combate(QueueCombate* q, Character* p, int action);
Node* pop_combate(QueueCombate* q);
void free_queue_combate(QueueCombate* q);
int calcularDano(int base, float mult);

// Função principal
int iniciar_batalha(Character* player, Character* enemy);

#endif // COMBATE_H