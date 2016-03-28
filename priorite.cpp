#include "priorite.h"
#include <iostream>

using namespace std;

// Ajoute un element
void FilePriorite::push(PointDist d) {
    int i = v.size();
    v.push_back(d);

    // On replace le point où il faut, selon si ses parents sont plus petits et ceux jusqu'au début:
    while (v[i / 2] < v[i] && i / 2 > 0) {
        swap(v[i / 2], v[i]);
        i = i / 2;
    }
}

// Retire un element
PointDist FilePriorite::pop() {
    PointDist p = v[1];
    v[1] = v.back();
    v.pop_back();

    if (!empty()) {
        int i = 1;

        // On continue s'il y a deux enfants, s'il y en a un plus grand, et s'il y a qu'un enfant, s'il est plus grand.
        while (((2 * i + 1 < v.size()) && (v[i] < v[2 * i] || v[i] < v[2 * i + 1])) ||
               ((2 * i < v.size()) && (v[i] < v[2 * i]))) {

            // On vérifie s'il y a deux enfants :
            if (2 * i + 1 < v.size()) {
                // Dans le cas ou les deux sont plus grands :
                if (v[i] < v[2 * i] && v[i] < v[2 * i + 1]) {
                    // on cherche le plus grand des deux.
                    if (v[2 * i] < v[2 * i + 1]) {
                        swap(v[i], v[2 * i + 1]);
                        i = 2 * i + 1;
                    }
                    else {
                        swap(v[i], v[2 * i]);
                        i = 2 * i;
                    }
                }
                else {
                    if (v[i] < v[2 * i]) {
                        swap(v[i], v[2 * i]);
                        i = 2 * i;
                    }
                    else {
                        swap(v[i], v[2 * i + 1]);
                        i = 2 * i + 1;
                    }
                }
            }

            else {
                swap(v[i], v[2 * i]);
            }
        }

    }
    return p;
}

FilePriorite::FilePriorite() {
    PointDist v(0, 0, 0);

    push(v);
};

bool FilePriorite::empty() {
    if (v.size() > 0) {
        return (false);
    }
    else {
        return (true);
    }
}