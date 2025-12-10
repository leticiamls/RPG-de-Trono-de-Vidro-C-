#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/game_logic.h"
#include "../include/minigame.h"
#include "../include/character.h"
#include "../include/npc.h"
#include "../include/combate.h"

// --- Lógica do Jogo ---

// --- Narrativas ---
void narrativa_endovier(Character *player) {
	printf("\n%s## A Libertacao da Assassina: Das Minas de Sal ao Castelo de Vidro%s\n", COR_AZUL, PADRAO);
	printf("\nPor dois anos, as minas de sal de Endovier foram seu inferno pessoal, e o nome Celaena Sardothien, a Assassina mais temida de Adarlan virou apenas mais uma lenda urbana...\n");
	printf("Voce estava em um dos tuneis escuros das Minas de Sal de Endovier, pagando sua pena perpétua com uma picareta em suas maos calejadas, quando o som dos cascos se tornou inconfundivel. Nao era a patrulha usual. O passo era pesado, ordenado. Seus sentidos, amortecidos pela miseria, despertaram instantaneamente.\n");
	printf("\nDe repente, a luz das tochas inundou o tunel, e uma figura imponente e bem-vestida parou a sua frente. Sua armadura preta refletia a chama, e seus olhos eram frios como gelo.\n");
	printf("\nO homem nao era outro senao Chaol Westfall, o Capitao da Guarda Real do Rei de Adarlan.\n\n");
	
	int escolhasNarrativa = 0;
	printf("*** Voce deseja:\n");
    printf("%s1) Questionar Guarda Real; \n2) Se manter em silencio; \n3) Tentar fugir.%s\n", COR_MAGENTA, PADRAO);
    scanf("%d", &escolhasNarrativa);
    
    switch (escolhasNarrativa) {
        case 1:
            printf("\n%s%sCelaena:%s \"O que voce quer, Chaol? Veio me matar pessoalmente? Economizaria o trabalho do frio.\"\n", NEGRITO, COR_LARANJA, PADRAO);
            printf("\nChaol a encarou com desdem, mas havia algo mais em sua rigidez.\n");
            g_chaol->amizade_score -= 5;
            printf("%s-5 de amizade com Chaol Westfall.%s Sua amizade com Chaol agora e: %s%s%d/100%s\n\n", COR_VERMELHA, PADRAO, NEGRITO, COR_AZUL, g_chaol->amizade_score, PADRAO);
            break;
        case 2:
            printf("\nVoce se mantem em silencio, nao se sabe o limite da maldade dessas pessoas poderosas a sua frente, e nem esta em forma para tentar fugir.\n");
            g_chaol->amizade_score += 10;
            printf("%s+10 de amizade com Chaol Westfall.%s Sua amizade com Chaol agora e: %s%s%d/100%s\n\n", COR_VERDE, PADRAO, NEGRITO, COR_AZUL, g_chaol->amizade_score, PADRAO);
            break;
        case 3:
            printf("\nChaol, com somente um assobio, faz com que um guarda de porte medio saia imediatamente de sua posicao e corra em sua direcao, agarrando com forca seu braco e a jogando contra a parede.\n");
            g_chaol->amizade_score -= 15;
            printf("%s-15 de amizade com Chaol Westfall.%s Sua amizade com Chaol agora e: %s%s%d/100%s\n\n", COR_VERMELHA, PADRAO, NEGRITO, COR_AZUL, g_chaol->amizade_score, PADRAO);
            player->health -= 2;
            printf("\n%s(Sua tentativa de fuga foi mal sucedida)\n-2hp\nSua saude agora e: %s%s%d%s.\n\n",COR_VERMELHA, NEGRITO, COR_AZUL, player->health, PADRAO);
            break;
        default:
            printf("\nVoce se mantem em silencio, nao se sabe o limite da maldade dessas pessoas poderosas a sua frente, e nem esta em forma para tentar fugir.\n");
            g_chaol->amizade_score += 10;
            printf("%s+10 de amizade com Chaol Westfall.%s Sua amizade com Chaol agora e: %s%s%d/100%s\n\n", COR_VERMELHA, PADRAO, NEGRITO, COR_AZUL, g_chaol->amizade_score, PADRAO);
            break;
    }
	printf("Chaol faz um sinal para os guardas, que abriram o caminho para outro homem, elegantemente vestido, com um sorriso debochado no rosto: Dorian Havilliard, o Principe Herdeiro.\n");
	printf("\n%s%sDorian:%s \"Surpresa, Celaena. Seu nome chegou aos ouvidos do meu pai, e nao da maneira que voce esperava.\"\n", NEGRITO, COR_AZUL, PADRAO);

	printf("\nVoce estreitou os olhos.\n");

	printf("\n%s%sCelaena:%s \"O Rei me quer morta, Principe. Eu o conheco melhor do que voce.\"\n", NEGRITO, COR_LARANJA, PADRAO);

	printf("\n%s%sDorian:%s \"Ah, mas nao para a morte. Para o Torneio.\"\n", NEGRITO, COR_AZUL, PADRAO);

    printf("\nA palavra a atingiu como um golpe fisico. Voce mal conseguia respirar. Torneio.\n");
    
    printf("\n%s%sChaol:%s \"O Rei esta patrocinando um torneio para encontrar um novo Campeao, um assassino a seu servico. Voce competira, Celaena. Se vencer, sera a Assassina do Rei e estara livre de Endovier. Mas, somente o vencedor saira vivo dessa competicao.\"\n", NEGRITO, COR_VERDE, PADRAO);
    
    printf("\nO Principe deu um passo a frente, a voz baixa.\n");
    
    printf("\n%s%sDorian:%s \"Voce tem a chance de sair daqui, Assassina. Deixe as minas de sal e venha para o Castelo de Vidro. Mas esteja avisada, sua liberdade e condicional. E a competicao e mortal.\"\n", NEGRITO, COR_AZUL, PADRAO);
    
    printf("\nVoce sentiu uma faisca de esperanca, um calor que nao vinha das tochas. Seria uma nova prisao, mas uma prisao de ouro, com armas e chances de vinganca.\n");
    
    printf("\n%s%sCelaena:%s \"Feito. Mande arrumar meus aposentos, Principe. E traga vinho. Eu bebo agua salgada ha dois anos.\"\n", NEGRITO, COR_LARANJA, PADRAO);
    
    printf("\nVoce ergueu o queixo, permitindo que a luz revelasse a cicatriz no seu braco. A Assassina de Adarlan estava de volta.\n");

	printf("\n---\n");

	printf("\n%sVoce foi transportada das minas de Endovier para o Castelo de Vidro. Seu primeiro capitulo de treinamento e sobrevivencia comeca agora.%s\n\n", NEGRITO, PADRAO);
}




