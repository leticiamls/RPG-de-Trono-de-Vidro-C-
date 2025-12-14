#include <stdio.h>
#include <string.h>
#include "../include/game_logic.h"
#include "../include/character.h"
#include "../include/npc.h"
#include "../include/narrativa.h"
#include "../include/inventario.h"

// Cores
#define CYN "\e[0;36m"
#define PADRAO "\x1b[0m"
#define COR_VERMELHA "\033[31m"
#define COR_VERDE "\033[32m"
#define COR_AZUL "\033[0;34m"
#define NEGRITO "\033[1m"
#define COR_MAGENTA "\033[0;35m"
#define COR_LARANJA "\033[0;33m"

void print_narrative_block(const char *start_tag, const char *end_tag) {
    FILE *file = fopen("narrativa.dat", "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo de narrativa");
        return;
    }

    char line[512];
    int reading = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, start_tag) != NULL) {
            reading = 1;
            continue;
        }

        if (strstr(line, end_tag) != NULL) {
            reading = 0;
            break;
        }

        if (reading) {
            line[strcspn(line, "\n")] = 0;
            printf("%s\n", line);
        }
    }

    fclose(file);
}

void narrativa_endovier(Character *player) {
	print_narrative_block("#NARRATIVA_ENDOVER#", "#FIM_NARRATIVA_ENDOVER#");
	int escolhasNarrativa = 0;
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
	print_narrative_block("#NARRATIVA_ENDOVER2#", "#FIM_NARRATIVA_ENDOVER2#");
}

void narrativa_castelo(Character *player) {
    print_narrative_block("#NARRATIVA_CASTELO#", "#FIM_NARRATIVA_CASTELO#");
    int escolhasCompetidores = 0;
    scanf("%d", &escolhasCompetidores);
    printf("Acao escolhida: %d\n", escolhasCompetidores);

    switch (escolhasCompetidores) {
        case 1:
            printf("\nVoce mantem a cabeca baixa. A calma esconde o predador, mas Chaol, que a observava, parece aliviado.\n");
            g_chaol->amizade_score += 5;
            printf("%s+5 de amizade com Chaol Westfall (Comportamento controlado).%s Amizade atual: %d/100\n", COR_VERDE, PADRAO, g_chaol->amizade_score);
            break;
        case 2:
            printf("\nVoce retribui o olhar com um sorriso lento e frio, prometendo dor. Cain desvia o olhar primeiro. Voce ganha respeito, mas Chaol fica tenso.\n");
            player->attack += 1;
            g_chaol->amizade_score -= 3;
            printf("%s+1 Ataque (Moral); -3 de amizade com Chaol Westfall (Desafio Aberto).%s Amizade atual: %d/100\n", COR_VERDE, PADRAO, g_chaol->amizade_score);
            break;
        case 3:
            printf("\n%s%sCelaena:%s (Baixo) \"Um porco gordo vestido de seda. Em breve serei a faca que te sangrara.\"\n", NEGRITO, COR_LARANJA, PADRAO);
            printf("\nCain ouviu, e sua raiva e palpavel. Chaol a fuzila com o olhar.\n");
            g_chaol->amizade_score -= 8;
            printf("%s-8 de amizade com Chaol Westfall (Comportamento impulsivo).%s Amizade atual: %d/100\n", COR_VERMELHA, PADRAO, g_chaol->amizade_score);
            break;
        default:
            printf("\nVoce foca no jantar (Ação Padrao).\n");
            break;
    }

    printf("\n\n%sHoras depois...%s", NEGRITO, PADRAO);

    printf("\n\nVoce e convocada. O ambiente e frio no Salao do Trono. O Rei de Adarlan esta la, ao lado de Dorian e Chaol.\n");
    
    printf("\n%s%sRei de Adarlan:%s \"Celaena Sardothien. Voce e uma ferramenta. Uma que posso quebrar ou afiar. Sua lealdade e a unica moeda que me interessa. O que voce tem a dizer em sua defesa... ou submissao?\"\n", NEGRITO, COR_VERMELHA, PADRAO);
    
    int escolhasNarrativa = 0;
    printf("*** Voce deseja:\n");
    printf("%s1) Mostrar Lealdade Absoluta ao Rei (Falsa Submissao); \n2) Responder com Desafio (Orgulho); \n3) Fazer uma Proposta Cinica (Acesso a Biblioteca).%s\n", COR_MAGENTA, PADRAO);
    
    scanf("%d", &escolhasNarrativa);
    printf("Acao escolhida: %d\n", escolhasNarrativa);


    switch (escolhasNarrativa) {
        case 1:
            printf("\nVoce jura obediencia superficial. O Rei fica satisfeito e lhe concede um bonus de saude para os treinos.\n");
            g_chaol->amizade_score += 15;
            g_dorian->amizade_score += 5;
            player->health += 10;
            printf("%s+10hp, +15 Chaol, +5 Dorian.%s\n", COR_VERDE, PADRAO);
            break;
        case 2:
            printf("\nVoce o chama de Tirano. A aura do Rei escurece. Chaol tenta te acalmar.\n");
            g_chaol->amizade_score -= 5;
            g_dorian->amizade_score += 10;
            player->health -= 5;
            printf("%s-5hp, -5 Chaol, +10 Dorian.%s\n", COR_VERMELHA, PADRAO);
            break;
        case 3:
            printf("\n%s%sCelaena:%s \"Minha habilidade tem um preço. Me de acesso a sua biblioteca, e farei sua vontade.\"\n", NEGRITO, COR_LARANJA, PADRAO);
            printf("\nDorian ri, e o Rei, intrigado, concorda. A Biblioteca e sua nova arma secreta.\n");
            g_chaol->amizade_score += 5;
            g_dorian->amizade_score += 15;
            printf("%s+5 Chaol, +15 Dorian.%s\n", COR_VERDE, PADRAO);
            break;
        default:
            printf("\nVoce se manteve estoica (Acao Padrao). O Principe parece levemente impressionado.\n");
            g_dorian->amizade_score += 10;
            player->health += 10;
            printf("%s+10hp, +10 Dorian.%s\n", COR_VERDE, PADRAO);
            break;
    }
    
    printf("\nO Rei a dispensou. Sua jornada no Castelo de Vidro e com os outros competidores comecou oficialmente.\n");

    printf("\n---\n");
}

