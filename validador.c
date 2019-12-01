#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "validador.h"
#include "xadrez.h"

int valida_jogada(char *jogadaAtual, matriz_t * m, int cor_adversario) {
    identifica_peca(jogadaAtual, m, cor_adversario);
    return 1;
}


/*funcao para identificar peca de acordo com o primeiro caractere*/
void identifica_peca(char *jogadaAtual, matriz_t * m, int cor_peca) {
    char c = jogadaAtual[0]; //o primeiro caractere vai identificar qual a peca
    
    int linha, coluna, movimento;


    if(cor_peca == 99)
        printf("\nBrancas jogam!\n");
    else
        printf("\nPretas jogam!\n");


    //chama a funcao para identificar o movimento da jogadaAtual
    movimento = identifica_movimento(jogadaAtual); 

    linha = gera_linha(jogadaAtual, movimento);
    coluna = gera_coluna(jogadaAtual, movimento);


    if (islower(c)) { //identifica o PEAO
        mover_peao(m, coluna, linha, cor_peca, movimento, jogadaAtual);
        
    } else {

        switch(c) {
            case 'R': //identifica a TORRE
                mover_torre(m, coluna, linha, cor_peca, movimento, jogadaAtual);
                break;

            case 'N': //identifica o CAVALO
                mover_cavalo(m, coluna, linha, cor_peca, movimento, jogadaAtual);
                break;

            case 'B': //identifica o BISPO
                mover_bispo(m, coluna, linha, cor_peca, movimento, jogadaAtual);
                break;

            case 'K': //identifica o REI
                mover_rei(m, coluna, linha, cor_peca, movimento, jogadaAtual);
                break;

            case 'Q': //identifica a RAINHA
                mover_rainha(m, coluna, linha, cor_peca, movimento, jogadaAtual);
                break;

            case 'O': //identifica o movimento ROQUE
                if(jogadaAtual[3] == '-') {
                    roque_maior(m, cor_peca);
                    break;
                }
                roque_menor(m, cor_peca);
                break;

            default:
                printf("A peca eh ivalida.\n");
                exit(1);                
        }
    }
}


int identifica_movimento(char *jogadaAtual) {
    /*
        retorna 1 se o movimento for normal
        retorna 2 se o mov for amb coluna
        retorna 3 se o mov for amb linha     
        retorna 4 se o mov for captura
        retorna 5 se o mov for captura amb coluna
        retorna 6 se o mov for captura amb linha
        retorna 7 se o mov for captura com promocao de peao
        retorna 8 se o mov for normal com promocao de peao
    */
   char c0, c1, c2, c3, c4, c5;

    c0 = jogadaAtual[0];
    c1 = jogadaAtual[1];
    c2 = jogadaAtual[2];
    c3 = jogadaAtual[3];
    c4 = jogadaAtual[4];
    c5 = jogadaAtual[5];

    if(islower(c0)) { //SE A JOGADA FOR DE PEAO
        if(c2 == '=') //se eh um movimento tipo b8=R
            return 8;
        else if(c4 == '=') //se eh um movimento tipo cxb1=Q
            return 7;
        else if(isdigit(c1)) //se eh um movimento tipo e4
            return 1;
        else if(c1 == 'x')  //se eh um movimento tipo exd5
            return 4;
      
    }

    else {
        if(isdigit(c2)) { //entao eh tipo Nh3 ou Kd5
            return 1;
        }
        else if(isdigit(c3)) {
            if(c1 == 'x') //caso em que Nxd3
                return 4;
            else if(isdigit(c1)) //caso em que N4f7
                return 3;
            else if(islower(c1)) //caso em que Ncd3
                return 2;
        }
        else if(isdigit(c4)) {
            if(isdigit(c1) && c2 == 'x') //caso em que N4xf7
                return 6;
            else if(islower(c1) && c2 == 'x') //caso em que Ncxd3
                return 5;
        }
    }

}




int gera_linha(char *jogadaAtual, int movimento) {
    int linha, i = 0;

    if(movimento == 3)  //N3f7
        i = 3;
    if(movimento == 6)  //N4xg4
        i = 4;

    if(i == 0) {
        while(!isdigit(jogadaAtual[i])) {
            i++;
        } 
    }

    printf("Linha: %c\n", jogadaAtual[i]);
    linha = '8' - jogadaAtual[i]; 

    return linha;
}


int gera_coluna(char *jogadaAtual, int movimento) {
    int coluna, i = 0;

    if(movimento == 3) //N3f7    Ngg5   R8b7 
        i = 2;
    if(movimento == 6) //N4xg4
        i = 3;

    if(i == 0) {
        while(!isdigit(jogadaAtual[i])) {
            i++;
        }
        i--;
    }

    printf("Coluna: %c\n\n", jogadaAtual[i]);
    coluna = (jogadaAtual[i] - 'a');
  
    return coluna;
}