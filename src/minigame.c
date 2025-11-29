#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/minigame.h"

void comecarJogoCorte(Character *player, Deck *deck) {
    if(deck->size < 2) {
        printf("O baralho esta incompleto. Impossivel jogar.\n");
        return;
    }

    int pot_favors = 0;
    int player_ante = 25; 
    int opponent_ante = 25;
    int opponent_favors = 300;

    printf("\n===============================================\n");
    printf("== CELAENA vs NEHEMIA : o desafio dos segredos ==\n");
    printf("=================================================\n");
    printf("Celaena: Voce esta em um duelo de astucia contra a Princesa Nehemia. O premio e uma peca vital de **Informacao** para seu proximo desafio. Você não está apostando no segredo em si, mas sim no risco e na importância que aquele segredo representa no contexto da corte.\n");
    printf("\n** REGRAS DA RODADA: **\n");
    printf("* **1. Segredo Revelado:** Uma carta eh virada, definindo o Segredo da rodada (Guerra/Alianca/Profecia).\n");
    printf("A carta virada (o Segredo) não é a carta de duelo, é o fator de influência da rodada. Ela define o tom:\n");
    printf("Se o Segredo for de Guerra (Carta tipo Ataque): O risco é alto. Nehemia pode apostar alto, indicando que a informação é crucial para a guerra. Sua aposta agora tem um peso maior, pois está ligada à vida ou morte.\n");
    printf("Se o Segredo for uma Aliança (Carta tipo Defesa): O risco pode ser menor ou mais focado em política. As apostas tendem a ser mais cautelosas, mas uma vitória pode significar o controle de uma aliança vital...\n");
    printf("* **2. Apostas:** Nehemia aposta uma determinada quantidade de ouro. Voce deve **Cobrir**, **Aumentar (Blefe)** ou **Desistir**.\n");
    printf("    -> Seu **Ataque (Intimidacao)** e seu poder de Blefe.\n");
    printf("* **3. Duelo Final:** Se as apostas forem cobertas, a Habilidade e o Destino decidem o vencedor.\n");
    printf("    -> O vencedor e decidido pela soma: (Valor da Carta) + (Seu Destino/Wyrd).\n");
    printf("\n** ALTO RISCO:** Vencer garante a **Informacao Crucial**. Perder pode custar ouro e um **Debuff** (Desvantagem).\n");
    printf("============================================\n");
 
printf("== O JOGO DA CORTE: BLEFE E SEGREDOS ==\n");
    printf("Voce e seu oponente colocam um 'ante' inicial de %d Favores (Moedas de Prata) cada.\n", player_ante);

    if (player->ouro < player_ante) {
        printf("Voce nao tem Favores suficientes para o 'ante' inicial!\n");
        return;
    }

    player->ouro -= player_ante;
    opponent_favors -= opponent_ante;
    pot_favors += player_ante + opponent_ante;

    // --- LOOP DA RODADA DE BLEFE ---
    printf("\n--- Revelacao do Segredo ---\n");

    // Simula a primeira carta virada na mesa: o Segredo que influencia a aposta
    Card *secret_card = draw_card(deck);
    if (secret_card == NULL) {
        printf("Erro ao revelar o Segredo da Corte.\n");
        return;
    }
    
    // Nomes temáticos baseados no 'type' da carta (reusando as constantes do minigame.h)
    char secret_name[50];
    if (secret_card->type == CARD_TYPE_ATAQUE) sprintf(secret_name, "Segredo de Guerra");
    else if (secret_card->type == CARD_TYPE_DEFESA) sprintf(secret_name, "Alianca Politica");
    else if (secret_card->type == CARD_TYPE_SORTE) sprintf(secret_name, "Profecia Antiga");
    else sprintf(secret_name, "Segredo Menor");


    printf("O Segredo Revelado e: **%s** (Valor: %d)\n", secret_name, secret_card->valor);

    // Oponente faz aposta baseada no segredo e na sua Força (Intimidação)
    int opponent_raise_amount = 40; 
    if (secret_card->valor >= 5 && secret_card->type == CARD_TYPE_ATAQUE) {
        // Oponente se sente forte por ser um Segredo de Guerra
        opponent_raise_amount = 75 + (rand() % 40); 
    } else {
        opponent_raise_amount = 40 + (rand() % 30); 
    }

    printf("O Oponente (Conselheiro Real) APOSTA: %d ouro(s).\n", opponent_raise_amount);
    int current_bet = opponent_raise_amount;

    // O jogador deve decidir
    int choice = 0;
    int player_raise_amount = 0;

    printf("\nSeus Favores: %d. Aposta de Poder Atual: %d.\n", player->ouro, pot_favors);
    printf("Escolha sua acao:\n");
    printf("1. Cobrir Aposta (%d Favores)\n", current_bet);
    printf("2. Aumentar Aposta (Blefe)\n");
    printf("3. Desistir (Perde a Honra)\n");
    printf("Sua escolha: ");

    // Simulação da entrada do usuário (em um jogo real, este seria o scanf)
    // Para fins deste exemplo de código, vou assumir uma entrada do usuário para a escolha.
    scanf("%d", &choice);

    if (choice == 3) {
        // Desistir
        printf("\nVoce DESISTIU do Segredo. O Conselheiro vence e sua **Reputacao** e levemente afetada.\n");
        player->sorte -= 1; 
        free(secret_card);
        display_character_stats(player);
        return;
    } else if (choice == 1) {
        // Cobrir Aposta (Call)
        if (player->ouro < current_bet) {
             printf("Favores insuficientes! Desistindo automaticamente.\n");
             free(secret_card);
             display_character_stats(player);
             return;
        }
        player->ouro -= current_bet;
        // Aposta do oponente ja foi considerada no 'raise'
        pot_favors += current_bet;
        printf("Voce COBRE a aposta. O duelo continua...\n");
        
    } else if (choice == 2) {
        // Aumentar Aposta (Raise/Blefe)
        printf("Quanto Favores voce deseja aumentar (minimo %d)? ", current_bet + 1);
        scanf("%d", &player_raise_amount);

        if (player_raise_amount <= current_bet || player->ouro < player_raise_amount) {
            printf("Aumento invalido ou Favores insuficientes. Cobrindo aposta em vez disso.\n");
            player_raise_amount = current_bet;
        }
        
        player->ouro -= player_raise_amount;
        pot_favors += player_raise_amount;
        printf("Voce AUMENTOU a aposta para %d Favores! (Usando sua Intimidacao: %d)\n", player_raise_amount, player->attack);
        
        // Simular a reacão do Oponente ao aumento do jogador (Blefe vs. Intimidação)
        // Se o aumento for muito grande E o jogador tiver um 'attack' alto, o NPC pode desistir.
        if (player_raise_amount > opponent_raise_amount * 2 && player->attack >= 15) {
            printf("O Conselheiro, intimidado por sua Forca e Blefe, DESISTE! Voce ganha a Aposta de Poder.\n");
            player->ouro += pot_favors;
            player->attack += 1; // Recompensa por blefe de sucesso
            free(secret_card);
            display_character_stats(player);
            return;
        } else {
            // Oponente cobre a aposta aumentada
            int difference = player_raise_amount - opponent_raise_amount;
            opponent_favors -= difference;
            pot_favors += difference;
            printf("O Conselheiro COBRE. Preparando para o Duelo de Destino...\n");
        }
    }

    // --- 2. Fase de Duelo de Destino (Showdown) ---
    printf("\n--- DUELO DE DESTINO (Wyrd) ---\n");
    
    Card *player_duel_card = draw_card(deck);
    Card opponent_duel_card;
    opponent_duel_card.valor = 1 + (rand() % 7);
    int opponent_luck = 5; // Oponente tem um Destino fixo
    
    // O Destino é o fator principal (metade do 'luck' somado)
    int final_player_score = player_duel_card->valor + (player->sorte / 2); 
    int final_opponent_score = opponent_duel_card.valor + (opponent_luck / 2); 

    printf("Sua Carta: %d (+%d de Destino) = **%d**\n", 
           player_duel_card->valor, player->sorte / 2, final_player_score);
    printf("Carta Oponente: %d (+%d de Destino) = **%d**\n", 
           opponent_duel_card.valor, opponent_luck / 2, final_opponent_score);
    
    // --- 3. Resultado Final ---
    if (final_player_score > final_opponent_score) {
        printf("\n*** VITORIA! ***\n");
        printf("Seu Destino foi mais forte. Voce ganhou %d Favores e uma Boa Sorte na proxima missao.\n", pot_favors);
        player->ouro += pot_favors;
        player->sorte += 2; // Recompensa por sorte
    } else {
        printf("\n*** DERROTA! ***\n");
        printf("O Destino te traiu. Voce perdeu o Pote para o Conselheiro e sofre uma penalidade na **Defesa**.\n");
        player->defesa -= 5; 
    }

    // Limpeza
    free(secret_card);
    free(player_duel_card);
    
    // Lógica de recriação do baralho
    if (deck->size <= 1) {
        printf("\nO baralho foi esgotado. Recriando cartas de Segredos...\n");
        // Lógica para repopular o deck com novos Segredos e Tipos
    }

    display_character_stats(player);
}
