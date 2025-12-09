#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game_logic.h"
#include "../include/minigame.h"

// --- Lógica do Jogo ---

void handle_narrative(const char *title, Character *player) {
    printf("\n[NARRATIVA] Voce esta em %s.\n", title);
    
    if (strcmp(title, "O Castelo de Vidro") == 0) {
        printf("Voce, a assassina mais temida de Adarlan, foi trazida da prisao nas minas de sal ao Castelo de Vidro para competir pelo titulo de Campea do Rei.\n");
        printf("Seu objetivo e sobreviver aos desafios, descobrir os segredos sombrios do castelo e finalmente se tornar assassina do rei, se livrando do seu fatidico destino nas minas de sal.\n");
    } else if (strcmp(title, "O Encontro com a Rainha") == 0) {
        printf("A Rainha de Adarlan convoca voce. Ela parece saber mais sobre voce do que voce gostaria.\n");
        printf("Você ganha 10 pontos de vida por sua lealdade (temporaria).\n");
        player->health += 10;
    } else if (strcmp(title, "A Revelaçao da Identidade") == 0) {
        printf("Seu verdadeiro nome e poder sao revelados. Voce sente uma nova força.\n");
        player->attack += 5;
        player->level++;
        printf("Seu ataque aumentou para %d e voce subiu para o Nivel %d!\n", player->attack, player->level);
    } else {
        printf("Um momento de reflexão e dialogo. O caminho a frente e incerto.\n");
    }
    
    display_character_stats(player);
}

void handle_training(Character *player) {
    int choice;
    printf("\n==================================================\n");
    printf("== TREINAMENTO: O OLHAR VIGILANTE DE CHAOL WESTFALL ==\n");
    printf("==================================================\n");

    printf("O Capitão da Guarda Real, Chaol Westfall, observa você na arena de treinamento. Seus olhos não demonstram emoção, mas a pressão de seu olhar é quase palpável. Ele não está aqui para ser seu amigo, mas para garantir que você esteja apta para a competição do Rei.\n");

    printf("\n\"Assassina,\" ele diz, a voz grave ecoando no silêncio da arena. \"A competição não perdoa fraquezas. Você tem um tempo limitado. Escolha um foco. Onde está sua maior necessidade?\"\n");

    printf("\nVocê sabe que cada escolha terá um custo. O foco total em uma área significa negligenciar as outras, mas o tempo é curto.\n");

    printf("\n** ESCOLHA SEU FOCO DE TREINAMENTO: **\n");
    printf("1. Treino de Ataque: Foco em Golpes Fatais e Intimidação (Aumenta o poder de Ataque)\n");
    printf("2. Treino de Defesa: Foco em Bloqueios e Resistência (Aumenta o poder de Defesa)\n");
    printf("3. Treino de Agilidade: Foco em Esquiva e Sorte (Aumenta a Sorte/Esquiva)\n");
    printf("Sua escolha: ");
    
    if (scanf("%d", &choice) != 1) {
        // Lidar com entrada inválida
        while (getchar() != '\n');
        choice = 1; // Padrão para Ataque
    }

    switch (choice) {
    case 1:
        player->attack += 3;
        printf("\nChaol acena com a cabeça. \"Bom. A melhor defesa é um ataque que não pode ser parado.\" Você passa as horas seguintes praticando sequências de golpes com força total. Seu corpo dói, mas seu ataque está mais afiado.\n");
        printf("Seu poder de ataque aumentou para %d.\n", player->attack);
        break;
    case 2:
        player->defense += 3;
        printf("\n\"Defesa? Uma escolha sensata para quem não confia em ninguém,\" Chaol murmura. Você passa o tempo treinando com escudos pesados e armaduras, aprendendo a absorver e desviar o impacto. Sua resistência é notável.\n");
        printf("Seu poder de defesa aumentou para %d.\n", player->defense);
        break;
    case 3:
        player->sorte += 3;
        printf("\nChaol franze a testa. \"Sorte? Não confio nela. Mas a agilidade pode salvar sua vida.\" Você treina movimentos evasivos e a leitura rápida de intenções. Seu instinto está mais aguçado.\n");
        printf("Seu atributo Sorte/Esquiva aumentou para %d.\n", player->sorte);
        break;
    default:
        printf("\nVocê hesita. Chaol apenas suspira e se afasta. \"Perdeu seu tempo, Assassina. A indecisão é a morte.\" Você não ganha bônus.\n");
        break;
}
    
    display_character_stats(player);
}

void handle_combat(Character *player) {
    printf("\n[COMBATE] Um desafio se apresenta!\n");
    
    // Inimigo simples (exemplo)
    char enemy_name[50];
    int enemy_health = 50 + (rand() % 20);
    int enemy_attack = 8 + (rand() % 5);
    int enemy_defense = 3 + (rand() % 3);     
    if (strcmp(player->class_name, "Assassina") == 0) {
        strcpy(enemy_name, "Guarda Real");
    } else {
        strcpy(enemy_name, "Criatura de Wyrd");
    }
    
    printf("Voce enfrenta um(a) %s (Vida: %d, Ataque: %d, Defesa: %d).\n", enemy_name, enemy_health, enemy_attack, enemy_defense);
    
    while (player->health > 0 && enemy_health > 0) {
        int player_damage = player->attack - enemy_defense;
        if (player_damage < 1) player_damage = 1;
        
        int enemy_damage = enemy_attack - player->defense;
        if (enemy_damage < 1) enemy_damage = 1;
        
        // Turno do Jogador
        enemy_health -= player_damage;
        printf("Voce ataca! %s perde %d de vida. (Restante: %d)\n", enemy_name, player_damage, enemy_health > 0 ? enemy_health : 0);
        
        if (enemy_health <= 0) {
            printf("Voce derrotou o(a) %s!\n", enemy_name);
            player->health += 10; // Recompensa
            printf("Voce recupera 10 de vida. Vida atual: %d\n", player->health);
            return;
        }
        
        // Turno do Inimigo
        player->health -= enemy_damage;
        printf("%s ataca! Voce perde %d de vida. (Restante: %d)\n", enemy_name, enemy_damage, player->health > 0 ? player->health : 0);
        
        if (player->health <= 0) {
            printf("Voce foi derrotado(a) por %s. Fim de Jogo.\n", enemy_name);
            exit(0); // Fim de jogo
        }
    }
}

void handle_minigame(Character *player, Runa *runa) {
    printf("\n[MINI-GAME] Voce precisa vencer um jogo de cartas para obter informaçoes cruciais.\n");
    blackjack(player, runa);
}
