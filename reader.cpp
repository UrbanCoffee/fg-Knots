#include "reader.h"
#include <string>

int attemptToOpen(FILE **f, char* fn) {
    if( !(*f = fopen(fn, "r")) ){
        return 0;
    }

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
    char *str1, *str2;
    while(fgets(line, 100, fp)){
        if(sscanf(line, "Knot = %*s", str1, str2)){
            continue;
        }
        else if(sscanf(line, "Primes = %*s", str1, str2)){
            continue;
        }
        else if(sscanf(line, "%c(%c,%c,%c)", &crx.crossing, &crx.x, &crx.y, &crx.z)){
            List.push_back(crx);
        }
    }

    return List;
}