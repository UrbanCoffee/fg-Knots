#ifndef RREM_H
#define RREM_H

#include "kdefs.h"

void swap(int *, int*, int); // swaps rows
void inv_row(int *, int);    // multiplies a row by the inverse of the entry at [i,i]
void subtr(int *, int *, int); // left row subtracts into the right row to make the [j,i] entry zero
void rrem(Kmtrx &, int, int);

#endif