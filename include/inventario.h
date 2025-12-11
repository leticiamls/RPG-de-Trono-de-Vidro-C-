#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEM_NAME 50
#define MAX_INVENTORY 30

#define ITEM_TYPE_CONSUMABLE 0
#define ITEM_TYPE_BUFF 1

typedef struct {
    char name[MAX_ITEM_NAME];
    int quantity;
    int heal_amount;
    int type;
} Item;

typedef struct {
    Item items[MAX_INVENTORY];
    int count;
} Inventory;

// Inicialização
void init_inventory(Inventory *inv);

// Manipulação
int add_item(Inventory *inv, const char *name, int qty, int heal_amount, int type);
int remove_item(Inventory *inv, const char *name, int qty);

// Utilização
int use_item(Inventory *inv, const char *name); 

// Interface
void show_inventory(Inventory *inv); 
int open_inventory_menu(Inventory *inv);

#endif
