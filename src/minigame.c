#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/minigame.h"

#include "minigame.h"
// --- Funções de Inventário ---




// --- Funções de Lógica (Blackjack) ---

int calcular_valor_runa(const Runa *runa) {
    if (strstr(runa->simbolo, "Lamina") || strstr(runa->simbolo, "Coroa") || strstr(runa->simbolo, "Dragao")) {
        return 10;
    }
    if (strstr(runa->simbolo, "AELINO")) {
        return 11;
    }
    
    size_t len = strlen(runa->simbolo);
    if (len > 0 && runa->simbolo[len - 1] >= '0' && runa->simbolo[len - 1] <= '9') {
        return runa->simbolo[len - 1] - '0';
    }
    return 0;
}

int calcular_pontuacao(const Runa *head) {
    int pontuacao = 0;
    int ases = 0;
    const Runa *current = head;
    
    while (current) {
        int valor = calcular_valor_runa(current);
        if (valor == 11) {
            ases++;
        }
        pontuacao += valor;
        current = current->prox;
    }

    while (pontuacao > 21 && ases > 0) {
        pontuacao -= 10;
        ases--;
    }

    return pontuacao;
}

Runa* distribuir_carta(Runa **baralho) {
    if (*baralho == NULL) return NULL;

    int contagem = 0;
    Runa *temp = *baralho;
    while (temp != NULL) {
        contagem++;
        temp = temp->prox;
    }

    if (contagem == 0) return NULL;
    int indice_aleatorio = rand() % contagem;

    Runa *atual = *baralho;
    Runa *anterior = NULL;

    for (int i = 0; i < indice_aleatorio; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) {
        *baralho = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    atual->prox = NULL;
    atual->ativada = 1;
    return atual;
}

void imprimir_mao(const char *nome, const Runa *mao, int ocultar_primeira, int pontuacao_revelada) {
    printf("  %s: [", nome);
    const Runa *current = mao;
    int i = 0;

    while (current) {
        if (ocultar_primeira && i == 0) {
            printf(NEGRITO "???" PADRAO);
        } else {
            if (strcmp(nome, "Elena") == 0) {
                printf(COR_VERMELHA "%s" PADRAO, current->simbolo);
            } else {
                printf(COR_VERDE "%s" PADRAO, current->simbolo);
            }
        }
        
        current = current->prox;
        if (current) {
            printf(", ");
        }
        i++;
    }
    printf("]");

    if (pontuacao_revelada) {
        printf(" (Pontuacao: %d)\n", calcular_pontuacao(mao));
    } else {
        printf("\n");
    }
}

int jogar_rodada(Runa **baralho, int num_rodada, int *vitorias_celaena, int *vitorias_npc) {
    Runa *mao_celaena = NULL;
    Runa *mao_npc = NULL;
    int pontuacao_celaena;
    int pontuacao_npc;
    char acao;
    int resultado = 0; // 1=Vitória Celaena, -1=Vitória NPC, 0=Empate

    printf("\n" NEGRITO "--------------------------- | RODADA %d | ---------------------------\n" PADRAO, num_rodada);
    printf("PLACAR: Celaena %d - %d Elena\n", *vitorias_celaena, *vitorias_npc);

    // Distribuição inicial (2 cartas para cada)
    mao_celaena = anexar_runa(mao_celaena, distribuir_carta(baralho));
    mao_npc = anexar_runa(mao_npc, distribuir_carta(baralho));
    mao_celaena = anexar_runa(mao_celaena, distribuir_carta(baralho));
    mao_npc = anexar_runa(mao_npc, distribuir_carta(baralho));

    if (!mao_celaena || !mao_npc) {
        printf("Erro ao distribuir cartas iniciais. Fim de jogo.\n");
        return 0;
    }

    printf("\n**Elena te entrega duas cartas do baralho de Oryonth. Sua Heranca Escondida:\n");
    imprimir_mao("Celaena", mao_celaena, 0, 1);

    printf("\n'Veja, Assassina. Esta e a face da Magia de Adarlan que eu controlo.'\n");
    imprimir_mao("Elena", mao_npc, 1, 0);

    // --- Turno de Celaena ---
    do {
        pontuacao_celaena = calcular_pontuacao(mao_celaena);

        if (pontuacao_celaena > 21) {
            printf(COR_VERMELHA NEGRITO "ESTOUROU! (%d) Voce ultrapassou 21. Elena Galathynius ri.\n" PADRAO, pontuacao_celaena);
            resultado = -1;
            break;
        }
        if (pontuacao_celaena == 21) {
            printf(COR_VERDE NEGRITO "FOGO DE FAE (21)! Voce atingiu o maximo.\n" PADRAO);
            break;
        }

        printf("\nSua pontuacao atual: %d. Deseja (H)it (Puxar Lamina) ou (S)tand (Esperar)? ", pontuacao_celaena);
        if (scanf(" %c", &acao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (acao == 'H' || acao == 'h') {
            Runa *nova_carta = distribuir_carta(baralho);
            if (nova_carta) {
                mao_celaena = anexar_runa(mao_celaena, nova_carta);
                printf("Voce puxa a lamina: %s\n", nova_carta->simbolo);
                imprimir_mao("Celaena", mao_celaena, 0, 1);
                imprimir_mao("Elena", mao_npc, 1, 0);
            } else {
                printf("Baralho acabou!\n");
                break;
            }
        }
    } while (acao == 'H' || acao == 'h');

    if (resultado != 0) {
        liberar_baralho(mao_celaena);
        liberar_baralho(mao_npc);
        return resultado;
    }

    // --- Turno da Rainha ---
    printf("\n--- Turno da Rainha ---\n");
    printf(NEGRITO "Elena revela sua carta oculta (Valg Oculto).\n" PADRAO);
    imprimir_mao("Elena", mao_npc, 0, 1);

    pontuacao_npc = calcular_pontuacao(mao_npc);

    while (pontuacao_npc < 17) {
        printf("Elena deve continuar Puxando...\n");
        Runa *nova_carta = distribuir_carta(baralho);
        if (nova_carta) {
            mao_npc = anexar_runa(mao_npc, nova_carta);
            printf("Elena recebeu: %s\n", nova_carta->simbolo);
            imprimir_mao("Elena", mao_npc, 0, 1);
        } else {
            printf("Baralho acabou!\n");
            break;
        }
        pontuacao_npc = calcular_pontuacao(mao_npc);
    }
    
    if (pontuacao_npc >= 17 && pontuacao_npc <= 21) {
        printf("Elena para com pontuacao: %d\n", pontuacao_npc);
    }

    // --- RESULTADO FINAL ---
    printf("\n" NEGRITO "--- RESULTADO DA RODADA %d ---\n" PADRAO, num_rodada);
    printf("Sua Pontuacao: %d\n", pontuacao_celaena);
    printf("Pontuacao de Elena: %d\n", pontuacao_npc);

    if (pontuacao_celaena > 21) {
        resultado = -1;
    } else if (pontuacao_npc > 21) {
        printf(COR_VERDE NEGRITO "VITORIA! Elena Estourou! (%d)\n" PADRAO, pontuacao_npc);
        resultado = 1;
    } else if (pontuacao_celaena > pontuacao_npc) {
        printf(COR_VERDE NEGRITO "VITORIA! Sua pontuacao e maior.\n" PADRAO);
        resultado = 1;
    } else if (pontuacao_celaena < pontuacao_npc) {
        printf(COR_VERMELHA NEGRITO "DERROTA. Sua pontuacao e menor.\n" PADRAO);
        resultado = -1;
    } else {
        printf("EMPATE (Push)! O destino nao foi decidido.\n");
        resultado = 0;
    }

    liberar_baralho(mao_celaena);
    liberar_baralho(mao_npc);
    
    return resultado;
}


// --- Função Principal do Jogo (Duelo de Três) ---
void blackjack() {
    srand(time(NULL));
    int vitorias_celaena = 0;
    int vitorias_npc = 0;
    int rodada_atual = 1;
    int resultado_rodada;
    Runa *baralho_mestre = NULL;
    
    // Variável para o Inventário de Conhecimento
    Conhecimento *inventario_celaena = NULL; 

    printf("\n" NEGRITO "==== Duelo de Simbolos (Trono de Vidro) ====\n" PADRAO);

    // Introdução Narrativa
    printf("**O ar nas catacumbas cheira a poeira e mofo. Os passos de Celaena ecoam, tensos, ate ela encontrar Elena Galathynius, a primeira rainha de Adarlan. Para provar seu valor e herdar seu destino, Celaena deve vencer o jogo que Elena propoe: um duelo de chance, sabedoria e coragem. O premio e o Conhecimento das Chaves de Wyrd (essencial para a batalha final).\n\n");
    
    // Regras
    printf(NEGRITO "============================== Regras do Jogo ==============================\n" PADRAO);
    printf("1- O numero no final da carta determina seu valor (2-9). Figuras (Lamina, Coroa, Dragao) valem 10. Aelino (As) vale 1/11.\n");
    printf("2- Voce deve puxar uma nova carta (Hit) com o objetivo de sua mao totalizar o mais proximo possivel de 21, sem ultrapassar.\n");
    printf("3- Caso voce ultrapasse o valor (BUST), voce automaticamente perde a rodada.\n");
    printf("4- Caso voce atinja o valor exato (21), voce automaticamente ganha a rodada.\n");
    printf(NEGRITO "5- Serao tres rodadas, quem ganhar a maior quantidade de rodadas (2) vence o duelo.\n\n" PADRAO);
    printf(NEGRITO "==========================================================================\n" PADRAO);

    // Loop do Melhor de Três
    while (vitorias_celaena < 2 && vitorias_npc < 2) {
        // Cria um novo baralho para cada duelo (opcional, mas mais justo)
        liberar_baralho(baralho_mestre);
        baralho_mestre = criar_baralho_runas();

        resultado_rodada = jogar_rodada(&baralho_mestre, rodada_atual, &vitorias_celaena, &vitorias_npc);

        if (resultado_rodada == 1) {
            vitorias_celaena++;
        } else if (resultado_rodada == -1) {
            vitorias_npc++;
        }
        
        if (vitorias_celaena < 2 && vitorias_npc < 2) {
            char continuar;
            printf("\nPLACAR ATUAL: Celaena %d - %d Elena.\n", vitorias_celaena, vitorias_npc);
            printf("Pressione 'C' para continuar para a proxima rodada... ");
            if (scanf(" %c", &continuar) != 1) {
                while (getchar() != '\n');
            }
            while (getchar() != '\n');
        }

        rodada_atual++;
        if (rodada_atual > 3 && vitorias_celaena == vitorias_npc) {
            printf("\n--- EMPATE NO MELHOR DE TRES! UMA RODADA DE DESEMPATE E NECESSARIA. ---\n");
        }
    }

    // Fim do Jogo
    printf("\n" NEGRITO "***************** FIM DO DUELO DE SIMBOLOS *****************\n" PADRAO);
    printf("PLACAR FINAL: Celaena %d - %d Elena\n", vitorias_celaena, vitorias_npc);

    if (vitorias_celaena > vitorias_npc) {
        printf(COR_VERDE NEGRITO "\nVITORIA SUPREMA! Você venceu Elena!\n" PADRAO);
        
        // Adquirir o Conhecimento
        inventario_celaena = adicionar_ao_inventario(inventario_celaena, "CHAVE DE WYRD: O Mapa Antigo");
        inventario_celaena = adicionar_ao_inventario(inventario_celaena, "MAGIA FAE: Poder Desbloqueado");

        imprimir_inventario(inventario_celaena);

    } else {
        printf(COR_VERMELHA NEGRITO "\nDERROTA. Elena ri friamente: 'Ainda nao e seu momento, Herdeira.'\n" PADRAO);
    }
    printf("\n*****************************************************************\n");

    // Liberação final de memória
    liberar_baralho(baralho_mestre);
    liberar_inventario(inventario_celaena); 
}

// --- FunC'C#o Principal ---
