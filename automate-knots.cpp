#include <iostream>
#include "knot.h"
#include "rrem.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Too few arguments.\n");
        printf("Use the following template: ./knot <#knot-id> <#prime>\n");
        return 1;
    }
    set_p(atoi(argv[2]));

    crossings test = read(argv[1]);
    if(!test.size()){
        printf("Nothing was read!");
        return 1;
    }

    Kmtrx knot_mtx;
    int prime = get_p();
    for(int b = 1; b+2 < prime; ++b){
        set_b(b);
        
        knot_mtx = build(&test);
    
        printf("b = (%d)\tp = %d\n\n", b, prime);
        rrem(knot_mtx, prime, knot_mtx.size()-1);
        hprintMtrx(&knot_mtx);
        printf("\n");

        clear(&knot_mtx);
    }

    return 0;
}