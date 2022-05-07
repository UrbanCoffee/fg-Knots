#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct knot_fg {
    int crossing, // f or g crossings
        x, y, z;  // strands. X is overstrand. Y is incoming strand. Z is outgoing strand.
};

typedef std::vector<int*> Kmtrx;
typedef std::vector<knot_fg> crossings;

//typedef std::vector<knot_fg> crossings;

crossings read(char*);
Kmtrx build(crossings);
void printMtrx(const Kmtrx *);
void hprintMtrx(const Kmtrx *);
void clear(Kmtrx *);


#endif