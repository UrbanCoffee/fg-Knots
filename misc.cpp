#include "misc.h"

// short list of primes. Null terminated array
const int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,
                       41,43,47,53,59,61,67,71,73,79,83,
                       89,97,  0};

std::vector<pair> primeFactor(int N) {
    std::vector<pair> pF;
    // pair.x will be used for primes. pair.y for frequency
    pair pf;

    for(unsigned int i = 0; primes[i] && N > 1; ++i){
        if(N % primes[i] == 0){
            pf.x = primes[i];
            pf.y = 0;
            while(N % pf.x == 0){
                N /= pf.x;
                pf.y++;
            }
            pF.push_back(pf);
        }
    }

    return pF;
}

std::vector<pair> unionVec(const std::vector<pair>& V1, const std::vector<pair>& V2) {
    std::vector<pair> ret;
    pair p;
    int i1 = 0, i2 = 0;

    while(i1 < V1.size() && i2 < V2.size()){
        if(V1[i1].x == V2[i2].x){
            p.x = V1[i1].x;
            p.y = V1[i1++].y + V2[i2++].y;
        }
        else if (V1[i1].x < V2[i2].x)
            p = V1[i1++];
        else
            p = V2[i2++];
        ret.push_back(p);
    }
    while(i1 < V1.size())
        ret.push_back(V1[i1++]);
    while(i2 < V2.size())
        ret.push_back(V2[i2++]);

    return ret;
}