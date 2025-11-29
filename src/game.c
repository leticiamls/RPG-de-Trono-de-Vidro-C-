#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game.h"
#include "../include/character.h"
#include "../include/data_structures.h"
#include "../include/file_handler.h"
#include "../include/game_logic.h"

// Variáveis globais (simplificação para o projeto)
Character *g_player = NULL;
Queue *g_progression_queue = NULL;
Deck *g_minigame_deck = NULL;

// Protótipos de funções internas
static void setup_new_game();
static void load_or_new_game();
static void setup_progression_queue();

int initialize_game() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    // 1. Carregar ou iniciar novo jogo
    load_or_new_game();

    // 2. Configurar a fila de progressão
    setup_progression_queue();

    // 3. Configurar o baralho do mini-game
    g_minigame_deck = create_deck();
    // Adicionar cartas (Exemplo simples)
    add_card(g_minigame_deck, "Amuleto de Wyrd", 5);
    add_card(g_minigame_deck, "Chave de ferro", 3);
    add_card(g_minigame_deck, "Shadowfire", 7);
    add_card(g_minigame_deck, "Royal Decree", 1);
    
    return 0;
}

static void load_or_new_game() {
    int choice;
    printf("Deseja carregar um jogo salvo (1) ou iniciar um novo jogo (2)? ");
    if (scanf("%d", &choice) != 1) {
        // Limpa o buffer de entrada em caso de erro
        while (getchar() != '\n');
        choice = 2; // Assume novo jogo em caso de entrada inválida
    }
    
    if (choice == 1) {
        g_player = load_game();
        if (g_player == NULL) {
            printf("Nenhum jogo salvo encontrado. Iniciando novo jogo...\n");
            setup_new_game();
        } else {
            printf("Jogo carregado com sucesso!\n");
            display_character_stats(g_player);
        }
    } else {
        setup_new_game();
    }
}

static void setup_new_game() {
    char name[MAX_NAME_LENGTH];
    int class_choice;

    printf("\n--- Novo Jogo ---\n");
    printf("Digite o nome do seu personagem: ");
    if (scanf("%s", name) != 1) {
        strcpy(name, "Aelin");
    }

    printf("Escolha sua classe:\n");
    printf("1. Assassina (Foco em Ataque)\n");
    printf("2. Guerreiro (Foco em Defesa)\n");
    printf("Escolha (1 ou 2): ");
    if (scanf("%d", &class_choice) != 1 || (class_choice != 1 && class_choice != 2)) {
        class_choice = 1; // Padrão para Assassina
    }

    if (class_choice == 1) {
        g_player = create_character(name, "Assassina");
        g_player->attack += 5; // Bônus de classe
    } else {
        g_player = create_character(name, "Guerreiro");
        g_player->defense += 5; // Bônus de classe
    }
    
    printf("\nPersonagem criado:\n");
    display_character_stats(g_player);
}

static void setup_progression_queue() {
    g_progression_queue = create_queue();
    
    // Fila de eventos baseada na narrativa de Trono de Vidro (simplificada)
    enqueue_chapter(g_progression_queue, "O Castelo de Vidro", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "O Desafio do Campeao", 1); // Combate
    enqueue_chapter(g_progression_queue, "O Encontro com a Rainha", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "Celaena vs. Nehemia", 2); // Mini-Game
    enqueue_chapter(g_progression_queue, "A Revelação da Identidade", 0); // Narrativa
    enqueue_chapter(g_progression_queue, "Confronto Final", 1); // Combate
}

void run_game_loop() {
    Chapter *current_chapter;
    int choice;

    while (!is_queue_empty(g_progression_queue)) {
        current_chapter = dequeue_chapter(g_progression_queue);
        
        printf("\n--- Capítulo: %s ---\n", current_chapter->title);
        
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
    if (g_minigame_deck) free_deck(g_minigame_deck);
}
