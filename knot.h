#ifndef KNOT_H
#define KNOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "kdefs.h"
#include "rrem.h"

void set_b(int);
void set_p(int);
int get_b();
int get_p();

int* f(char, char, char);
int* g(char, char, char);

crossings read(const char*);
Kmtrx build(crossings*);
void printCx(const crossings *);
void printMtrx(const Kmtrx *);
void hprintMtrx(const Kmtrx *);
void nprintMtrx(const Kmtrx *, unsigned int);
void clear(Kmtrx *);

int KDet(const crossings*);

crossings ksum(const crossings*, const crossings*);
bool isTrivial(const Kmtrx*, unsigned int);

#endif