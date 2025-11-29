#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_structures.h"

// --- Implementação da Lista Encadeada (Deck/Baralho) ---

Deck* create_deck() {
    Deck *deck = (Deck *)malloc(sizeof(Deck));
    if (deck == NULL) {
        perror("Erro ao alocar memória para o baralho");
        return NULL;
    }
    deck->head = NULL;
    deck->size = 0;
    return deck;
}

void add_card(Deck *deck, const char *name, int value) {
    Card *new_card = (Card *)malloc(sizeof(Card));
    if (new_card == NULL) {
        perror("Erro ao alocar memória para a carta");
        return;
    }
    
    strncpy(new_card->name, name, 49);
    new_card->name[49] = '\0';
    new_card->valor = value;
    
    // Adiciona no início da lista (simplificação)
    new_card->next = deck->head;
    deck->head = new_card;
    deck->size++;
}

Card* draw_card(Deck *deck) {
    if (deck == NULL || deck->head == NULL) {
        return NULL;
    }
    
    // Remove do início da lista (simplificação)
    Card *drawn_card = deck->head;
    deck->head = deck->head->next;
    deck->size--;
    drawn_card->next = NULL; // Garante que a carta removida não aponte para o resto da lista
    
    return drawn_card;
}

void free_deck(Deck *deck) {
    if (deck == NULL) return;
    Card *current = deck->head;
    Card *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(deck);
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
