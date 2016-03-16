#include "priorite.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int n = 15;

int main() {
    srand((unsigned int) time(0));
    vector<PointDist> v;
    for (int i = 0; i < n; i++) {
        v.push_back(PointDist(i, 0, double(i)));
    }

    FilePriorite Phil;
    FilePriorite PhilTriee;

    for (int i = 0; i < n; i++) {
        Phil.push(v[i]);
    }

    for (int i = 1; i < Phil.v.size(); i++) {
        cout << Phil.v[i].dist << endl;
    }

    cout << "" << endl;
    cout << Phil.v.size() << endl;
    cout << "" << endl;

    PointDist a(0, 0, 0);

    for (int i = 1; i < n; i++) {
        a = Phil.pop();
        cout << a.dist << endl;
        PhilTriee.push(a);
    }

    for (int i = 1; i < PhilTriee.v.size(); i++) {
        cout << PhilTriee.v[i].dist << endl;
    }

    return 0;
}
