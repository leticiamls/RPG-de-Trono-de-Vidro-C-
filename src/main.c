#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    printf("Bem-vindo ao RPG Trono de Vidro!\n");
    printf("==================================\n");
    
    // Inicializa o jogo
    if (initialize_game() != 0) {
        fprintf(stderr, "Erro ao inicializar o jogo.\n");
        return 1;
    }

    // Loop principal do jogo
    run_game_loop();

    // Finaliza o jogo
    cleanup_game();

    printf("Obrigado por jogar!\n");
    return 0;
}
