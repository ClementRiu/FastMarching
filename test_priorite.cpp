#include "priorite.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

const int n=20;

int main() {
    std::srand((unsigned int)std::time(0));
    std::vector<PointDist> v;
    for(int i=0; i<n; i++)
        v.push_back( PointDist(i,0, (double)i) );
    // A completer
    return 0;
}
