#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game_logic.h"
#include "../include/minigame.h"

// --- Lógica do Jogo ---

void handle_narrative(const char *title, Character *player) {
    printf("\n[NARRATIVA] Você está em %s.\n", title);
    
    if (strcmp(title, "O Castelo de Vidro") == 0) {
        printf("Você, a assassina mais temida de Adarlan, foi trazida da prisão nas minas de sal ao Castelo de Vidro para competir pelo título de Campeã do Rei.\n");
        printf("Seu objetivo é sobreviver aos desafios, descobrir os segredos sombrios do castelo e finalmente se tornar assassina do rei, se livrando do seu fatídico destino nas minas de sal.\n");
    } else if (strcmp(title, "O Encontro com a Rainha") == 0) {
        printf("A Rainha de Adarlan convoca você. Ela parece saber mais sobre você do que você gostaria.\n");
        printf("Você ganha 10 pontos de vida por sua lealdade (temporária).\n");
        player->health += 10;
    } else if (strcmp(title, "A Revelação da Identidade") == 0) {
        printf("Seu verdadeiro nome e poder são revelados. Você sente uma nova força.\n");
        player->attack += 5;
        player->level++;
        printf("Seu ataque aumentou para %d e você subiu para o Nível %d!\n", player->attack, player->level);
    } else {
        printf("Um momento de reflexão e diálogo. O caminho à frente é incerto.\n");
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
    
    printf("Você enfrenta um(a) %s (Vida: %d, Ataque: %d, Defesa: %d).\n", enemy_name, enemy_health, enemy_attack, enemy_defense);
    
    while (player->health > 0 && enemy_health > 0) {
        int player_damage = player->attack - enemy_defense;
        if (player_damage < 1) player_damage = 1;
        
        int enemy_damage = enemy_attack - player->defense;
        if (enemy_damage < 1) enemy_damage = 1;
        
        // Turno do Jogador
        enemy_health -= player_damage;
        printf("Você ataca! %s perde %d de vida. (Restante: %d)\n", enemy_name, player_damage, enemy_health > 0 ? enemy_health : 0);
        
        if (enemy_health <= 0) {
            printf("Você derrotou o(a) %s!\n", enemy_name);
            player->health += 10; // Recompensa
            printf("Você recupera 10 de vida. Vida atual: %d\n", player->health);
            return;
        }
        
        // Turno do Inimigo
        player->health -= enemy_damage;
        printf("%s ataca! Você perde %d de vida. (Restante: %d)\n", enemy_name, enemy_damage, player->health > 0 ? player->health : 0);
        
        if (player->health <= 0) {
            printf("Você foi derrotado(a) por %s. Fim de Jogo.\n", enemy_name);
            exit(0); // Fim de jogo
        }
    }
}

void handle_minigame(Character *player, Deck *deck) {
    printf("\n[MINI-GAME] Você precisa vencer um jogo de cartas para obter informações cruciais.\n");
    comecarJogoCorte(player, deck);
}
