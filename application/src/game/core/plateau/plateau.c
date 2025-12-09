#include "plateau.h"

Plateau *Plateau_create() {


    Plateau *plat = (Plateau *)calloc(1, sizeof(Plateau));
    AssertNew(plat);

    plat->plate = (int ** ) calloc(5,sizeof(char));
    for(int i=0; i<5 ; i++){
        plat->plate[i] = (int * )calloc(4,sizeof(char));
    }

    return plat;
}


void Print_plateau(Plateau *plate){

    assert(plate != NULL);

    for( int i=0 ; i<5; i ++){
        for( int j=0 ; j<4 ; j ++){
            printf("%c",plate->plate[i][j]);
        }
        printf("\n");
    }
}
