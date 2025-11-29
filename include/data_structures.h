#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Definição da estrutura para o Baralho (Lista Encadeada)
typedef struct Card {
    char name[50];
    int valor;
    int type;
    struct Card *next;
} Card;

typedef struct Deck {
    Card *head;
    int size;
} Deck;

// Funções para Lista Encadeada (Baralho)
Deck* create_deck();
void add_card(Deck *deck, const char *name, int value);
Card* draw_card(Deck *deck);
void free_deck(Deck *deck);

// Definição da estrutura para a Progressão (Fila)
typedef struct Chapter {
    char title[100];
    int type; // 0: Narrativa, 1: Combate, 2: Mini-Game
    struct Chapter *next;
} Chapter;

typedef struct Queue {
    Chapter *front;
    Chapter *rear;
} Queue;

// Funções para Fila (Progressão)
Queue* create_queue();
void enqueue_chapter(Queue *queue, const char *title, int type);
Chapter* dequeue_chapter(Queue *queue);
int is_queue_empty(Queue *queue);
void free_queue(Queue *queue);

#endif // DATA_STRUCTURES_H
