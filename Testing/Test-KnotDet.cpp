#include <iostream>
#include "../knot.h"

void knotDetTest(const char*, int);

int main(){

    knotDetTest("3_1", 3);
    knotDetTest("4_1", 5);
    knotDetTest("7_2", 11);
    knotDetTest("7_5", 17);
    knotDetTest("7_6", 19);
    knotDetTest("8_5", 21);
    knotDetTest("8_6", 23);
    knotDetTest("8_7", 23);
    knotDetTest("8_8", 25);
    knotDetTest("8_13", 29);
    knotDetTest("8_14", 31);
    knotDetTest("8_15", 33);
    knotDetTest("8_16", 35);
    knotDetTest("8_17", 37);
    knotDetTest("9_4", 21);
    knotDetTest("9_8", 31);
    knotDetTest("9_23", 45);
    knotDetTest("9_25", 47);

    return 0;
}

void knotDetTest(const char* c, int exp){
    crossings test = read(c);
    if(test.empty()){
        printf("Nothing was read!\n");
        return;
    }
    printf("Running %s expecting %d: \t", c, exp);
    int result = KDet(&test);
    if(result == exp)
        printf("PASSED\n");
    else
        printf("FAILED. Got %d instead.\n", result);

    return;
}