#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_handler.h"
#include "../include/character.h"

// ================= Savepoints =================

int save_game(const Character *player) {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo de save");
        return -1;
    }

    if (fwrite(player, sizeof(Character), 1, file) != 1) {
        perror("Erro ao escrever dados de save");
        fclose(file);
        return -1;
    }

    printf("\n*** Jogo salvo com sucesso em %s ***\n", SAVE_FILE);
    fclose(file);
    return 0;
}

Character* load_game() {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        return NULL;
    }

    Character *player = (Character *)malloc(sizeof(Character));
    if (player == NULL) {
        perror("Erro ao alocar memória para carregar o personagem");
        fclose(file);
        return NULL;
    }

    if (fread(player, sizeof(Character), 1, file) != 1) {
        free(player);
        player = NULL;
    }

    fclose(file);
    return player;
}

// ================= Configurações =================

int save_config(int volume, int difficulty) {
    FILE *file = fopen(CONFIG_FILE, "w");
    if (file == NULL) {
        perror("Erro ao abrir arquivo de configuração");
        return -1;
    }

    fprintf(file, "volume=%d\n", volume);
    fprintf(file, "difficulty=%d\n", difficulty);

    printf("Configurações salvas em %s\n", CONFIG_FILE);
    fclose(file);
    return 0;
}

int load_config(int *volume, int *difficulty) {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file == NULL) {
        *volume = 50;
        *difficulty = 1;
        return -1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "volume=")) {
            sscanf(line, "volume=%d", volume);
        } else if (strstr(line, "difficulty=")) {
            sscanf(line, "difficulty=%d", difficulty);
        }
    }

    printf("Configurações carregadas de %s\n", CONFIG_FILE);
    fclose(file);
    return 0;
}
