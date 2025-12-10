#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEM_NAME 50
#define MAX_INVENTORY 30

typedef struct {
    char name[MAX_ITEM_NAME];
    int quantity;
    int heal_amount;  // quanto cura, 0 caso não seja consumível
} Item;

typedef struct {
    Item items[MAX_INVENTORY];
    int count;
} Inventory;

// Inicialização
void init_inventory(Inventory *inv);

// Manipulação
int add_item(Inventory *inv, const char *name, int qty, int heal_amount);
int remove_item(Inventory *inv, const char *name, int qty);

// Utilização
int use_item(Inventory *inv, const char *name, int *player_hp, int max_hp);

// Interface
void show_inventory(Inventory *inv);
void open_inventory_menu(Inventory *inv, int *player_hp, int max_hp);

#endif
