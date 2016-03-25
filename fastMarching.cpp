#define USE_MATH_DEFINES

#include <cmath>
#include "fastMarching.h"
#include "priorite.h"
#include <algorithm>

const int voisin[4][2] = {{-1, 0},
                          {+1, 0},
                          {0,  -1},
                          {0,  +1}};

// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float> &D, int x, int y, float &dx, float &dy) {
    dx = min(D(x, y + 1), D(x, y - 1));
    dy = min(D(x + 1, y), D(x - 1, y));
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y) {
    float dx,dy;
    minVoisins(D,x,y,dx,dy);
    if (dx==INF || dy == INF){
        D(x,y)=min(dx,dy)+W(x,y);
    }
    else {
        if (2*pow(W(x,y),2)-pow(dx-dy,2)<=0){
            D(x,y)=(dx+dy+pow(2*pow(W(x,y),2)-pow(dx-dy,2),0.5))/2;
        }
        else {
            D(x,y)=min(dx,dy)+W(x,y);
        }
    }
    return D(x,y);
}

// Fast Marching: carte de distance a partir des points de niv0, qui sont a
// distance 0 par definition.
Image<float> fastMarching(const Image<float> &W, const vector<PointDist> &niv0) {
    const int w = W.width(), h = W.height();
    PointDist point(0,0,0);
    int i;
    int j;
    // Initialisation
    Image<float> D(w, h);
    D.fill(INF);
    Image<bool> E(w, h);
    E.fill(false);
    FilePriorite F;
    for (int k=1; k < (niv0.size()); k++){
        point=niv0.back();
        F.push(point);
        i=point.i;
        j=point.j;
        D(i,j)=0;
        E(i,j)=true;
    }
    while (!F.empty()){
        point=F.pop();
        i=point.i;
        j=point.j;
        for (int k=-1; k<2; k++){
            for (int l=-1; l<2; l++) {
                if (i+k>=0 && i+k<w){
                    if (j+l>=0 && j+l<h){
                        float Di=calcDistance(D,W,i+k,j+l);
                        E(i+k,j+l)=true;
                        PointDist point2(i+k,j+l,Di);
                        F.push(point2);
                    }
                }
            }
        }
    }
    return D;
}

// Affiche en couleur l'image des distances.
// bleu=0, rouge=maximum, vert=infini
void affiche(const Image<float> &I) {
    Image<float> D = I.clone();
    for (int i = 0; i < D.height(); i++)
        for (int j = 0; j < D.width(); j++)
            if (D(j, i) == INF)
                D(j, i) = -1.0f;
    float M = *max_element(D.begin(), D.end());
    M = max(1.0f, M);
    Image<Color> B(D.width(), D.height());
    for (int i = 0; i < D.height(); i++)
        for (int j = 0; j < D.width(); j++) {
            if (D(j, i) >= 0) {
                float angle = M_PI / 2 * D(j, i) / M;
                B(j, i) = Color(byte(255 * sin(angle)), 0, byte(255 * cos(angle)));
            }
            else B(j, i) = GREEN;
        }
    display(B);
}
