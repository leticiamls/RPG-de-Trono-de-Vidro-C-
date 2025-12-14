#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game_logic.h"
#include "../include/minigame.h"
#include "../include/character.h"
#include "../include/npc.h"
#include "../include/combate.h"
#include "../include/inventario.h"
#include "../include/narrativa.h"

// ================= Voids Itens =================

void narrativa_confronto_final(Character *player);
void narrativa_confronto_ridderak(Character *player);

void limpar_tela() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

void aplicar_magia_fae(Character *player) {
    if (player == NULL) return;

    const char *item_name = "MAGIA FAE: Poder Desbloqueado";
    const float MULT_ATAQUE = 0.30f;
    const float MULT_DEFESA = 0.15f;
    
    int bonus_ataque_pts = (int)(player->attack * MULT_ATAQUE);
    int bonus_defesa_pts = (int)(player->defesa * MULT_DEFESA);

    for (int i = 0; i < player->inventory.count; i++) {
        Item *item = &player->inventory.items[i];
        
        if (strcmp(item->name, item_name) == 0) {
            if (item->quantity == 1) { 
                
                player->attack += bonus_ataque_pts;
                player->defesa += bonus_defesa_pts; 
                
                item->quantity = 0; 
                
                printf("\n\033[1;32m[DESPERTAR DE PODER FAE]\033[0m %s ativado! \n", item_name);
                printf("\033[1;32mStatus atual: ATK +%d (%d) | DEFESA +%d (%d)\033[0m\n", 
                       bonus_ataque_pts, player->attack, 
                       bonus_defesa_pts, player->defesa);
                return;
            }
            return; 
        }
    }
}

void handle_training(Character *player) {
    int choice;
    printf("\n=================================================\n");
    printf("========= TREINAMENTO PARA O CAMPEONATO =========\n");
    printf("=================================================\n");

    printf("**O Capitao da Guarda Real, Chaol Westfall, observa voce na arena de treinamento. Seus olhos nao demonstram emocao, mas a pressao de seu olhar e quase palpavel. Ele nao esta aqui para ser seu amigo, mas para garantir que voce esteja apta para a competicao do Rei.\n");

    printf("\n%sChaol:%s \"Celaena, a competicao nao perdoa fraquezas. Voce tem um tempo limitado. Escolha um foco. Onde esta sua maior necessidade?\n", COR_VERDE, PADRAO);

    printf("\nVoce sabe que cada escolha tera um custo. O foco total em uma area significa negligenciar as outras, mas o tempo e curto.\"\n");

    printf("\n** ESCOLHA SEU FOCO DE TREINAMENTO: **\n");
    printf("1. Treinar Arco e Flecha: Foco em Precisao e Sorte (+3 ataque | +5 sorte)\n");
    printf("2. Treinar Lutas Corporais: Foco em Bloqueios e Resistencia (+5 defesa | +3 forca)\n");
    printf("3. Treinar Luta de Espada: Foco em Golpes Fatais e Intimidacao (+5 ataque | +3 defesa)\n");
    printf("Sua escolha: ");
    
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
    }

    switch (choice) {
    case 1:
        player->attack += 3; 
        player->sorte += 5;
        printf("\n%s%sChaol:%s \"Bom. A melhor defesa e um ataque que nao pode ser parado.\"\n", NEGRITO, COR_VERDE, PADRAO);
        printf("Voce passa as horas seguintes praticando sequencias de tiro ao alvo com arco e flecha. Seu corpo doi, mas seu ataque esta mais afiado.\n");
        printf("Seu poder de ataque aumentou para %d. E sua sorte aumentou para %d\n", player->attack, player->sorte);
        break;
    case 2:
        player->defesa += 3; 
        player->forca += 5;
        printf("\n%s%sChaol:%s \"Lutas? Uma escolha sensata para quem nao confia em ninguem.\"\n", NEGRITO, COR_VERDE, PADRAO);
        printf("Voce passa o tempo treinando com sacos de pancada pesados e armaduras, aprendendo a absorver e desviar o impacto. Sua resistencia e notavel.\n");
        printf("Seu poder de defesa aumentou para %d e sua Forca para %d.\n", player->defesa, player->forca);
        break;
    case 3:
        player->attack += 3; 
        player->defesa += 5;
        printf("\n%s%sChaol:%s \"Treinar como usar uma espada pode te ajudar muito nos momentos que requerem agilidade.\"\n", NEGRITO, COR_VERDE, PADRAO);
        printf("Voce treina movimentos evasivos e a leitura rapida de intencoes. Seu instinto esta mais agucado.\n");
        printf("Seu poder de defesa aumentou para %d e sua forca para %d.\n", player->defesa, player->forca);
        break;
    default:
        printf("\nVoce hesita. Chaol apenas suspira e se afasta.\n");
        printf("\n%s%sChaol:%s \"Perdeu seu tempo, Assassina. A indecisão e a morte.\"\n", NEGRITO, COR_VERDE, PADRAO);
        printf("Voce nao ganha bonus.\n");
        break;
}
    
    display_character_stats(player);
}

void handle_combat(Character *player) {
    printf("\n[COMBATE] Um desafio se apresenta!\n");
    
    // ========= Definição e criação do inimigo ==========
    
    char *enemy_name;
    int enemy_health;
    int enemy_max_health;
    int enemy_attack;
    int enemy_defense;

    if (player->level == 1) { 
    enemy_name = "Ridderak";
    enemy_health = 60 + (rand() % 20); 
    enemy_attack = 10 + (rand() % 5);
    enemy_defense = 5 + (rand() % 3);
    enemy_max_health = enemy_health;

} else { 
    enemy_name = "Cain";
    enemy_health = 70 + (rand() % 30);
    enemy_attack = 12 + (rand() % 5);
    enemy_defense = 6 + (rand() % 3);
    enemy_max_health = enemy_health;

    aplicar_magia_fae(player); 
}

    if (strcmp(enemy_name, "Cain") == 0 || strcmp(enemy_name, "Confronto Final") == 0) {
        narrativa_confronto_final(player);
        aplicar_magia_fae(player); 
    } else {
        narrativa_confronto_ridderak(player);
    }

    Character *enemy = create_enemy(enemy_name, enemy_health, enemy_attack, enemy_defense, enemy_max_health);
    if (enemy == NULL) {
        fprintf(stderr, "Erro critico: Falha ao criar inimigo.\n");
        return;
    }
    
    int resultado_batalha;
    
    // --- 2. ORQUESTRAÇÃO DO COMBATE (Loop de Retry) ---
    do {
        player->health = player->health;
        enemy->health = enemy_health;
        
        printf("\nVoce enfrenta o(a) %s! Prepare-se.\n", enemy->name);

        resultado_batalha = iniciar_batalha(player, enemy); 
        
        if (resultado_batalha == 0) {
            // 0: Desistir (Fim de Jogo)
            free(enemy);
            exit(0);
        }
        
    } while (resultado_batalha == 2);
    
    // --- 3. PÓS-BATALHA (Recompensa) ---
    if (resultado_batalha == 1) {
        printf("\n[SUCESSO] O desafio foi vencido!\n");
    }
    free(enemy);
}

void handle_minigame(Character *player, Runa *runa) {
    printf("\n[MINI-GAME] Voce precisa vencer um jogo de cartas para obter informaçoes cruciais.\n");
    blackjack(player, runa);
}
