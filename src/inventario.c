#include <stdio.h>
#include <string.h>
#include "inventario.h"

void init_inventory(Inventory *inv) {
    inv->count = 0;
}

int add_item(Inventory *inv, const char *name, int qty, int heal_amount) {
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

int use_item(Inventory *inv, const char *name, int *player_hp, int max_hp) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {

            if (inv->items[i].heal_amount <= 0) {
                printf("Este item não pode ser usado agora.\n");
                return 0;
            }

            *player_hp += inv->items[i].heal_amount;
            if (*player_hp > max_hp) *player_hp = max_hp;

            printf("Você usou %s e recuperou %d HP!\n",
                   name, inv->items[i].heal_amount);

            remove_item(inv, name, 1);
            return 1;
        }
    }
    return 0;
}

void show_inventory(Inventory *inv) {
    printf("\n========= INVENTÁRIO =========\n");

    if (inv->count == 0) {
        printf("Inventário vazio.\n");
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

void open_inventory_menu(Inventory *inv, int *player_hp, int max_hp) {
    int choice;

    while (1) {
        show_inventory(inv);
        printf("\nHP atual: %d / %d\n", *player_hp, max_hp);
        printf("Escolha um item para usar (0 para sair): ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice < 1 || choice > inv->count) {
            printf("Opção inválida.\n");
            continue;
        }

        Item *selected = &inv->items[choice - 1];
        use_item(inv, selected->name, player_hp, max_hp);
        break;
    }
}
