#include <iostream>
#include "knot.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Too few arguments.\n");
        printf("Use the following template: ./knot <#knot1-id> <#knot2-id> ...\n");
        return -1;
    }

    crossings knotSum = read(argv[1]);
    if(knotSum.empty()){
        printf("Nothing was read from  %s!\n", argv[1]);
        return 1;
    }

    crossings knot;
    for(int i = 2; i < argc; ++i){
        knot = read(argv[i]);
        if(knot.empty()){
            printf("Nothing was read from %s!\n", argv[i]);
            return 1;
        }

        knotSum = ksum(&knotSum, &knot);
    }

    if(knotSum.empty()){
        printf("An error has occured with the knot sum.\n");
        printf("Knot sum is of size 0.\n");
        return 1;
    }

    printf("Knot Sum Det: %d\n", KDet(&knotSum));

    //Kmtrx knot_mtx;
    /*for(){
        for(){

        }
    }*/

    return 0;
}