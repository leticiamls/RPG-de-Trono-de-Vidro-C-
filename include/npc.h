#ifndef NPC_H
#define NPC_H
#define COR_LARANJA "\033[0;33m"
#define PADRAO "\x1b[0m"

#define MAX_NPC_NAME_LEN 30

typedef struct {
    char name[MAX_NPC_NAME_LEN];
    int amizade_score;
    int empatia_poder; 
    int health;
    int attack;
} NPC;

NPC* create_npc(const char *name, int amizade_base, int empatia_base);
void display_npc_stats();

extern NPC *g_chaol;
extern NPC *g_dorian;
extern NPC *g_nehemia;

#endif