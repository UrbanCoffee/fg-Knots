#ifndef KDEFS_H
#define KDEFS_H

#include <vector>

struct knot_fg {
    char crossing, // f or g crossings
        x, y, z;  // strands. X is overstrand. Y is incoming strand. Z is outgoing strand.
};

typedef std::vector<int*> Kmtrx;
typedef std::vector<knot_fg> crossings;

#endif