void handle_narrative(const char *title, Character *player) {
    printf("\n[NARRATIVA] Voce esta em %s.\n", title);
    if (strcmp(title, "Minas de Endovier") == 0) {
        narrativa_endovier(player);
    } else if (strcmp(title, "O Castelo de Vidro") == 0) {
        printf("A Rainha de Adarlan convoca voce. Ela parece saber mais sobre voce do que voce gostaria.\n");
        printf("Você ganha 10 pontos de vida por sua lealdade (temporaria).\n");
        player->health += 10;
    } else if (strcmp(title, "Mortes Repentinas") == 0) {
        printf("Seu verdadeiro nome e poder sao revelados. Voce sente uma nova força.\n");
        player->attack += 5;
        player->level++;
        printf("Seu ataque aumentou para %d e voce subiu para o Nivel %d!\n", player->attack, player->level);
    } else if (strcmp(title, "The Last Dance") == 0) {
        printf("Seu verdadeiro nome e poder sao revelados. Voce sente uma nova força.\n");
        player->attack += 5;
        player->level++;
    } else {
        printf("Um momento de reflexão e dialogo. O caminho a frente e incerto.\n");
    }
    
    display_character_stats(player);
    display_npc_stats();
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
        printf("Seu poder de defesa aumentou para %d.\n", player->defesa, player->forca);
        break;
    case 3:
        player->attack += 3; 
        player->defesa += 5;
        printf("\nChaol franze a testa. \"Sorte? Não confio nela. Mas a agilidade pode salvar sua vida.\" Você treina movimentos evasivos e a leitura rápida de intenções. Seu instinto está mais aguçado.\n");
        printf("Seu atributo Sorte/Esquiva aumentou para %d.\n", player->attack, player->defesa);
        break;
    default:
        printf("\nVocê hesita. Chaol apenas suspira e se afasta. \"Perdeu seu tempo, Assassina. A indecisão é a morte.\" Você não ganha bônus.\n");
        break;
}
    
    display_character_stats(player);
}

void handle_combat(Character *player) {
    printf("\n[COMBATE] Um desafio se apresenta!\n");
    
    // --- 1. DEFINIÇÃO E CRIAÇÃO DO INIMIGO ---
    
    char *enemy_name;
    int enemy_health;
    int enemy_attack;
    int enemy_defense;
    
    // Lógica básica para definir o inimigo (usando os stats antigos como base)
    if (strcmp(player->class_name, "Assassina") == 0) {
        enemy_name = "Guarda Real";
        enemy_health = 60 + (rand() % 20); // Stats aleatórios
        enemy_attack = 10 + (rand() % 5);
        enemy_defense = 5 + (rand() % 3);
    } else {
        enemy_name = "Criatura de Wyrd";
        enemy_health = 70 + (rand() % 30);
        enemy_attack = 12 + (rand() % 5);
        enemy_defense = 6 + (rand() % 3);
    }

    // Cria o inimigo usando a função externa
    Character *enemy = create_enemy(enemy_name, enemy_health, enemy_attack, enemy_defense);
    if (enemy == NULL) {
        fprintf(stderr, "Erro critico: Falha ao criar inimigo.\n");
        return;
    }
    
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
