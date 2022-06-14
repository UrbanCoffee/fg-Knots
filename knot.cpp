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

crossings read(const char *fn) {
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
            //printf("Knot = %s\n", str1);
        }

        else if(sscanf(line, "Primes = %[^\n]\n", &str2) == 1){
            //printf("Primes = %s\n", str2);
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

void printCx(const crossings *c){
    if(!c){
        printf("Null passed as argument for printCx in knot.cpp.\n");
        return;
    }
    knot_fg cc = (*c)[0];
    for(unsigned i = 0; i < c->size(); cc = (*c)[++i])
        printf("\t%c(%c,%c,%c)\n", cc.crossing, cc.x, cc.y, cc.z);
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

// No-Zero Print Matrix
// Prints the passed-in Knot Matrix but any zeroes are replaced with spaces.
// Does not seperate values with commas.
void nprintMtrx(const Kmtrx *m, unsigned int size){
    int val;
    for(unsigned int k = 0; k < size; ++k){
        printf("\t");
        for(int j = 0; j + 1 < size; ++j){
            val = (*m)[k][j];
            // check if the value assigned to val is non-zero
            (val != 0) ? printf("%3d ", val) : printf("%*s", 4, "") ;
        }
        val = (*m)[k][size-1];
        (val != 0 ) ? printf("%3d\n", val) : printf("\n") ;
        //printf("%3d\n", (*m)[k][size-2]);
    }
}

void clear(Kmtrx *mtrx){
    for(int i = 0; i < mtrx->size(); ++i)
        delete[] (*mtrx)[i];

    mtrx->clear();
}

int KDet_Helper(int** d, unsigned int sz){
    if(!d){
        printf("Null passed as argument for KDet_Helper in knot.cpp.\n");
        return 0;
    }
    if(sz <= 0){ return 0;}
    if(sz == 1){ return d[0][0];}

    int nsz = sz - 1;

    int index;
    int **nd = new int*[nsz];
    for(int i = 0; i<nsz; i++)
        nd[i] = new int[nsz];

    int ret = 0;

    for(int j = 0; j < sz; j++){
        if(d[0][j] == 0)
            continue;

        index = 0;
        for(int i = 1; i < sz; i++){
            for(int j_ = 0; j_ < sz; j_++){
                if (j_ != j)
                    nd[index/nsz][index++%nsz] = d[i][j_];
        }}
                                             // this last bit simulates (-1)^(i)
        ret += d[0][j]*KDet_Helper(nd, sz - 1)*(-1+2*((j+1)%2));
    }

    for(int i = 0; i<nsz; i++)
        delete[] nd[i];
    delete[] nd;

    return ret;
}

int KDet(const crossings *c){
    if(!c){
        printf("Null passed as argument for KDet in knot.cpp.\n");
        return 0;
    }
    // return abs(AlxPlny(c)(-1));

    int ret;

    int sz = c->size();
    int **nd = new int*[sz];
    for(int i = 0; i<sz; i++)
        nd[i] = new int[sz];
    for(int i = 0; i<sz; i++){
        for(int j = 0; j<sz; j++)
            nd[i][j] = 0;
    }

    knot_fg cx;
    for(int i = 0; i<sz; i++){
        cx = (*c)[i];
        nd[i][cx.x - 'a'] = 2;
        nd[i][cx.y - 'a'] = -1;
        nd[i][cx.z - 'a'] = -1;
    }

    ret = abs(KDet_Helper(nd, sz-1));

    for(int i = 0; i<sz; i++)
        delete[] nd[i];
    delete[] nd;

    return ret;
}

crossings ksum(const crossings *k1, const crossings *k2){
    // First size-1 entries will be the same in sum and k1
    crossings sum = *k1;
    sum.pop_back(); // add it back later
    unsigned int newSize = k1->size() + k2->size();
    // Need to add new understand sequence in sum
    int offset = k1->size() - 1;
    char curChar = 'a' + offset;

    knot_fg ncx;
    for(unsigned int i = 0; i < k2->size(); ++i){
        ncx = (*k2)[i];

        if(ncx.x == 'a')
            ncx.x = 'a' + newSize - 1;
        else
            ncx.x +=  offset;

        ncx.y = curChar++;
        ncx.z = curChar;

        sum.push_back(ncx);
    }
    ncx = k1->back();
    ncx.y = curChar;
    ncx.z = 'a';
    sum.push_back(ncx);

    return sum;
}

bool isTrivial(const Kmtrx* km, unsigned int sz){
    for(unsigned row  = 0; row < sz; ++row){
        for(unsigned col = 0; col < sz; ++col){
            if(row != col && (*km)[row][col])
                return false;
        }
    }

    return true;
}