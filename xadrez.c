// ==================================================================
// Desafio de Xadrez - MateCheck
// Versão 2.0 - Nível aventureiro
// Objetivo: utilizar estruturas de repetição aninhadas para simular o movimento do cavalo (um L).
// ==================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

// Estilos de texto (ANSI)
#define NEGRITO "\033[1m"
#define BG_BRANCO "\033[47m"
#define BG_PRETO "\033[40m"
#define RESET "\033[0m"

// Codificação do tipo de peça.
typedef enum {
    PECA_NULL = 0,
    PECA_PEAO,
    PECA_TORRE,
    PECA_BISPO,
    PECA_CAVALO,
    PECA_DAMA,
    PECA_REI
} TipoPeca;

// Codificação da cor da peça.
typedef enum {
    COR_NULL = 0,
    COR_PRETO,
    COR_BRANCO
} Cor;

// Estrutura de cada casa.
typedef struct {
    TipoPeca status;
    Cor cor; 
} Casa;

// Estrutura do tabuleiro, basicamente uma matriz de casas;
typedef struct {
    Casa casas[8][8];
} Tabuleiro;



/* ========================== Utilitários ========================== */

void limpar_tela() {
    system("cls || clear");
}

void imprimir_titulo (char *titulo) {
    limpar_tela();
    printf("\n\n\n\n\n\n %20s%s%20s", NEGRITO, titulo, RESET);
    sleep(2);
}

const char *casa_para_simbolo(Casa *casa) {
    const char *pecas_brancas[] = { " ", "♙", "♖", "♗", "♘", "♕", "♔" };
    const char *pecas_pretas[] = { " ", "♟", "♜", "♝", "♞", "♛", "♚" };
    
    return (casa->cor == COR_BRANCO) ? pecas_brancas[casa->status] : pecas_pretas[casa->status];
}


/* ========================== Funcionalidades ========================== */


void inicializar_tabuleiro(Tabuleiro *matriz) {
    for (int linha = 0; linha < 8; linha++) {
        for (int coluna = 0; coluna < 8; coluna++) {
            matriz->casas[linha][coluna] = (Casa) {PECA_NULL, COR_NULL};
        }
    }
}

void mover_peca(Casa *origem, Casa *destino) {
    *destino = *origem; // Copia origem para destino.
    *origem = (Casa) {PECA_NULL, COR_NULL}; // Zera a origem.
}

void imprimir_tabuleiro(Tabuleiro *matriz) {
    limpar_tela();

    for (int linha = 0; linha < 8; linha++) {
        for (int altura = 0; altura < 3; altura++) {
            int altura_central = (altura == 1);

            // Imprime o numero das linhas.
            (altura_central) ? printf(" %i ", linha + 1) : printf("   "); 

            for (int coluna = 0; coluna < 8; coluna++) {
                const char *cor_casa = ((coluna + linha) % 2) ? BG_PRETO : BG_BRANCO;
                const char *simbolo = (altura_central) ? casa_para_simbolo(&matriz->casas[linha][coluna]) : " ";

                printf("%s   %s   %s", cor_casa, simbolo, RESET);
            } 
            puts("");
        }
    }

    // Imprime a letra das colunas.
    printf("   ");
    for (char letra = 'a'; letra <= 'h'; letra++) 
        printf("   %c   ", letra); 
    puts("");

    sleep(2);
}



/* ========================== Função Principal ========================== */


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    Tabuleiro matriz;

    
    // Torre
    imprimir_titulo("Torre");

    inicializar_tabuleiro(&matriz);
    matriz.casas[0][0] = (Casa) { PECA_TORRE, COR_PRETO };
    imprimir_tabuleiro(&matriz);

    for (int i = 0; i < 5; i++) {
        Casa *origem = &matriz.casas[0][i];
        Casa *destino = &matriz.casas[0][i + 1]; // vai para direita

        mover_peca(origem, destino);
        imprimir_tabuleiro(&matriz);
    }


    // Bispo
    imprimir_titulo("Bispo");

    inicializar_tabuleiro(&matriz);
    matriz.casas[7][0] = (Casa) { PECA_BISPO, COR_PRETO };
    imprimir_tabuleiro(&matriz);

    int linha = 7;
    int coluna = 0;

    while (coluna < 5) {
        Casa *origem = &matriz.casas[linha][coluna];
        Casa *destino = &matriz.casas[--linha][++coluna]; // sobe e vai para direita

        mover_peca(origem, destino);
        imprimir_tabuleiro(&matriz);
    }


    // Rainha
    imprimir_titulo("Rainha");

    inicializar_tabuleiro(&matriz);
    matriz.casas[0][7] = (Casa) { PECA_DAMA, COR_PRETO };
    imprimir_tabuleiro(&matriz);

    int i = 7;
    do {
        Casa *origem = &matriz.casas[0][i];
        Casa *destino = &matriz.casas[0][--i]; // vai para esquerda

        mover_peca(origem, destino);
        imprimir_tabuleiro(&matriz);
    } while (i > 0);


    // Cavalo
    imprimir_titulo("Cavalo");

    inicializar_tabuleiro(&matriz);
    matriz.casas[4][4] = (Casa) { PECA_CAVALO, COR_PRETO };
    imprimir_tabuleiro(&matriz);

    linha = 4;
    coluna = 4;

    for (int i = 0; i < 3; i++) {
        while (i < 2) {
            Casa *origem = &matriz.casas[linha][coluna];
            Casa *destino = &matriz.casas[++linha][coluna]; // sobe

            mover_peca(origem, destino);
            imprimir_tabuleiro(&matriz);
            i++;
        }
        Casa *origem = &matriz.casas[linha][coluna];
        Casa *destino = &matriz.casas[linha][--coluna]; // vai para esquerda

        mover_peca(origem, destino);
        imprimir_tabuleiro(&matriz);
    }

    return 0;
}
