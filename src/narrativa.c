#include <stdio.h>
#include <string.h>
#include "../include/game_logic.h"
#include "../include/character.h"
#include "../include/npc.h"
#include "../include/narrativa.h"

// Cores
#define CYN "\e[0;36m"
#define PADRAO "\x1b[0m"
#define COR_VERMELHA "\033[31m"
#define COR_VERDE "\033[32m"
#define COR_AZUL "\033[0;34m"
#define NEGRITO "\033[1m"
#define COR_MAGENTA "\033[0;35m"
#define COR_LARANJA "\033[0;33m"

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