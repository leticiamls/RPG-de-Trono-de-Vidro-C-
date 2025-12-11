#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define CHAPTER_TYPE_TRAINING 3

// =============== Cores ===============
#define CYN "\e[0;36m"
#define PADRAO "\x1b[0m"
#define COR_VERMELHA "\033[31m"
#define COR_VERDE "\033[32m"
#define COR_AZUL "\033[0;34m"
#define NEGRITO "\033[1m"
#define COR_MAGENTA "\033[0;35m"
#define COR_LARANJA "\033[0;33m"

// ===== Lista Encadeada Baralho ========
typedef struct runa {
    char simbolo[20];
    int ativada;
    struct runa *prox;
} Runa;

Runa* criar_runa(const char *simbolo);
Runa* anexar_runa(Runa *head, Runa *nova);
Runa* criar_baralho_runas();
void liberar_baralho(Runa *head);

// ============== Filas =================
typedef struct Chapter {
    char title[100];
    int type; // 0: Narrativa, 1: Combate, 2: Mini-Game
    struct Chapter *next;
} Chapter;

typedef struct Queue {
    Chapter *front;
    Chapter *rear;
} Queue;

Queue* create_queue();
void enqueue_chapter(Queue *queue, const char *title, int type);
Chapter* dequeue_chapter(Queue *queue);
int is_queue_empty(Queue *queue);
void free_queue(Queue *queue);

#endif
