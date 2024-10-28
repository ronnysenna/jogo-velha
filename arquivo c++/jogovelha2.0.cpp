#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Fun��o para mostrar o tabuleiro
void mostrarTabuleiro(char tabuleiro[3][3]) {
	
    printf("\n\t===================");
    printf("\n\t   JOGO DA VELHA   ");
    printf("\n\t===================");
    
    for (int l = 0; l < 3; l++) {
        printf("\n\n\t");
        for (int c = 0; c < 3; c++) {
            printf("[%c]\t", tabuleiro[l][c]);
        }
    }

    printf("\n");
    printf("\n\t===================");
    printf("\n\t   FACULDADE CDL   ");
    printf("\n\t===================");
}

// Fun��o para verificar se h� um vencedor
char verificarVencedor(char tabuleiro[3][3]) {
    // Verifica��o de linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return tabuleiro[i][0];  // Vencedor na linha
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return tabuleiro[0][i];  // Vencedor na coluna
    }

    // Verifica��o das diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return tabuleiro[0][0];  // Diagonal principal
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return tabuleiro[0][2];  // Diagonal secund�ria

    return ' ';  // Nenhum vencedor ainda
}

// Fun��o para verificar se o tabuleiro est� cheio (empate)
bool tabuleiroCheio(char tabuleiro[3][3]) {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (tabuleiro[l][c] == ' ')
                return false;  // H� espa�o livre
        }
    }
    return true;  // Tabuleiro cheio
}

int main(int argc, char** argv) {
    char tabuleiro[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    int l = -1, c = -1;
    char vencedor = ' ';

    srand(time(0));

    // Loop do jogo, continua enquanto n�o houver vencedor ou empate
    while (vencedor == ' ' && !tabuleiroCheio(tabuleiro)) {
        // Jogada da m�quina
        printf("\n\n\tJOGADA DA MAQUINA\n");
        do {
            l = rand() % 3;
            c = rand() % 3;
        } while (tabuleiro[l][c] != ' ');
        tabuleiro[l][c] = 'x';

        // Mostra o tabuleiro ap�s a jogada da m�quina
        mostrarTabuleiro(tabuleiro);

        // Verifica se a m�quina venceu
        vencedor = verificarVencedor(tabuleiro);
        if (vencedor != ' ' || tabuleiroCheio(tabuleiro)) break;  // Verifica se h� vencedor ou empate

        // Jogada do usu�rio
        printf("\n\n\tJOGADA DO USUARIO\n");
        do {
            printf("\n\t === Escolha a linha [0-2]: ");
            scanf("%d", &l);
            printf("\n\t === Escolha a coluna [0-2]: ");
            scanf("%d", &c);
            if (tabuleiro[l][c] != ' ')
                printf("\n\n\t Posicao invalida, tente novamente.\n");
        } while (tabuleiro[l][c] != ' ');
        tabuleiro[l][c] = 'o';

        // Mostra o tabuleiro ap�s a jogada do usu�rio
        mostrarTabuleiro(tabuleiro);

        // Verifica se o usu�rio venceu
        vencedor = verificarVencedor(tabuleiro);
    }

    // Mostra o resultado do jogo
    if (vencedor == 'x') {
        printf("\n\n\t A maquina venceu!\n");
    } else if (vencedor == 'o') {
        printf("\n\n\t Voce venceu!\n");
    } else {
        printf("\n\n\t Empate!\n");
    }

    return 0;
}

