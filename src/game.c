#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game.h"
#include "../include/character.h"
#include "../include/data_structures.h"
#include "../include/file_handler.h"
#include "../include/game_logic.h"
#include "../include/npc.h"
#include "../include/combate.h"


// Variáveis globais (simplificação para o projeto)
Character *g_player = NULL;
Queue *g_progression_queue = NULL;
Runa *g_minigame_deck = NULL;

//NPCs
NPC *g_chaol = NULL;
NPC *g_dorian = NULL;
NPC *g_nehemia = NULL;

// Protótipos de funções internas
static void load_or_new_game();
static void setup_progression_queue();
static void initialize_npcs() {
    // ATRIBUTOS BASE DE CADA NPC

    // Chaol: Baixa amizade inicial (20), mas Alto Poder/Status (50)
    g_chaol = create_npc("Chaol Westfall", 20, 50); 
    
    // Dorian: Amizade neutra/alta (40), Alto Poder/Status (70)
    g_dorian = create_npc("Dorian Havilliard", 40, 70); 
    
    // Nehemia: Amizade alta (70), Empatia/Confiança alta (60)
    g_nehemia = create_npc("Nehemia Ytger", 70, 60); 

    // ... (verificação de erro) ...
}

int initialize_game() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    initialize_npcs();
    // 1. Carregar ou iniciar novo jogo
    load_or_new_game();

    // 2. Configurar a fila de progressão
    setup_progression_queue();

    // 3. Configurar o baralho do mini-game
    g_minigame_deck = criar_baralho_runas();
    return 0;
}

static void load_or_new_game() {
    int choice = 0;
    printf("Deseja carregar um jogo salvo (1) ou iniciar um novo jogo (2)? ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        choice = 2;
    }

    if (choice == 1) {
        g_player = load_game();
        if (g_player == NULL) {
            printf("Nenhum jogo salvo encontrado. Iniciando novo jogo...\n");
            choice = 2;
        } else {
            printf("Jogo carregado com sucesso!\n");
        }
    }

    if (choice == 2 || g_player == NULL) { 
        printf("Iniciando novo jogo (Celaena Sardothien)...\n");
        g_player = create_character();
        if (g_player == NULL) {
            fprintf(stderr, "Erro critico: Falha ao criar personagem.\n");
            exit(1);
        }
    }
}

static void setup_progression_queue() {
    g_progression_queue = create_queue();
    
    // Fila de eventos baseada na narrativa de Trono de Vidro (simplificada)
    enqueue_chapter(g_progression_queue, "Minas de Endovier", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "O Castelo de Vidro", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "Treinamento para o Campeonato", 3); //Treinamento
    enqueue_chapter(g_progression_queue, "Mortes Repentinas", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "Revelacoes de Elena", 2); // Mini-Game
    enqueue_chapter(g_progression_queue, "Ameaca de Ridderak", 1); // Combate
    enqueue_chapter(g_progression_queue, "The Last Dance", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "Confronto Final", 1); // Combate
}

void run_game_loop() {
    Chapter *current_chapter;
    int choice;

    while (!is_queue_empty(g_progression_queue)) {
        current_chapter = dequeue_chapter(g_progression_queue);
        
        printf("\n--- Capitulo: %s ---\n", current_chapter->title);

    switch (current_chapter->type) {
        case 0: // Narrativa
            handle_narrative(current_chapter->title, g_player);
            break;
        case 1: // Combate
            handle_combat(g_player);
            break;
        case 2: // Mini-Game
            handle_minigame(g_player, g_minigame_deck);
            break;
        case 3: // Treinamento
            handle_training(g_player);
            break;
        default:
            printf("Tipo de capitulo desconhecido.\n");
            break;
    }
        // Salvar o jogo após cada capítulo
        save_game(g_player);
        
        // Pergunta ao jogador se deseja continuar
        if (!is_queue_empty(g_progression_queue)) {
            printf("\nCapitulo concluido. Deseja continuar (1) ou sair (2)? ");
            if (scanf("%d", &choice) != 1 || choice != 1) {
                printf("Saindo do jogo...\n");
                free(current_chapter);
                break;
            }
        }
        
        free(current_chapter);
    }
    
    if (is_queue_empty(g_progression_queue)) {
        printf("\nParabens! Você completou a historia de Trono de Vidro!\n");
    }
}

void cleanup_game() {
    if (g_player) free_character(g_player);
    if (g_progression_queue) free_queue(g_progression_queue);
    if (g_minigame_deck) liberar_baralho(g_minigame_deck);
    
    // Libera a memória alocada para os NPCs
    if (g_chaol) free(g_chaol);
    if (g_dorian) free(g_dorian);
    if (g_nehemia) free(g_nehemia);
}
