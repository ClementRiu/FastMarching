#pragma once

#include <vector>
#include "pointDist.h"

using namespace std;

class FilePriorite {
public:
    vector<PointDist> v;

public:
    void push(PointDist d);

    PointDist pop();

    FilePriorite();

    bool empty();
};
