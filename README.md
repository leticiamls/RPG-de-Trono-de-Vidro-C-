# README - RPG Trono de Vidro

## Sumário
1. [Resumo do Projeto](#resumo-do-projeto)
2. [Tecnologias Utilizadas](#tecnologias-utilizadas)
3. [Estrutura do Sistema](#estrutura-do-sistema)
4. [Aprendizados e Desenvolvimento](#aprendizados-e-desenvolvimento)
5. [Como Executar](#como-executar)

---

## Resumo do Projeto
O **Trono de Vidro** é um jogo de RPG (Role-Playing Game) baseado em texto desenvolvido em linguagem C. O projeto simula uma jornada interativa inspirada no universo literário de mesmo nome, onde o jogador navega por diálogos, enfrenta inimigos em um sistema de combate e gere recursos através de um inventário. O jogo utiliza o terminal para exibição de mensagens coloridas e formatadas para aumentar a imersão.

## Tecnologias Utilizadas
* **Linguagem C**: Base de todo o desenvolvimento da lógica e estruturas.
* **Padrão C99**: Utilizado para garantir conformidade e recursos específicos da linguagem.
* **GCC (GNU Compiler Collection)**: Compilador para geração do binário executável.
* **GNU Make**: Ferramenta de automação de compilação para gerir múltiplos ficheiros fonte.

## Estrutura do Sistema
A arquitetura do projeto é modular, separando as responsabilidades em diferentes componentes:
* **Interface e Loop**: O ficheiro `main.c` gere a entrada no jogo e o loop principal de execução.
* **Gestão de Dados**: `data_structures.c` e `character.c` definem como as informações do jogador e do mundo são armazenadas.
* **Sistemas de Jogo**: Inclui módulos específicos para `combate.c`, `inventario.c`, `npc.c` e `minigame.c`.
* **Persistência**: O `file_handler.c` trata da leitura e escrita de ficheiros como `savegame.dat` e `narrativa.dat`.

## Aprendizados e Desenvolvimento
O desenvolvimento deste projeto permitiu a consolidação de conceitos fundamentais de programação:
* **Modularização em C**: Organização de código em cabeçalhos (`.h`) e implementações (`.c`) para facilitar a manutenção.
* **Manipulação de Ficheiros Binários**: Armazenamento de estados complexos de structs em disco para permitir a continuação do jogo.
* **Lógica de Automação (Build)**: Criação de regras de compilação eficientes que recompilam apenas o necessário.
* **Gestão de Memória e Recursos**: Garantia de que o jogo inicializa e finaliza (limpeza) corretamente.

## Como Executar

1. **Compilação**: Utilize o comando `make` na raiz do projeto para gerar o executável `rpg_throne_of_glass`.
2. **Execução**: Rode o programa com `./rpg_throne_of_glass`.
3. **Manutenção**: Use `make clean` para remover ficheiros temporários e saves antigos.
