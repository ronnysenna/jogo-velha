#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Função para mostrar o tabuleiro
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

// Função para verificar se há um vencedor
char verificarVencedor(char tabuleiro[3][3]) {
    // Verificação de linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return tabuleiro[i][0];  // Vencedor na linha
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return tabuleiro[0][i];  // Vencedor na coluna
    }

    // Verificação das diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return tabuleiro[0][0];  // Diagonal principal
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return tabuleiro[0][2];  // Diagonal secundária

    return ' ';  // Nenhum vencedor ainda
}

// Função para verificar se o tabuleiro está cheio (empate)
bool tabuleiroCheio(char tabuleiro[3][3]) {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (tabuleiro[l][c] == ' ')
                return false;  // Há espaço livre
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

    // Loop do jogo, continua enquanto não houver vencedor ou empate
    while (vencedor == ' ' && !tabuleiroCheio(tabuleiro)) {
        // Jogada da máquina
        printf("\n\n\tJOGADA DA MAQUINA\n");
        do {
            l = rand() % 3;
            c = rand() % 3;
        } while (tabuleiro[l][c] != ' ');
        tabuleiro[l][c] = 'x';

        // Mostra o tabuleiro após a jogada da máquina
        mostrarTabuleiro(tabuleiro);

        // Verifica se a máquina venceu
        vencedor = verificarVencedor(tabuleiro);
        if (vencedor != ' ' || tabuleiroCheio(tabuleiro)) break;  // Verifica se há vencedor ou empate

        // Jogada do usuário
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

        // Mostra o tabuleiro após a jogada do usuário
        mostrarTabuleiro(tabuleiro);

        // Verifica se o usuário venceu
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

