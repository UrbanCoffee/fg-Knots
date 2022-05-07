#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

struct knot_fg {
    char crossing, // f or g crossings
        x, y, z;  // strands. X is overstrand. Y is incoming strand. Z is outgoing strand.
};

typedef std::vector<int*> Kmtrx;
typedef std::vector<knot_fg> crossings;

void set_b(int);
void set_p(int);
int get_b();
int get_p();

int* f(char, char, char);
int* g(char, char, char);

crossings read(char*);
Kmtrx build(crossings*);
void printMtrx(const Kmtrx *);
void hprintMtrx(const Kmtrx *);
void clear(Kmtrx *);


#endif