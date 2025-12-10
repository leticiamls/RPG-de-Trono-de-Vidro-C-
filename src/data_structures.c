#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_structures.h"

// --- Implementação da Lista Encadeada (Deck/Baralho) ---

Runa* criar_runa(const char *simbolo) {
    Runa *r = (Runa*) malloc(sizeof(Runa));
    if (r == NULL) {
        printf("Erro ao alocar memoria para runa.\n");
        exit(1);
    }
    strncpy(r->simbolo, simbolo, 19);
    r->simbolo[19] = '\0';
    r->ativada = 0;
    r->prox = NULL;
    return r;
}

Runa* anexar_runa(Runa *head, Runa *nova) {
    if (!head) return nova;
    Runa *aux = head;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = nova;
    return head;
}

Runa* criar_baralho_runas() {
    const char *runasBase[] = {"Luz", "Wryd", "Magia", "Trevas"};
    const char *figuras[] = {"Lamina", "Coroa", "Dragao"};
    char simbolo[20];
    Runa *head = NULL;

    // Cartas de 2 a 9
    for (int i = 0; i < 4; i++) {
        for (int v = 2; v <= 9; v++) { 
            snprintf(simbolo, sizeof(simbolo), "%s%d", runasBase[i], v);
            head = anexar_runa(head, criar_runa(simbolo));
        }
    }

    // Cartas de Figura (Valem 10)
    for (int i = 0; i < 4; i++) {
        for (int f = 0; f < 3; f++) {
            snprintf(simbolo, sizeof(simbolo), "%s-%s", runasBase[i], figuras[f]);
            head = anexar_runa(head, criar_runa(simbolo));
        }
    }
    
    // Cartas Ás/Aelino (Valem 1/11)
    for (int i = 0; i < 4; i++) {
        snprintf(simbolo, sizeof(simbolo), "%s-AELINO", runasBase[i]);
        head = anexar_runa(head, criar_runa(simbolo));
    }

    return head;
}

void liberar_baralho(Runa *head) {
    Runa *current = head;
    Runa *proximo;
    while (current) {
        proximo = current->prox;
        free(current);
        current = proximo;
    }
}

// --- Implementação da Fila (Queue/Progressão) ---

Queue* create_queue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL) {
        perror("Erro ao alocar memória para a fila");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue_chapter(Queue *queue, const char *title, int type) {
    Chapter *new_chapter = (Chapter *)malloc(sizeof(Chapter));
    if (new_chapter == NULL) {
        perror("Erro ao alocar memória para o capítulo");
        return;
    }
    
    strncpy(new_chapter->title, title, 99);
    new_chapter->title[99] = '\0';
    new_chapter->type = type;
    new_chapter->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = new_chapter;
        queue->rear = new_chapter;
    } else {
        queue->rear->next = new_chapter;
        queue->rear = new_chapter;
    }
}

Chapter* dequeue_chapter(Queue *queue) {
    if (queue == NULL || queue->front == NULL) {
        return NULL;
    }
    
    Chapter *dequeued_chapter = queue->front;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    return dequeued_chapter;
}

int is_queue_empty(Queue *queue) {
    return queue == NULL || queue->front == NULL;
}

void free_queue(Queue *queue) {
    if (queue == NULL) return;
    Chapter *current = queue->front;
    Chapter *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}
