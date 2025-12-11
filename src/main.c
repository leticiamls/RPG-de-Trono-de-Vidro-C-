#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "data_structures.h"

// gcc -Iinclude src/*.c -o trono.exe

int main() {
    printf("%s%s====================================\n", NEGRITO, COR_MAGENTA);
    printf("= Bem-vindo ao RPG Trono de Vidro! =\n");
    printf("====================================%s\n", PADRAO);
    
    if (initialize_game() != 0) {
        fprintf(stderr, "Erro ao inicializar o jogo.\n");
        return 1;
    }

    // Loop principal do jogo
    run_game_loop();

    // Finaliza o jogo
    cleanup_game();

    printf("%s%sObrigado por jogar!%s\n", NEGRITO, COR_VERDE, PADRAO);
    return 0;
}
