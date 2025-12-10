#include <stdio.h>
#include <string.h>
#include "../include/inventario.h"

void init_inventory(Inventory *inv) {
    inv->count = 0;
}

int add_item(Inventory *inv, const char *name, int qty, int heal_amount, int type) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            inv->items[i].quantity += qty;
            return 1;
        }
    }

    if (inv->count >= MAX_INVENTORY) return 0;

    strncpy(inv->items[inv->count].name, name, MAX_ITEM_NAME);
    inv->items[inv->count].quantity = qty;
    inv->items[inv->count].heal_amount = heal_amount;
    inv->items[inv->count].type = type;
    inv->count++;

    return 1;
}

int remove_item(Inventory *inv, const char *name, int qty) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            if (inv->items[i].quantity < qty) return 0;

            inv->items[i].quantity -= qty;

            if (inv->items[i].quantity == 0) {
                inv->items[i] = inv->items[inv->count - 1];
                inv->count--;
            }
            return 1;
        }
    }
    return 0;
}

int use_item(Inventory *inv, const char *name) {
    // 1. Procura o item
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            
            // 2. Armazena o valor de cura/buff para retorno
            int effect_value = inv->items[i].heal_amount;
            int item_type = inv->items[i].type;

            // 3. Se for consumível, remove. Se for buff, apenas retorna o valor (depende da lógica)
            // Para Buff/Fae, não faz nada com a quantidade aqui.
            if (item_type == ITEM_TYPE_CONSUMABLE) {
                 remove_item(inv, name, 1);
            }
            // 4. Retorna um código que o chamador (combate.c) interpretará
            return effect_value; 
        }
    }
    return 0; // Item não encontrado
}

void show_inventory(Inventory *inv) {
    printf("\n========= INVENTARIO =========\n");

    if (inv->count == 0) {
        printf("Inventario vazio.\n");
        return;
    }

    for (int i = 0; i < inv->count; i++) {
        printf("%d - %s (x%d)\n",
            i + 1,
            inv->items[i].name,
            inv->items[i].quantity
        );
    }
}

int open_inventory_menu(Inventory *inv) { 
    int choice;
    while (1) {
        show_inventory(inv);
        printf("Escolha um item para usar (0 para sair): ");
        // Limpeza de buffer necessária (como recomendado anteriormente)
        if (scanf("%d", &choice) != 1) {
            printf("Opção invalida. Digite um numero.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (choice == 0) return 0; // Sai

        if (choice >= 1 && choice <= inv->count) {
             return choice; // Sai do menu após usar um item com sucesso
        }
    }
}
