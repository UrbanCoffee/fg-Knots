#include <iostream>
#include "rrem.h"

static int *inv;
static int P; // global - used in most functions

int* initInv(int);
void clearInv(int *);

void rrem(Kmtrx &arr, int p, int nS){
    P = p;
    inv = initInv(p);

    // row reduce echelon with modulo p
    for(int i = 0; i < nS; ++i){
        // if arr[i][i] is 0, swap with other lower row
        if(arr[i][i] == 0){
            for(int j = i+1; j < nS; ++j){
                if(arr[j][i]){
                    swap(arr[j], arr[i], nS);
                    break;
        }}}


        //multiple row i with the mult. inverse of arr[i][i]
        inv_row(arr[i], nS);

        // subtract all other rows with row i
        for(int j = 0; j < nS; ++j){
            if( j != i )
                subtr(arr[i], arr[j], nS);
        }
        
    }

    clearInv(inv);

    return;
}

void swap(int *r, int *nr, int len){
    if(!r || !nr){
        printf("Passed NULL pointer to swap().\n");
        exit(1);
    }
    
    int temp;

    for(int i = 0; i < len; ++i){
        temp = r[i];
        r[i] = nr[i];
        nr[i] = temp;
    }
}

void inv_row(int *row, int len){
    if(!row){
        printf("Passed NULL pointer to inv_row().\n");
        exit(1);
    }

    int inverse;
    int i;
    for(i = 0; i < len; ++i){
        if(row[i]){
            inverse = inv[row[i]];
            break;
        }
    }

    for(int j = i; j < len; ++j)
        row[j] = (row[j] * inverse) % P; 

}

void subtr(int *er, int *sr, int len){
    if(!er || !sr){
        printf("Passed NULL pointer to subtr().\n");
        exit(1);
    }

    int i;
    for(i = 0; i < len; ++i){
        if(er[i]) break;
    }

    for(int j = len-1; j >= i; --j)
        sr[j] = sr[j] - er[j]*sr[i];

    for(int j = i; j < len; ++j)
        sr[j] = ( (sr[j] % P) + P ) % P;
}

int* initInv(int p) {
    int *inverse = new int[p];

    for(int i = 0; i < p; ++i)
        inverse[i] = 0;

    for(int i = 1; i < p; ++i){
        if(inverse[i] == 0){
            for(int j = 1; j < p; ++j){
                if((i*j-1) % p == 0){
                    inverse[i] = j;
                    inverse[j] = i;
    }}}}

    return inverse;
}

void clearInv(int *inverse){
    if(inverse)
        delete[] inverse;
    inverse = NULL;
}