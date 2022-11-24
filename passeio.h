#ifndef PASSEIO_TP
#define PASSEIO_TP
#include <stdio.h>


int verify(int Cnxt_house,int Rnxt_house,int board[8][8]){
    return (Cnxt_house >= 0) && (Cnxt_house < 8) && (Rnxt_house >= 0) && (Rnxt_house < 8) && (board[Cnxt_house][Rnxt_house] == 0);
}

int bestmovements(int C_move[8], int R_move[8],int Cnxt_house,int Rnxt_house, int board[8][8]){
        int v[8];

    for(int i = 0; i < 8; i++){
        int count = 0;
        if(verify(Cnxt_house + C_move[i], Rnxt_house + R_move[i], board)){
            for(int j = 0; j < 8; j++){
                count += verify(Cnxt_house + C_move[i] + C_move[j], Rnxt_house + R_move[i] + R_move[j], board);
            }
        }
        else{
            count = 9;
        }
        v[i] = count;
    }
    int menor = v[0];
    int idx = 0;

    for(int i = 1; i < 8; i++){
        if(v[i] < menor){
            menor = v[i];
            idx = i;
        }
    }
    return idx;
}
int tour(int board[8][8], int C_first, int R_first,int idx, int C_move[8], int R_move[8], long long int*visited_houses, long long int*backtraking){
    

    //condição de parada 
    if(idx > 64){
        return 1;
    }
    // andar do cavalo
    *visited_houses = *visited_houses + 1;
    int Bmove = bestmovements(C_move,R_move,C_first,R_first,board);
    board[C_first + C_move[Bmove]][R_first + R_move[Bmove]] = idx;
    return tour(board, C_first + C_move[Bmove],R_first + R_move[Bmove], idx+1, C_move, R_move, visited_houses, backtraking);
}
void passeio(int x, int y){
    long long int visited_houses = 1;
    long long int backtraking = 0;
    int board[8][8];
    int idx = 2;
    int C_move[8] = {1, 1, -1, -1, 2, 2, -2, -2};
    int R_move[8] = {2, -2, 2, -2, 1, -1, 1, -1};

    FILE* saida = fopen("saida.txt", "a");

    for(int i= 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = 0;
        }
    }

    board[x - 1][y - 1] = 1;
    
    tour(board,x - 1, y - 1,idx,C_move,R_move,&visited_houses,&backtraking);
    for(int i= 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] >= 10){
                fprintf(saida, "%d ", board[i][j]);
            }else{
                fprintf(saida, " %d ", board[i][j]);
            }
        }
        fprintf(saida, "\n");
    }
    
    fprintf(saida, "%lld\n", visited_houses);
    fprintf(saida, "%lld\n", backtraking);

    fclose(saida);
}

#endif