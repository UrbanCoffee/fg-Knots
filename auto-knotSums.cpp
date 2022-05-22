#include <iostream>
#include "knot.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Too few arguments.\n");
        printf("Use the following template: ./knot <#knot1-id> <#knot2-id>\n");
        return -1;
    }

    crossings knot1 = read(argv[1]);
    crossings knot2 = read(argv[2]);
    if(knot1.empty() || knot2.empty()){
        printf("Nothing was read from one or both of the knots!\n");
        return 1;
    }

    crossings knotSum = ksum(&knot1, &knot2);
    //printCx(&knotSum);
    if(knotSum.empty()){
        printf("An error has occured with the knot sum.\n");
        printf("Knot sum is of size 0.\n");
        return 1;
    }


    Kmtrx knot_mtx;
    /*for(){
        for(){

        }
    }*/

    return 0;
}