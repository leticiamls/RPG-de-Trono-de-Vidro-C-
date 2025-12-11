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


// ========== Variáveis globais ==========
Character *g_player = NULL;
Character *g_enemy = NULL;
Queue *g_progression_queue = NULL;
Runa *g_minigame_deck = NULL;

// ========== NPCs ==========
NPC *g_chaol = NULL;
NPC *g_dorian = NULL;
NPC *g_nehemia = NULL;

static void load_or_new_game();

static void setup_progression_queue();

static void initialize_npcs() {
    g_chaol = create_npc("Chaol Westfall", 20, 50); 
    g_dorian = create_npc("Dorian Havilliard", 40, 70);
    g_nehemia = create_npc("Nehemia Ytger", 70, 60); 

    // ... (verificação de erro) ...
}

int initialize_game() {
    srand(time(NULL));

    initialize_npcs();

    load_or_new_game();

    setup_progression_queue();

    g_minigame_deck = criar_baralho_runas();

    return 0;
}

static void load_or_new_game() {
    int choice = 0;
    printf("%s%sDeseja carregar um jogo salvo (1) ou iniciar um novo jogo (2)?%s ", NEGRITO, COR_VERDE, PADRAO);
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        choice = 2;
    }

    if (choice == 1) {
        g_player = load_game();
        if (g_player == NULL) {
            printf("%s%sNenhum jogo salvo encontrado. Iniciando novo jogo...%s\n", NEGRITO, COR_VERDE, PADRAO);
            choice = 2;
        } else {
            printf("Jogo carregado com sucesso!\n", NEGRITO, COR_VERDE, PADRAO);
        }
    }

    if (choice == 2 || g_player == NULL) { 
        printf("%s%sIniciando novo jogo (Celaena Sardothien)...%s\n", NEGRITO, COR_VERDE, PADRAO);
        g_player = create_character();
        if (g_player == NULL) {
            fprintf(stderr, "%s%sErro critico: Falha ao criar personagem.%s\n", NEGRITO, COR_VERMELHA, PADRAO);
            exit(1);
        }
    }
}

static void setup_progression_queue() {
    g_progression_queue = create_queue();
    
    // Fila de eventos baseada na narrativa de Trono de Vidro (simplificada)
    enqueue_chapter(g_progression_queue, "Minas de Endovier", 0); // Narrativa 1
    enqueue_chapter(g_progression_queue, "O Castelo de Vidro", 0); // Narrativa 2
    enqueue_chapter(g_progression_queue, "Treinamento para o Campeonato", 3); //Treinamento
    enqueue_chapter(g_progression_queue, "Mortes Repentinas", 0); // Narrativa 3
    enqueue_chapter(g_progression_queue, "Revelacoes de Elena", 2); // Mini-Game
    enqueue_chapter(g_progression_queue, "Ameaca de Ridderak", 1); // Combate
    enqueue_chapter(g_progression_queue, "The Last Dance", 0); // Narrativa 4
    enqueue_chapter(g_progression_queue, "Confronto Final", 1); // Combate
}

void run_game_loop() {
    Chapter *current_chapter;
    int choice;

    while (!is_queue_empty(g_progression_queue)) {
        current_chapter = dequeue_chapter(g_progression_queue);
        
        printf("\n%s=== Capitulo: %s ===%s\n", NEGRITO, current_chapter->title, PADRAO);

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
            printf("\n%s%sCapitulo concluido. Deseja continuar (1) ou sair (2)?%s ", NEGRITO, COR_VERDE, PADRAO);
            if (scanf("%d", &choice) != 1 || choice != 1) {
                printf("Saindo do jogo...\n");
                free(current_chapter);
                break;
            }
        }
        
        free(current_chapter);
    }
    
    if (is_queue_empty(g_progression_queue)) {
        printf("\n%s%sParabens! Voce completou a historia de Trono de Vidro!%s\n", NEGRITO, COR_VERDE, PADRAO);
    }
}

void cleanup_game() {
    if (g_player) free_character(g_player);
    if (g_progression_queue) free_queue(g_progression_queue);
    if (g_minigame_deck) liberar_baralho(g_minigame_deck);
    
    if (g_chaol) free(g_chaol);
    if (g_dorian) free(g_dorian);
    if (g_nehemia) free(g_nehemia);
}