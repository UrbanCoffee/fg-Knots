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

crossings read(char*);
Kmtrx build(crossings*);
void printCx(const crossings *);
void printMtrx(const Kmtrx *);
void hprintMtrx(const Kmtrx *);
void nprintMtrx(const Kmtrx *, unsigned int);
void clear(Kmtrx *);

crossings ksum(const crossings*, const crossings*);
bool istrivial(const Kmtrx*, unsigned int);

#endif