#include <iostream>
#include <vector>
//#include <fstream>

int a, b, c;            // want to iterate different valid combinations of these
const int p = 5;        // knot specific. keep const
const int numStrds = 8; // ''

int* f(char, char, char);
int* g(char, char, char);

int main() {
    a = 3; b = 1; c = 2;

    std::vector<int*> mat;

    mat.push_back( g('a', 'e', 'f') );
    mat.push_back( g('f', 'a', 'b') );
    mat.push_back( f('b', 'c', 'd') );
    mat.push_back( f('h', 'b', 'c') );
    mat.push_back( f('c', 'h', 'a') );
    mat.push_back( g('d', 'g', 'h') );
    mat.push_back( g('g', 'd', 'e') );
    mat.push_back( g('e', 'f', 'g') );

    printf("(a,b,c) = (%d,%d,%d)\tp = %d\n\n", a,b,c,p);
    for(unsigned int k = 0; k < mat.size(); ++k){
        printf("\t");
        for(int j = 0; j + 1 < numStrds; ++j)
            printf("%3d, ", mat[k][j]);
        
        printf("%3d\n", mat[k][numStrds -1]);
    }
    printf("\n");

    for(int i = 0; i < mat.size(); ++i)
        delete[] mat[i];

    return 0;
}

int* f(char x, char y, char z){
    int x_ = x - 'a',
        y_ = y - 'a',
        z_ = z - 'a';
    int *out = new int[numStrds];

    for(int i = 0; i < numStrds; ++i)
        out[i] = 0;

    out[x_] = a % p;
    out[y_] = b % p;
    out[z_] = (-(a+b) ) % p;

    return out;
}

int* g(char x, char y, char z){
    int *out = f(x,z,y);

    for(int i = 0; i < numStrds; ++i)
        out[i] = (c*out[i]) % p;

    return out;
}
