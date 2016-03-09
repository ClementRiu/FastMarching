#include "priorite.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int n = 27;

int main() {
    srand((unsigned int) time(0));
    vector<PointDist> v;
    for (int i = 0; i < n; i++) {
        v.push_back(PointDist(i, 0, double(i)+0.5));
    }

    FilePriorite Phil;

    for (int i = 0; i< n ; i++){
        Phil.push(v[i]);
    }

    for (int i=1; i<Phil.v.size(); i++) {
        cout << Phil.v[i].dist << endl;
    }

    cout<<""<<endl;
    cout<<Phil.v.size()<<endl;
    cout<<""<<endl;

    PointDist dernier = Phil.pop();
    cout<<""<<endl;
    cout<<dernier.dist<<endl;
    cout<<""<<endl;

    cout<<Phil.v.size()<<endl;


    for (int i=1; i<Phil.v.size(); i++) {
        cout << Phil.v[i].dist << endl;
    }

    return 0;
}
