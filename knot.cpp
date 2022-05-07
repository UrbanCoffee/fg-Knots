#include "knot.h"

static int numStrds; //set during build() when the number of crossings is known
static int b;
static int p;
static std::vector<int> primes;

void set_b(int _b){ b = _b; }
void set_p(int _p){ p = _p; }
int get_b(){ return b; }
int get_p(){ return p; }

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

int attemptToOpen(FILE **f, std::string fn) {
    if( !(*f = fopen(fn.c_str(), "r")) ){
        if( !( *f = fopen(("Knots/" + fn + ".txt").c_str(), "r") ) ){
            return 0;
    }}

    return 1;
}

crossings read(char *fn) {
    if(!fn){
        printf("ERROR: Passed NULL to read().\n");
        exit(1);
    }

    FILE *fp;
    if(!attemptToOpen(&fp, fn)){
        printf("Could not open \"%s\". \n", fn);
        exit(1);
    }

    char line[100];
    crossings List;
    knot_fg crx;
    char *str1[100], *str2[100];
    while(fgets(line, sizeof(line), fp)){

        if(sscanf(line, "Knot = %s\n", &str1) == 1){
            printf("Knot = %s\n", str1);
        }

        else if(sscanf(line, "Primes = %[^\n]\n", &str2) == 1){
            printf("Primes = %s\n", str2);
        }

        else if(sscanf(line, "%c(%c,%c,%c)", &crx.crossing, &crx.x, &crx.y, &crx.z) == 4){
            List.push_back(crx);
        }
    }

    fclose(fp);
    return List;
}

Kmtrx build(crossings* crx) {
    Kmtrx mtrx;

    numStrds = crx->size(); //numStrds is global
    for(unsigned int i = 0; i < numStrds; ++i){
        knot_fg c = (*crx)[i];
        if(c.crossing == 'f'){
           mtrx.push_back( f(c.x, c.y, c.z) );
        }
        else if (c.crossing == 'g'){
            mtrx.push_back( g(c.x, c.y, c.z) );
        }
        else {
            printf("BAD CROSSING!");
            exit(1);
        }
    }

    return mtrx;
}

void printMtrx(const Kmtrx *m){
    unsigned int size = m->size();
    for(unsigned int k = 0; k < size; ++k){
        printf("\t");
        for(int j = 0; j + 1 < size; ++j)
            printf("%3d, ", (*m)[k][j]);
        
        printf("%3d\n", (*m)[k][size-1]);
    }
}
void hprintMtrx(const Kmtrx *m){
    unsigned int size = m->size();
    for(unsigned int k = 0; k < size-1; ++k){
        printf("\t");
        for(int j = 0; j + 2 < size; ++j)
            printf("%3d, ", (*m)[k][j]);
        
        printf("%3d\n", (*m)[k][size-2]);
    }
}

void clear(Kmtrx *mtrx){
    for(int i = 0; i < mtrx->size(); ++i)
        delete[] (*mtrx)[i];

    mtrx->clear();
}