void narrativa_mortes_repentinas(Character *player) {
    print_narrative_block("#NARRATIVA_MORTES_REPENTINAS#", "#FIM_NARRATIVA_MORTES_REPENTINAS#");
    int escolhasNarrativa = 0;
    scanf("%d", &escolhasNarrativa);
    printf("Acao escolhida: %d\n", escolhasNarrativa);

    switch (escolhasNarrativa) {
        case 1:
            printf("\nVoce toca o pergaminho. Uma dor lancinante atinge voce, mas visoes de Fae, Valg e um nome antigo - **Aelin Galathynius** - inundam sua mente. Seu verdadeiro nome e poder sao despertados(Porem, para ativar seu poder, voce precisara vencer um desafio posterior).\n");
            player->attack += 5;
            g_chaol->amizade_score -= 10;
            g_dorian->amizade_score += 15;
            printf("%s+5 Ataque.%s Sua saude agora e: %s%s%d%s. %s-10 Chaol, +15 Dorian.%s\n", 
                   COR_VERDE, PADRAO, NEGRITO, COR_AZUL, player->health, PADRAO, COR_VERMELHA, PADRAO);
            break;
        case 2:
            printf("\nVoce ignora o pergaminho e se coloca entre Chaol e Dorian, tentando acalmar a situacao. Voce prioriza a discricao sobre a descoberta magica.\n");
            g_chaol->amizade_score += 15;
            g_dorian->amizade_score -= 5;
            printf("%s+15 de amizade com Chaol Westfall (Lealdade ao Patrono).%s Amizade atual: %d/100. %s-5 Dorian.%s\n", 
                   COR_VERDE, PADRAO, g_chaol->amizade_score, COR_VERMELHA, PADRAO);
            break;
        case 3:
            printf("\nEm um ato de desespero, voce empurra Dorian para o pergaminho. Ele sente uma atracao e sua magia latente desperta violentamente(Porem, para ativar seu poder, voce precisara vencer um desafio posterior). Dorian esta chocado com a sua traicao, mas agora confia no poder da magia.\n");
            g_dorian->amizade_score += 10;
            g_chaol->amizade_score -= 15; // Repugnância por usar o Príncipe
            player->health -= 3; 
            printf("%s-3hp, -15 Chaol (Repugnancia), +10 Dorian (Segredo Mutuo).%s Sua saude agora e: %s%s%d%s.\n", 
                   COR_VERMELHA, PADRAO, NEGRITO, COR_AZUL, player->health, PADRAO);
            break;
        default:
            printf("\nVoce decide que o pergaminho deve ser destruido imediatamente, concordando com a cautela de Chaol.\n");
            g_chaol->amizade_score += 10;
            printf("%s+10 Chaol.%s\n", COR_VERDE, PADRAO);
            break;
    }
    
    printf("\nO misterio se aprofunda. Com ou sem magia, voce sabe que o Torneio e uma fachada para um mal muito maior. O verdadeiro inimigo esta escondido nas sombras do Castelo de Vidro.\n");

    printf("\n---\n");
}

