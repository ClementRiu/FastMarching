#define USE_MATH_DEFINES

#include <cmath>
#include "fastMarching.h"
#include "priorite.h"
#include <algorithm>

const int voisin[4][2] = {{-1, 0},
                          {+1, 0},
                          {0,  -1},
                          {0,  +1}};

/*
// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float> &D, int x, int y, float &dx, float &dy) {
    int w=D.width();
    int h=D.height();
    float Dp[4];
    for (int k=0; k<4; k++){
        int ip= x+voisin[k][0];
        int jp = y+voisin[k][1];
        if (ip>=0 && ip<w && jp>=0 && jp<h){
            Dp[k]=D(ip,jp);
        }
        else{
            Dp[k]=INF;
        }
    }
    dx=min(Dp[0],Dp[1]);
    dy=min(Dp[2],Dp[3]);
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y) {
    float Dxy,dx,dy;
    minVoisins(D,x,y,dx,dy);
    float deter=2*pow(W(x,y),2)-pow(dx-dy,2);
    if (dx!=INF && dy != INF && deter >=0){
        Dxy=(dx+dy+sqrt(deter))/2.0f;
    }
    else {
        Dxy=min(dx,dy)+W(x,y);
    }
    return Dxy;
}


// Fast Marching: carte de distance a partir des points de niv0, qui sont a
// distance 0 par definition.
Image<float> fastMarching(const Image<float> &W, const vector<PointDist> &niv0) {
    const int w = W.width(), h = W.height();
    int i;
    int j;
    // Initialisation
    Image<float> D(w, h);
    D.fill(INF);
    Image<bool> E(w, h);
    E.fill(false);
    FilePriorite F;
    for (int k=0; k < (niv0.size()); k++){
        PointDist point=niv0[k];
        F.push(point);
        i=point.i;
        j=point.j;
        D(i,j)=0;
        E(i,j)=true;
    }
    cout<<"Lancement de Fast_Marching..."<<endl;
    while (!F.empty()){
        PointDist point=F.pop();
        for (int k=0; k<4; k++){
            int ip= point.i+voisin[k][0];
            int jp = point.j+voisin[k][1];
            if (ip>=0 && ip<w && jp>=0 && jp<h){
                if(!E(ip,jp)) {
                    D(ip, jp) = calcDistance(D, W, ip, jp);
                    E(ip, jp) = true;
                    PointDist point2(ip, jp, -D(ip, jp));
                    F.push(point2);
                }
            }
        }
    }
    cout << "fait !" << endl;
    return D;
}
*/
// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float>& D, int x, int y, float& dx, float& dy) {
    const int w=D.width(), h=D.height();

// Tableau qui stocke les D(i,j) des quatre voisins
    float Dvois[4];
    for (int k=0; k<4; ++k){
        int X = x + voisin[k][0];
        int Y = y + voisin[k][1];
// Si jamais on est en coin, cela permet de ne traiter que les points qui existent
        if (0 <= X && X < w && 0 <= Y && Y < h){
            Dvois[k] = D(X,Y);
        }
// S'il n'existe pas, on met la valeur INF
        else{
            Dvois[k] = INF;
        }
    }

    dy = min(Dvois[3], Dvois[2]);
    dx = min(Dvois[1], Dvois[0]);
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y) {
    float d2, d1, dxy;
    minVoisins(D, x, y, d2, d1);
    float det = 2*W(x, y)*W(x, y) - (d1-d2)*(d1-d2);
    if (d1 != INF && d2 != INF && det >= 0){
        dxy = (0.5f)*(d1 + d2 + sqrt(det));
    }

    else{
        dxy = min(d1, d2) + W(x, y);
    }

    return dxy;
}

Image<float> fastMarching(const Image<float>& W, const vector<PointDist>& niv0){
    const int w=W.width(), h=W.height();

// Initialisation
    Image<float> D(w,h); D.fill(INF);
    Image<bool> E(w,h); E.fill(false);
    FilePriorite F;
    for (int k=0; k<niv0.size(); ++k){
        F.push(niv0[k]);
        D(niv0[k].i, niv0[k].j) = 0;
        E(niv0[k].i, niv0[k].j) = true;
    }

    cout << "fastMarching en cours ..." << endl;

// Boucle principale
    while(!F.empty()){
        PointDist p = F.pop();
        for (int k=0; k<4; ++k){
            int x = p.i + voisin[k][0];
            int y = p.j + voisin[k][1];
// Si jamais on est en coin, cela permet de ne traiter que les points qui existent et qui n'ont pas ete visite
            if (0<=x && x<w && 0<=y && y<h && !E(x,y)){
                D(x, y) = calcDistance(D, W, x, y);
                E(x, y) = true;
                PointDist q(x, y, -D(x,y));
                F.push(q);
            }
        }
    }
    cout << "fait !" << endl;
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
