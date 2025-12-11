#ifndef COMBATE_H
#define COMBATE_H

#include "character.h"

// ====================== CONSTANTES DE AÇÃO ============================
#define LEVE 1
#define PESADO 2
#define DEFENDER 3
#define ESQUIVAR 4

// ====================== STRUCT QUEUE (Fila de Turnos) ============================
typedef struct Node {
    int action;
    Character* ref;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} QueueCombate;

// ====================== PROTÓTIPOS ============================
void push_combate(QueueCombate* q, Character* p, int action);
Node* pop_combate(QueueCombate* q);
void free_queue_combate(QueueCombate* q);
int calcularDano(int base, float mult);

int iniciar_batalha(Character* player, Character* enemy);

#endif 