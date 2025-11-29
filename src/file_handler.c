#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_handler.h"
#include "../include/character.h"

// --- Manipulação de Arquivos (Savepoints) ---

int save_game(const Character *player) {
    FILE *file = fopen(SAVE_FILE, "wb"); // "wb" para escrita binária
    if (file == NULL) {
        perror("Erro ao abrir arquivo de save");
        return -1;
    }

    // Escreve a estrutura Character inteira no arquivo
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
    FILE *file = fopen(SAVE_FILE, "rb"); // "rb" para leitura binária
    if (file == NULL) {
        // Arquivo não existe ou erro de abertura, retorna NULL para novo jogo
        return NULL;
    }

    Character *player = (Character *)malloc(sizeof(Character));
    if (player == NULL) {
        perror("Erro ao alocar memória para carregar o personagem");
        fclose(file);
        return NULL;
    }

    // Lê a estrutura Character inteira do arquivo
    if (fread(player, sizeof(Character), 1, file) != 1) {
        // Erro de leitura ou arquivo vazio
        free(player);
        player = NULL;
    }

    fclose(file);
    return player;
}

// --- Manipulação de Arquivos (Configurações) ---

int save_config(int volume, int difficulty) {
    FILE *file = fopen(CONFIG_FILE, "w"); // "w" para escrita de texto
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
    FILE *file = fopen(CONFIG_FILE, "r"); // "r" para leitura de texto
    if (file == NULL) {
        // Arquivo não existe, usa valores padrão
        *volume = 50;
        *difficulty = 1;
        return -1;
    }

    // Leitura simples de chave=valor
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
