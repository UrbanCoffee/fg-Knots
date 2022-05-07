#include <iostream>
#include <stdlib.h>
#include <vector>
//#include <fstream>

int b;                  // want to iterate different valid combinations of these
int p;                  //prime
const int numStrds = 8; // knot specific. Change for different number of knot strands

void printMtrx(const std::vector<int*> *);
void hprintMtrx(const std::vector<int*> *);
void clear(std::vector<int*> *);
std::vector<int*> rre(const std::vector<int*>);

int* f(char, char, char);
int* g(char, char, char);

int main(int argc, char* argv[]) {
    if(argc > 1) p = atoi(argv[1]);
    else{
        printf("Please enter an integer argument when executing script.");
        return 1;
    }

    for(b = 1; b < p-2; ++b){
        std::vector<int*> mat;

        mat.push_back( g('d', 'a', 'b') );
        mat.push_back( g('g', 'b', 'c') );
        mat.push_back( g('a', 'c', 'd') );
        mat.push_back( g('c', 'd', 'e') );
        mat.push_back( g('h', 'e', 'f') );
        mat.push_back( g('e', 'f', 'g') );
        mat.push_back( g('b', 'g', 'h') );
        mat.push_back( g('f', 'h', 'a') );


        printf("b = (%d)\tp = %d\n\n", b, p);
        //printMtrx(&mat);
        hprintMtrx(&mat);
        printf("\n");

        clear(&mat);
    }

    return 0;
}

int* f(char x, char y, char z){
    int x_ = x - 'a',
        y_ = y - 'a',
        z_ = z - 'a';
    int *out = new int[numStrds];

    for(int i = 0; i < numStrds; ++i)
        out[i] = 0;

    out[x_] = 2;
    out[y_] = b % p;
    out[z_] = (((-(b+2) ) % p) + p ) % p;

    return out;
}

int* g(char x, char y, char z){
    return f(x,z,y);
}

void clear(std::vector<int*> *mtrx) {
    for(int i = 0; i < mtrx->size(); ++i)
        delete[] (*mtrx)[i];

    mtrx->clear();
}

void printMtrx(const std::vector<int*> *mtrx){
    for(unsigned int k = 0; k < mtrx->size(); ++k){
        printf("\t");
        for(int j = 0; j + 1 < numStrds; ++j)
            printf("%3d, ", (*mtrx)[k][j]);
        
        printf("%3d\n", (*mtrx)[k][numStrds-1]);
    }
}

void hprintMtrx(const std::vector<int*> *mtrx) {
    for(unsigned int k = 0; k < mtrx->size()-1; ++k){
        printf("\t");
        for(int j = 0; j + 2 < numStrds; ++j)
            printf("%3d, ", (*mtrx)[k][j]);
        
        printf("%3d\n", (*mtrx)[k][numStrds-2]);
    }
}