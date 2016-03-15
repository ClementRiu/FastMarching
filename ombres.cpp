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
    // A completer

    cout << "Cliquez la position de la source lumineuse" << endl;
    vector<PointDist> v;
    // A completer

    // Remplissage des cartes de cout avec et sans obstacles
    Image<float> Wavec(w,h), Wsans(w,h);
    Wavec.fill(1.0f); Wsans.fill(1.0f);
    // A completer

    cout << "Calcul" << endl;
    Image<float> Davec = fastMarching(Wavec, v);
    Image<float> Dsans = fastMarching(Wsans, v);
    // A completer

    endGraphics();
    return 0;
}
