#define USE_MATH_DEFINES
#include <cmath>
#include "fastMarching.h"
#include "priorite.h"
#include <algorithm>

const int voisin[4][2] = { {-1,0}, {+1,0}, {0,-1}, {0,+1} };

// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float>& D, int x, int y, float& dx, float& dy) {
    // A completer
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y) {
    // A completer
    return D(x,y);
}

// Fast Marching: carte de distance a partir des points de niv0, qui sont a
// distance 0 par definition.
Image<float> fastMarching(const Image<float>& W, const vector<PointDist>& niv0){
    const int w=W.width(), h=W.height();

    // Initialisation
    Image<float> D(w,h); D.fill(INF);
    Image<bool>  E(w,h); E.fill(false);
    FilePriorite F;
    // A completer

    return D;
}

// Affiche en couleur l'image des distances.
// bleu=0, rouge=maximum, vert=infini
void affiche(const Image<float>& I) {
    Image<float> D=I.clone();
    for(int i=0; i<D.height(); i++)
        for(int j=0; j<D.width(); j++)
            if(D(j,i)==INF)
                D(j,i)=-1.0f;
    float M = *max_element(D.begin(), D.end());
    M = max(1.0f,M);
    Image<Color> B(D.width(), D.height());
    for(int i=0; i<D.height(); i++)
        for(int j=0; j<D.width(); j++) {
            if(D(j,i)>=0) {
                float angle=M_PI/2*D(j,i)/M;
                B(j,i) = Color(byte(255*sin(angle)), 0, byte(255*cos(angle)));
            }
            else B(j,i) = GREEN;
        }
    display(B);
}
