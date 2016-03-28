#include "fastMarching.h"
#include <iostream>

const int w=512, h=512;
const float TOL=0.1f; // Seuil de tolerance d'imprecision numerique

// Selection a la souris d'un rectangle.
bool selectionRect(int& x1, int& y1, int& x2, int& y2, const Image<Color>& I) {
    Event e;
    do {
        getEvent(0, e);
        if(e.type==EVT_BUT_ON) {
            x1 = x2 = e.pix[0];
            y1 = y2 = e.pix[1];
            if(e.button==3)
                return false;
        }
        if(e.type==EVT_MOTION) {
            x2 = e.pix[0];
            y2 = e.pix[1];
            display(I);
            fillRect(std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2),
                     RED);
        }
    } while(e.type!=EVT_BUT_OFF || abs(x1-x2)<5 || abs(y1-y2)<5);
    if(x1>x2) std::swap(x1,x2);
    if(y1>y2) std::swap(y1,y2);
    return true;
}

int main() {
    openWindow(w, h);
    Image<Color> I(w,h);
    I.fill(WHITE);

    cout << "Dessinez des rectangles, clic droit pour terminer" << endl;
    int x1, y1, x2, y2;
    while (selectionRect(x1,y1,x2,y2,I)){
        for (int i=x1; i<x2;i++){
            for (int j=y1; j<y2; j++){
                I(i,j)=RED;
            }
        }
    }


    cout << "Cliquez la position de la source lumineuse" << endl;
    vector<PointDist> v;
    int x,y;
    getMouse(x,y);
    while (I(x,y)==RED){
        getMouse(x,y);
    }
    fillCircle(x, y, 2, GREEN);
    PointDist p(x,y,0.f);
    v.push_back(p);

    // Remplissage des cartes de cout avec et sans obstacles
    Image<float> Wavec(w,h), Wsans(w,h);
    Wavec.fill(1.0f); Wsans.fill(1.0f);
    for (int i=0; i<w;i++){
        for (int j=0; j<h; j++){
            if (I(i,j)==RED){
                Wavec(i,j)=INF;
            }
        }
    }

    cout << "Calcul" << endl;
    Image<float> Davec = fastMarching(Wavec, v);
    Image<float> Dsans = fastMarching(Wsans, v);
    // A completer
    for (int i=0; i<w; i++){
        for (int j=0; j<h;j++){
            if (I(i,j)==WHITE && Davec(i,j)-Dsans(i,j)>TOL ){
                I(i,j)==BLUE;
            }
        }
    }
    display(I);

    endGraphics();
    return 0;
}