void narrativa_the_last_dance(Character *player) {
    print_narrative_block("#NARRATIVA_THE_LAST_DANCE#", "#FIM_NARRATIVA_THE_LAST_DANCE#");
    int escolhasNarrativa = 0;
    scanf("%d", &escolhasNarrativa);

    switch (escolhasNarrativa) {
        case 1:
            printf("\nVoce pega o amuleto de ferro frio. Prioriza a tatica sobre o vinculo.\n");
            player->defesa += 5;
            g_dorian->amizade_score += 5;
            player->level++;
            printf("%s+5 Defesa. +5 Dorian. Nivel Up!%s\n", COR_VERDE, PADRAO);
            break;
        case 2:
            printf("\n%s%sCelaena:%s \"Eu sou Aelin Ashryver Galathynius, Rainha de Terrasen.\"\n", NEGRITO, COR_LARANJA, PADRAO);
            player->level++; 
            g_dorian->amizade_score += 20;
            printf("%sNivel Up! +20 Dorian (Confianca Total).%s\n", COR_VERDE, PADRAO);
            break;
        case 3:
            printf("\nVoce recusa o amuleto. Confia apenas em si mesma.\n");
            player->attack += 3;
            g_dorian->amizade_score -= 10;
            player->level++;
            printf("%s+3 Ataque. -10 Dorian (Decepcao). Nivel Up!%s\n", COR_VERDE, PADRAO);
            break;
        default:
            printf("\nVoce acena com a cabeca e se afasta (Acao Padrao).\n");
            g_dorian->amizade_score += 5;
            player->level++;
            printf("%s+5 Dorian.%s Nivel Up!\n", COR_VERDE, PADRAO);
            break;
    }
    printf("\n---\n");
}

void narrativa_confronto_ridderak(Character *player) {
    print_narrative_block("#NARRATIVA_CONFRONTO_RIDDERAK#", "#FIM_NARRATIVA_CONFRONTO_RIDDERAK#");
}

void narrativa_confronto_final(Character *player) {
    print_narrative_block("#NARRATIVA_CONFRONTO_CAIN#", "#FIM_NARRATIVA_CONFRONTO_CAIN#");
}

void handle_narrative(const char *title, Character *player) {
    printf("\n[NARRATIVA] Voce esta em %s.\n", title);
    if (strcmp(title, "Minas de Endovier") == 0) {
        narrativa_endovier(player);
    } else if (strcmp(title, "O Castelo de Vidro") == 0) {
        narrativa_castelo(player);
    } else if (strcmp(title, "Mortes Repentinas") == 0) {
        narrativa_mortes_repentinas(player);
    } else if (strcmp(title, "The Last Dance") == 0) {
        narrativa_the_last_dance(player);
    } else {
        printf("Um momento de reflexao e dialogo. O caminho a frente e incerto.\n");
    }
    
    display_character_stats(player);
    display_npc_stats();
}