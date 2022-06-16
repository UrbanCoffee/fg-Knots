#ifndef __MISC_H__
#define __MISC_H__

#include <vector>

struct pair {
    unsigned int x, y;
};

// decomposes an integer into its prime factorization
std::vector<pair> primeFactor(int);

// TODO: Make this a template function with an additional function pointer argument./
// combines two vectors together while ignoring duplicates from the right vector
std::vector<pair> unionVec(const std::vector<pair>&, const std::vector<pair>&);

#endif