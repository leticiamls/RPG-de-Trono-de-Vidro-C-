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

void narrativa_castelo(Character *player) {
    printf("\n%s## O Castelo de Vidro%s\n", COR_MAGENTA, PADRAO);
    printf("\nA viagem de Endovier ao Castelo de Vidro foi rapida, mas o choque cultural foi imediato. Voce foi levada a um luxuoso quarto no anexo do castelo, uma suite digna de uma nobre, mas com guardas posicionados em cada esquina.\n");
    printf("\nChaol Westfall a informou sobre as regras: voce e a Campea do Principe, mas esta sob sua vigilancia constante.\n");

    printf("\n%s%sChaol:%s \"Ha vinte e tres competidores, todos assassinos, ladroes ou mercenarios. Cada um tem um patrono que o trouxe aqui—nobres, duques, e ate o Principe Rhaegar. Nao se engane, todos querem sua cabeca, Celaena.\"\n", NEGRITO, COR_VERDE, PADRAO);
    
    printf("\nVoce observou a cidade de Rifthold atraves da janela de vidro. A liberdade estava tao perto, mas ainda separada por camadas de mentiras e intencoes assassinas.\n");
    
    printf("\nDurante o jantar na ala dos competidores, voce sente a tensao. Um homem corpulento, com a insignia de um Barao no peito, te encara com puro desprezo. Ele e Cain, um dos favoritos.\n");
    
    int escolhasCompetidores = 0;
    printf("\n*** Voce deseja reagir a Cain:\n");
    printf("%s1) Ignorar a provocacao e focar na refeicao; \n2) Retribuir o olhar com um sorriso intimidador; \n3) Murmurar um insulto para ser ouvido.%s\n", COR_MAGENTA, PADRAO);
    
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
            printf("\n%s%sCelaena:%s (Baixo) \"Um porco gordo vestido de seda. Em breve serei a faca que te sangrará.\"\n", NEGRITO, COR_LARANJA, PADRAO);
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
    printf("Ação escolhida: %d\n", escolhasNarrativa);


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
    printf("\n%s## Mortes Repentinas: O Misterio da Marca de Wyrd%s\n", COR_VERMELHA, PADRAO);
    printf("\nO Torneio avanca, e voce elimina competidores com eficiencia fria. No entanto, algo esta errado. Candidatos fracos, que voce nem considerava ameaça, sao encontrados mortos em seus quartos, com os corpos drenados e uma marca estranha cravada na pele — as lendarias Marcas de Wyrd.\n");
    
    printf("\nA paranoia toma conta do Castelo. O Rei ordenou que Chaol dobrasse a segurança, mas nem mesmo a Guarda Real consegue impedir o terror que se espalha.\n");
    
    printf("\nEm uma noite, Dorian a encontra em segredo na vastidão da Biblioteca, onde você tem buscado respostas para a magia que o Rei jurou ter banido.\n");

    printf("\n%s%sDorian:%s \"E magia negra, Celaena. Meu pai nao esta apenas patrocinando o Torneio, ele esta acobertando algo muito mais sinistro. Eu sinto isso, como um frio no meu peito.\"\n", NEGRITO, COR_AZUL, PADRAO);
    
    printf("\nVoce revela a Dorian que suspeita de um dos competidores mais sombrios, uma princesa chamada Nehemia que desapareceu, e ambos começam a vasculhar a secao proibida da Biblioteca. Chaol, alertado pela ausencia de voces, irrompe na sala.\n");
    
    printf("\n%s%sChaol:%s \"O que voces estao fazendo aqui? Isso e loucura! Celaena, saia de perto do Principe. Eu sou responsavel pela sua segurança, e nao vou permitir que seja envolvida com qualquer... porcaria magica que ele encontre!\"\n", NEGRITO, COR_VERDE, PADRAO);
    
    printf("\nNa pressa, voce derruba um volume antigo. Dele cai um pergaminho coberto de runas de Wyrd, brilhando com uma energia maligna, atraindo voce e repelindo Chaol.\n");

    int escolhasNarrativa = 0;
    printf("\n*** A energia do pergaminho e poderosa e ameacadora. Voce deve agir:\n");
    printf("%s1) Tocar no Pergaminho para absorver seu conhecimento (Alto Risco, Alto Ganho); \n2) Ignorar a magia e focar em acalmar a furia de Chaol; \n3) Usar Dorian como escudo, empurrando-o para a magia (Traicao de Confiança).%s\n", COR_MAGENTA, PADRAO);

    scanf("%d", &escolhasNarrativa);
    printf("Ação escolhida: %d\n", escolhasNarrativa);

    switch (escolhasNarrativa) {
        case 1:
            printf("\nVoce toca o pergaminho. Uma dor lancinante atinge voce, mas visoes de Fae, Valg e um nome antigo - **Aelin Galathynius** - inundam sua mente. Seu verdadeiro nome e poder sao despertados(Porem, para ativar seu poder, voce precisara vencer um desafio posterior).\n");
            player->attack += 5;
            player->level++;
            g_chaol->amizade_score -= 10;
            g_dorian->amizade_score += 15;
            printf("%s+5 Ataque, Nivel Up!%s Sua saude agora é: %s%s%d%s. %s-10 Chaol, +15 Dorian.%s\n", 
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
    printf("\n%s## The Last Dance: A Final Sombria e o Legado Desperto%s\n", COR_LARANJA, PADRAO);
    printf("\nVoce esta na iminencia da Final. Apos o encontro com o espirito da Rainha Elena e de saber que voce sabe que e Aelin Galathynius, a herdeira de Terrasen, e que o Rei esta trazendo os Valg (senhores demoniacos) para Erilea.\n");
    
    printf("\nO Grande Salao esta repleto. Seu oponente, Cain, esta sob a influencia maligna do Wyrd, uma criatura de forca sobrenatural.\n");
    
    printf("\nAntes do duelo, Dorian se aproxima de voce, palido. Ele lhe entrega um pequeno amuleto de ferro frio, um material detestado pela magia.\n");
    
    int escolhasNarrativa = 0;
    printf("\n*** Em face da magia sombria e de sua nova identidade, voce deve escolher:\n");
    printf("%s1) Aceitar o Amuleto e Focar na Luta; \n2) Confessar a Dorian a verdade total sobre Aelin Galathynius; \n3) Recusar o amuleto, confiando apenas em sua propria forca.%s\n", COR_MAGENTA, PADRAO);
    scanf("%d", &escolhasNarrativa);

    switch (escolhasNarrativa) {
        case 1:
            printf("\nVoce pega o amuleto de ferro frio. Prioriza a tatica sobre o vinculo.\n");
            add_item(&player->inventory, "AMULETO: anulador de magia(voce bloqueara a magia inimiga, mas nao sera capaz de utilizar a sua)", 1, 0, ITEM_TYPE_BUFF);
            player->defesa += 5;
            g_dorian->amizade_score += 5;
            printf("%s+5 Defesa. +5 Dorian.%s\n", COR_VERDE, PADRAO);
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
            printf("%s+3 Ataque. -10 Dorian (Decepcao).%s\n", COR_VERDE, PADRAO);
            break;
        default:
            printf("\nVoce acena com a cabeca e se afasta (Acao Padrao).\n");
            g_dorian->amizade_score += 5;
            printf("%s+5 Dorian.%s\n", COR_VERDE, PADRAO);
            break;
    }
    printf("\n---\n");
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
        printf("Um momento de reflexão e dialogo. O caminho a frente e incerto.\n");
    }
    
    display_character_stats(player);
    display_npc_stats();
}