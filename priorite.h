#pragma once
#include <vector>
#include "pointDist.h"

class FilePriorite {
    std::vector<PointDist> v;
public:
    void push(PointDist d);
    PointDist pop();
};
