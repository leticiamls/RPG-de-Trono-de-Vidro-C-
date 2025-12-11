#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/combate.h"
#include "../include/inventario.h"

// ======================== CORES ANSI ============================
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

// ====================== CONSTANTES ============================
#define LEVE 1
#define PESADO 2
#define DEFENDER 3
#define ESQUIVAR 4
extern void aplicar_magia_fae(Character *player);

// ====================== FUNÇÕES BÁSICAS ============================

void push_combate(QueueCombate* q, Character* p, int action){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    new_node->ref = p;
    new_node->action = action;
    new_node->next = NULL;

    if(q->rear == NULL){
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
}

Node* pop_combate(QueueCombate* q){
    if(q->front == NULL) return NULL;
    Node* temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    return temp;
}

void free_queue_combate(QueueCombate* q) {
    Node* temp;
    while ((temp = pop_combate(q)) != NULL) {
        free(temp);
    }
}

int calcularDano(int base, float mult) {
    int res = (int)(base * mult);
    if (res < 0) res = 0;
    return res;
}

// ====================== LÓGICA DE COMBATE ============================

//0 = Derrota (Fim), 1 = Vitória (Continua), 2 = Retry (Repete loop)
int iniciar_batalha(Character* player, Character* enemy) {
    QueueCombate turnos = {NULL, NULL};
    int rodada = 1;
    
    printf(CYAN "\n============================================\n");
    printf("       BATALHA INICIADA: VS %s", enemy->name);
    printf("\n============================================\n" RESET);

    push_combate(&turnos, player, LEVE); 

    while(player->health > 0 && enemy->health > 0){
        printf(YELLOW "\n=========== RODADA %d ===========\n" RESET, rodada);

        Node* turno = pop_combate(&turnos);
        if (!turno) {
            push_combate(&turnos, player, 0);
            turno = pop_combate(&turnos);
        }
        Character* atual = turno->ref;
        Character* inimigo = (atual == player ? enemy : player);

        int acao = turno->action;       
        int acaoInimigo = 0;           

        // ---------------- TURNO DO JOGADOR ----------------
        if(atual == player) {
            if (acao == 0) { 
                printf(BLUE "\nE seu turno! Escolha sua acao:\n" RESET);
                printf("1 - Atacar Leve\n");
                printf("2 - Defender\n");
                printf("3 - Esquivar\n");
                printf("4 - Inventario (Usar itens)\n");
                
                int escolha;
                int inputValido = 0;
                while(!inputValido) {
                    printf("> ");
                    if (scanf("%d", &escolha) != 1) {
                        while(getchar() != '\n');
                    } else {
                        if (escolha >= 1 && escolha <= 4) inputValido = 1; 
                    }
                }
                switch(escolha) {
                    case 1: acao = LEVE; break;
                    case 2: acao = DEFENDER; break;
                    case 3: acao = ESQUIVAR; break;
                    case 4:{
                            printf("HP %s: %d / %d\n", player->name, player->health, player->max_health);
                            
                            int item_index = open_inventory_menu(&player->inventory);
                            if (item_index > 0) {
                                Item *selected_item = &player->inventory.items[item_index - 1];

                                if (selected_item->type == ITEM_TYPE_CONSUMABLE) {
                                    player->health += selected_item->heal_amount;
                                    if (player->health > player->max_health) player->health = player->max_health;
                                    
                                    // Remover o item
                                    remove_item(&player->inventory, selected_item->name, 1); 
                                    printf(GREEN "Você usou %s e se curou! HP atual: %d/%d\n" RESET, selected_item->name, player->health, player->max_health);
                                    continue; 
                                    
                                } else if (selected_item->type == ITEM_TYPE_BUFF) {
                                    aplicar_magia_fae(player);
                                    continue; 
                                }
                            }
                            continue;
                    }
                }
            if(acao == LEVE) acaoInimigo = (rand() % 4) + 1; 
            }
        }
        // ---------------- TURNO DO INIMIGO ----------------
        else {
            acao = (rand() % 2) + 1; 
            
            // --- MENSAGENS DE IMPACTO ---
            if(acao == LEVE) {
                printf("\n%s>>> %s AVANCA RAPIDO! <<<%s\n", RED, enemy->name, RESET);
            } else {
                printf(RED "\n>>> CUIDADO! %s CARREGA UM ATAQUE PESADO! <<<\n" RESET, enemy->name);
            }

            printf(BLUE "Como voce reage?\n" RESET);
            printf("1 - Atacar Leve (Troca de dano)\n");
            printf("2 - Defender\n");
            printf("3 - Esquivar\n");
            
            int escolha;
            int inputValido = 0;
            while(!inputValido) {
                printf("> ");
                if (scanf("%d", &escolha) != 1) {
                    while(getchar() != '\n');
                } else {
                    if (escolha >= 1 && escolha <= 3) inputValido = 1;
                }
            }
            switch(escolha) {
                case 1: acaoInimigo = LEVE; break;
                case 2: acaoInimigo = DEFENDER; break;
                case 3: acaoInimigo = ESQUIVAR; break;
            }
        }

        // ---------------- CÁLCULO DE DANO ----------------
        int danoAtacante = 0;
        int danoInimigo = 0;

        if (acao == LEVE) danoAtacante = calcularDano(atual->attack, 1.0f);
        else if (acao == PESADO) danoAtacante = calcularDano(atual->attack, 1.5f);

        if (acaoInimigo == LEVE) danoInimigo = calcularDano(inimigo->attack, 1.0f);
        else if (acaoInimigo == PESADO) danoInimigo = calcularDano(inimigo->attack, 1.5f);

        // ---------------- REGRAS ----------------
        
        // Contra-Ataque
        if(acao == PESADO && acaoInimigo == ESQUIVAR){
            printf(GREEN "%s esquivou perfeitamente e CONTRA-ATACA!\n" RESET, inimigo->name);
            int contra = calcularDano(inimigo->attack, 1.10f);
            atual->health -= contra;
            printf(RED "%s recebeu %d de dano critico!\n" RESET, atual->name, contra);
        }
        else if(acaoInimigo == PESADO && acao == ESQUIVAR){
            printf(GREEN "%s esquivou perfeitamente e CONTRA-ATACA!\n" RESET, atual->name);
            int contra = calcularDano(atual->attack, 1.10f);
            inimigo->health -= contra;
            printf(RED "%s recebeu %d de dano critico!\n" RESET, inimigo->name, contra);
        }
        else {
            // Dano Normal
            int danoFinalInimigo = danoAtacante - inimigo->defesa;
            if (danoFinalInimigo < 0) danoFinalInimigo = 0;
            
            int danoFinalAtual = danoInimigo - atual->defesa;
            if (danoFinalAtual < 0) danoFinalAtual = 0;

            if(acao == LEVE){
                if(acaoInimigo == DEFENDER) danoFinalInimigo = 0; 
                else if(acaoInimigo == ESQUIVAR) danoFinalInimigo = (int)(danoFinalInimigo * 0.5f);
            } else if(acao == PESADO){
                if(acaoInimigo == DEFENDER) danoFinalInimigo = (int)(danoFinalInimigo * 0.75f);
                else if(acaoInimigo == ESQUIVAR) danoFinalInimigo = 0; 
            }

            if(acaoInimigo == LEVE){
                if(acao == DEFENDER) danoFinalAtual = 0;
                else if(acao == ESQUIVAR) danoFinalAtual = (int)(danoFinalAtual * 0.5f);
            } else if(acaoInimigo == PESADO){ 
                if(acao == DEFENDER) danoFinalAtual = (int)(danoFinalAtual * 0.75f);
                else if(acao == ESQUIVAR) danoFinalAtual = 0; 
            }

            // --- PRINTS DE DANO COMPLETOS ---
            if(danoFinalInimigo > 0) {
                inimigo->health -= danoFinalInimigo;
                if(acao == LEVE && acaoInimigo == ESQUIVAR)
                    printf(CYAN "A esquiva falhou! %s sofreu %d de dano!\n" RESET, inimigo->name, danoFinalInimigo);
                else
                    printf(RED "%s recebeu %d de dano!\n" RESET, inimigo->name, danoFinalInimigo);
            } else if (danoAtacante > 0) {
                printf(GREEN "%s defendeu o ataque!\n" RESET, inimigo->name);
            }

            if(danoFinalAtual > 0) {
                atual->health -= danoFinalAtual;
                if(acaoInimigo == LEVE && acao == ESQUIVAR)
                    printf(CYAN "A esquiva falhou! %s sofreu %d de dano!\n" RESET, atual->name, danoFinalAtual);
                else
                    printf(RED "%s recebeu %d de dano!\n" RESET, atual->name, danoFinalAtual);
            } else if (danoInimigo > 0) {
                printf(GREEN "%s defendeu o ataque!\n" RESET, atual->name);
            }
        }

        if (player->health < 0) player->health = 0;
        if (enemy->health < 0) enemy->health = 0;

        printf(GREEN "\nHP %s: %d\n" RESET, player->name, player->health);
        printf(RED "HP %s: %d\n" RESET, enemy->name, enemy->health);

        free(turno);
        push_combate(&turnos, inimigo, 0); 
        rodada++;
    }

    free_queue_combate(&turnos);

    if(player->health > 0){
        printf(GREEN "\n>>> VITORIA! %s caiu. <<<\n" RESET, enemy->name);
        return 1; 
    }
    
    printf(RED "\n========================================\n");
    printf("        DERROTA... %s venceu.", enemy->name);
    printf("\n========================================\n" RESET);
    printf("1 - Tentar Novamente\n");
    printf("2 - Desistir\n> ");
    
    int opcao;
    scanf("%d", &opcao);
    if(opcao == 1) return 2; 
    
    return 0; 
}