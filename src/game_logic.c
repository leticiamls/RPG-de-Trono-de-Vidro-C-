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

// --- Lógica do Jogo ---
void aplicar_magia_fae(Character *player) {
    if (player == NULL) return;

    const char *item_name = "MAGIA FAE: Poder Desbloqueado";
    const float MULT_ATAQUE = 0.30f;
    const float MULT_DEFESA = 0.15f;
    
    // Cálculo dos bônus em pontos inteiros
    int bonus_ataque_pts = (int)(player->attack * MULT_ATAQUE);
    int bonus_defesa_pts = (int)(player->defesa * MULT_DEFESA); // Usando player->defesa para calcular

    for (int i = 0; i < player->inventory.count; i++) {
        Item *item = &player->inventory.items[i];
        
        if (strcmp(item->name, item_name) == 0) {
            if (item->quantity == 1) { 
                
                // APLICAÇÃO CORRIGIDA
                player->attack += bonus_ataque_pts;
                player->defesa += bonus_defesa_pts; // <-- Aplicando à DEFESA, como pretendido (15%)
                
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

void aplicar_amuleto_ferro(Character *player, Character *enemy) {
    if (player == NULL || enemy == NULL) return;

    const char *item_name = "AMULETO: anulador de magia(voce bloqueara a magia inimiga, mas nao sera capaz de utilizar a sua)";
    const float reducao_ataque_inimigo = 0.30f;
    int amuleto_encontrado = 0;

    // 1. Verificar se o Amuleto de Ferro está no inventario do jogador
    for (int i = 0; i < player->inventory.count; i++) {
        Item *item = &player->inventory.items[i];
        
        // Verifica se o Amuleto está presente e se a quantidade é maior que zero
        if (strcmp(item->name, item_name) == 0 && item->quantity > 0) {
            amuleto_encontrado = 1;
            break; 
        }
    }

    if (amuleto_encontrado) {
        // 2. Aplicar a penalidade de 30% no ataque do inimigo
        int dano_original = enemy->attack;
        
        // Calcula a nova penalidade, garantindo que o ataque minimo seja 1 (ou 0, dependendo da regra do jogo)
        int reducao = (int)(dano_original * reducao_ataque_inimigo);
        enemy->attack = dano_original - reducao;
        
        // Garante que o ataque nao fique negativo, se a logica permitir
        if (enemy->attack < 0) {
            enemy->attack = 0; 
        }

        printf("\n\033[1;36m[AMULETO DE FERRO ATIVO]\033[0m A presenca do ferro afeta o inimigo!");
        printf("\nO ataque de %s foi reduzido em %d (30%%). ATK Inimigo atual: %d\n", 
               enemy->name, reducao, enemy->attack);

        // Nao há necessidade de uma flag de "uso" no Amuleto, pois ele é um item passivo/permanente.
    }
}

void handle_training(Character *player) {
    int choice;
    printf("\n=================================================\n");
    printf("========= TREINAMENTO PARA O CAMPEONATO =========\n");
    printf("=================================================\n");

    printf("**O Capitao da Guarda Real, Chaol Westfall, observa voce na arena de treinamento. Seus olhos nao demonstram emocao, mas a pressao de seu olhar e quase palpavel. Ele nao esta aqui para ser seu amigo, mas para garantir que voce esteja apta para a competicao do Rei.\n");

    printf("\n%sChaol:%s 'Celaena,' ele diz, a voz grave ecoando no silencio da arena. 'A competicao nao perdoa fraquezas. Voce tem um tempo limitado. Escolha um foco. Onde esta sua maior necessidade?'\n", CYN, PADRAO);

    printf("\n'Voce sabe que cada escolha tera um custo. O foco total em uma area significa negligenciar as outras, mas o tempo e curto.'\n");

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
        printf("\nChaol acena com a cabeça. \"Bom. A melhor defesa é um ataque que não pode ser parado.\" Você passa as horas seguintes praticando sequências de golpes com força total. Seu corpo dói, mas seu ataque está mais afiado.\n");
        printf("Seu poder de ataque aumentou para %d. E sua sorte aumentou para %d\n", player->attack, player->sorte);
        break;
    case 2:
        player->defesa += 3; 
        player->forca += 5;
        printf("\n\"Defesa? Uma escolha sensata para quem não confia em ninguém,\" Chaol murmura. Você passa o tempo treinando com escudos pesados e armaduras, aprendendo a absorver e desviar o impacto. Sua resistência é notável.\n");
        printf("Seu poder de defesa aumentou para %d e sua Força para %d.\n", player->defesa, player->forca);
        break;
    case 3:
        player->attack += 3; 
        player->defesa += 5;
        printf("\nChaol franze a testa. \"Sorte? Não confio nela. Mas a agilidade pode salvar sua vida.\" Você treina movimentos evasivos e a leitura rápida de intenções. Seu instinto está mais aguçado.\n");
        printf("Seu poder de defesa aumentou para %d e sua força para %d.\n", player->defesa, player->forca);
        break;
    default:
        printf("\nVocê hesita. Chaol apenas suspira e se afasta. \"Perdeu seu tempo, Assassina. A indecisão é a morte.\" Você não ganha bônus.\n");
        break;
}
    
    display_character_stats(player);
}

extern void aplicar_magia_fae(Character *player);

void handle_combat(Character *player) {
    printf("\n[COMBATE] Um desafio se apresenta!\n");
    
    // --- 1. DEFINIÇÃO E CRIAÇÃO DO INIMIGO ---
    
    char *enemy_name;
    int enemy_health;
    int enemy_max_health;
    int enemy_attack;
    int enemy_defense;
    

    // Lógica básica para definir o inimigo (usando os stats antigos como base)
    if (strcmp(player->class_name, "Assassina") == 0) {
        enemy_name = "Ridderak";
        enemy_health = 60 + (rand() % 20); // Stats aleatórios
        enemy_attack = 10 + (rand() % 5);
        enemy_defense = 5 + (rand() % 3);
        enemy_max_health = enemy_health;
    } else {
        enemy_name = "Cain";
        enemy_health = 70 + (rand() % 30);
        enemy_attack = 12 + (rand() % 5);
        enemy_defense = 6 + (rand() % 3);
        enemy_max_health = enemy_health;
    }

    

    // --- PONTO DE APLICAÇÃO DO BÔNUS ---
    if (strcmp(enemy_name, "Cain") == 0 || strcmp(enemy_name, "Confronto Final") == 0) {
        // Checa e aplica o bônus antes de criar o inimigo final
        aplicar_magia_fae(player); 
    }

    // Cria o inimigo usando a função externa
    Character *enemy = create_enemy(enemy_name, enemy_health, enemy_attack, enemy_defense, enemy_max_health);
    if (enemy == NULL) {
        fprintf(stderr, "Erro critico: Falha ao criar inimigo.\n");
        return;
    }
    
    aplicar_amuleto_ferro(player, enemy);
    int resultado_batalha;
    
    // --- 2. ORQUESTRAÇÃO DO COMBATE (Loop de Retry) ---
    do {
        // Restaura o HP do jogador para o valor inicial antes de CADA TENTATIVA
        // (Nota: Em um RPG, você deve usar uma variável para o HP Máximo)
        player->health = player->health; // Mantém a vida atual
        enemy->health = enemy_health;    // Restaura o HP do inimigo para o máximo
        
        printf("\nVoce enfrenta o(a) %s! Prepare-se.\n", enemy->name);

        // Chama a lógica de combate completa (implementada em src/combate.c)
        resultado_batalha = iniciar_batalha(player, enemy); 
        
        if (resultado_batalha == 0) {
            // Resultado 0: Desistir (Fim de Jogo)
            free(enemy);
            exit(0);
        }
        
    } while (resultado_batalha == 2); // Resultado 2: Tentar Novamente (Retry)
    
    // --- 3. PÓS-BATALHA (Recompensa) ---
    if (resultado_batalha == 1) {
        printf("\n[SUCESSO] O desafio foi vencido!\n");
        player->health += 10;
        printf("Você recupera 10 de vida. Vida atual: %d\n", player->health);
    }
    
    // Libera a memória alocada para o inimigo temporário
    free(enemy);
}

void handle_minigame(Character *player, Runa *runa) {
    printf("\n[MINI-GAME] Voce precisa vencer um jogo de cartas para obter informaçoes cruciais.\n");
    blackjack(player, runa);
}
