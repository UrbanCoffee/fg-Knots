#include <iostream>
#include "reader.h"

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Too few arguments.");
        return 1;
    }

    crossings test = read(argv[1]);
    for(int i = 0; i < test.size(); ++i){
        printf("%c(%c,%c,%c)\n", test[i].crossing, test[i].x, test[i].y, test[i].z);
    }

    return 0;
}