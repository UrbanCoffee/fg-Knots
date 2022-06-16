#include <iostream>
#include "knot.h"

int main(int argc, char *argv[]){
    // KnotSum takes at least two knots
    if(argc < 3){
        printf("Too few arguments.\n");
        printf("Use the following template: ./knot <#knot1-id> <#knot2-id> ...\n");
        return -1;
    }

    std::vector<pair> primeCadidates;

    // Set the first knot as the base for the knot sum.
    crossings knotSum = read(argv[1]);
    if(knotSum.empty()){
        printf("Nothing was read from  %s!\n", argv[1]);
        return 1;
    }
    primeCadidates = primeFactor( KDet(&knotSum) );

    // Add the remaining knots one at a time to the base knot (knotSum).
    // Exit if an error occurs.
    crossings knot;
    for(int i = 2; i < argc; ++i){
        knot = read(argv[i]);                                   // read from file
        if(knot.empty()){                                       // check if read was successful
            printf("Nothing was read from %s!\n", argv[i]);
            return 1;
        }
        primeCadidates = unionVec(primeCadidates, primeFactor(KDet(&knot)));

        knotSum = ksum(&knotSum, &knot);                        // add knot to knotSum
    }

    // extra error check
    if(knotSum.empty()){
        printf("An error has occured with the knot sum.\n");
        printf("Knot sum is of size 0.\n");
        return 1;
    }

    //printf("Knot Sum Det: %d\n", KDet(&knotSum));

    printf("Primes: ");
    for(int i = 0; i < primeCadidates.size(); ++i)
        printf("%d ", primeCadidates[i].x);
    printf("\r\n");

    Kmtrx knotSum_mtx;
    int prime;
    bool allTrivial = true;
    for(int pIndex = 0; pIndex < primeCadidates.size(); pIndex++){
        prime = primeCadidates[pIndex].x;
        set_p(prime);

        for(int b = 1; b+2 < prime; ++b){
            set_b(b);
        
            knotSum_mtx = build(&knotSum);
        
            rrem(knotSum_mtx, prime, knotSum_mtx.size()-1);
            if(!isTrivial(&knotSum_mtx, knotSum_mtx.size()-1)){
                allTrivial = false;
                printf("b = (%d)\tp = %d\n\n", b, prime);
                nprintMtrx(&knotSum_mtx, knotSum_mtx.size()-1);
                printf("\n");
            }

            clear(&knotSum_mtx);
        }
    }

    if(allTrivial){
        printf("All trivial.\n");
    }

    return 0;
}