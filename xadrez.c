// ==================================================================
// Desafio de Xadrez - MateCheck
// Versão 2.5 - Melhorias na estrutura e legibilidade do código.
// Objetivo: deixar o código mais organizado, legível e fácil de entender, mantendo a funcionalidade original.
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

// Codificação dos tipos de movimento.
typedef enum {
    MOV_CIMA,
    MOV_BAIXO,
    MOV_ESQUERDA,
    MOV_DIREITA
} TipoMovimento;



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
    memset(matriz, 0, sizeof(Tabuleiro)); // Zera toda a estrutura do tabuleiro.
}

void mover_peca(Tabuleiro *matriz, Casa **peca, TipoMovimento movimento) {
    
    // Calcula a posição de peça
    int pos_linear = *peca - &matriz->casas[0][0];
    int linha = pos_linear / 8;
    int coluna = pos_linear % 8;

    // Calcula a posição de destino
    switch (movimento) {
        case MOV_CIMA: linha--; break;
        case MOV_BAIXO: linha++; break;
        case MOV_ESQUERDA: coluna--; break;
        case MOV_DIREITA: coluna++; break;
    }
    Casa *destino = &matriz->casas[linha][coluna];
    
    *destino = **peca; // Copia o conteudo de peça para destino.
    **peca = (Casa) {PECA_NULL, COR_NULL}; // Zera a origem.
    *peca = destino; // Atualiza o ponteiro de peça para a nova localização.
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
    Casa *peca; // Ponteiro para a peça.
    
    // Torre
    imprimir_titulo("Torre");
    inicializar_tabuleiro(&matriz);

    peca = &matriz.casas[0][0];
    *peca = (Casa) { PECA_TORRE, COR_PRETO }; 

    imprimir_tabuleiro(&matriz);
    for (int i = 0; i < 5; i++) {
        mover_peca(&matriz, &peca, MOV_DIREITA);
        imprimir_tabuleiro(&matriz);
    }


    // Bispo
    imprimir_titulo("Bispo");
    inicializar_tabuleiro(&matriz);

    peca = &matriz.casas[7][0];
    *peca = (Casa) { PECA_BISPO, COR_PRETO }; 

    imprimir_tabuleiro(&matriz);

    int i = 0;
    while (i < 5) {
        mover_peca(&matriz, &peca, MOV_CIMA);
        mover_peca(&matriz, &peca, MOV_DIREITA);
        imprimir_tabuleiro(&matriz);
        i++;
    }


    // Rainha
    imprimir_titulo("Rainha");
    inicializar_tabuleiro(&matriz);

    peca = &matriz.casas[0][7];
    *peca = (Casa) { PECA_DAMA, COR_PRETO }; 

    imprimir_tabuleiro(&matriz);

    i = 7;
    do {
        mover_peca(&matriz, &peca, MOV_ESQUERDA);
        imprimir_tabuleiro(&matriz);
        i--;
    } while (i > 0);


    // Cavalo
    imprimir_titulo("Cavalo");
    inicializar_tabuleiro(&matriz);

    peca = &matriz.casas[4][4];
    *peca = (Casa) { PECA_CAVALO, COR_PRETO };

    imprimir_tabuleiro(&matriz);
    for (int i = 0; i < 3; i++) {
        while (i < 2) {
            mover_peca(&matriz, &peca, MOV_CIMA);
            imprimir_tabuleiro(&matriz);
            i++;
        }
        mover_peca(&matriz, &peca, MOV_ESQUERDA);
        imprimir_tabuleiro(&matriz);
    }

    return 0;
}
