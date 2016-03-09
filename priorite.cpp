#include "priorite.h"
#include <iostream>

using namespace std;

// Ajoute un element
void FilePriorite::push(PointDist d) {
    v.push_back(d);

    int i = v.size() - 1;

    while (v[i / 2] < v[i] && i / 2 > 0) {
        swap(v[i / 2], v[i]);

        i = i / 2;
    }
}

// Retire un element
PointDist FilePriorite::pop() {
    v[0] = v[1];
    v[1] = v.back();

    cout<<v.size()<<endl;

    v.pop_back();

    cout<<v.size()<<endl;

    int i = 1;

    while (v[i] < v[2 * i] || v[i] < v[2 * i + 1]) {
        if (v[i] < v[2 * i] && v[i] < v[2 * i + 1]) {
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

    return v[0];
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