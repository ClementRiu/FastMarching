#include "fastMarching.h"
#include <iostream>


typedef FVector<float, 2> FloatPoint2; // point avec coordonnees float

const int w = 512, h = 512;
const float TAU = 0.8f; // Increment dans la direction opposee au gradient

IntPoint2 arrondi(const FloatPoint2 p) {
    return IntPoint2((int) (p[0] + 0.5f), (int) (p[1] + 0.5f));
}

// Selection a la souris d'un cercle.
bool selectionCercle(int &xc, int &yc, float &r) {
    Color *cols;
    int w, h;
    captureWindow(cols, w, h);
    Image<Color> I(cols, w, h, true);
    Event e;

    do {
        getEvent(0, e);
        if (e.type == EVT_BUT_ON) {
            xc = e.pix[0];
            yc = e.pix[1];
            r = 0;
            if (e.button == 3)
                return false;
        }
        if (e.type == EVT_MOTION) {
            float dx = xc - e.pix[0], dy = yc - e.pix[1];
            r = sqrt(dx * dx + dy * dy);
            display(I);
            drawCircle(xc, yc, (int) (r + 0.5f), GREEN);
        }
    } while (e.type != EVT_BUT_OFF || r < 3.0f);

    return true;
}

// Ajoute poids gaussien a W.
void ajouteGaussienne(Image<float> &W, float xc, float yc, float r) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            W(i, j) += exp(-((i - xc) * (i - xc) + (j - yc) * (j - yc)) / (r * r));
        }
    }
}

// Calcule la geodesique de p1 a p2.
vector<FloatPoint2> geodesique(const Image<float> &D,
                               FloatPoint2 p1, FloatPoint2 p2) {
    vector<FloatPoint2> v;
    v.push_back(p2);
    FloatPoint2 q, grad;
    q = v.back();
    while ((q[0] - p1[0]) * (q[0] - p1[0]) + (q[1] - p1[1]) * (q[1] - p1[1]) >= 1) {
        grad = gradient(D, Coords<2>(q[0], q[1]));
        q[0] -= grad[0] * TAU / sqrt(grad[0] * grad[0] + grad[1] * grad[1]);
        q[1] -= grad[1] * TAU / sqrt(grad[0] * grad[0] + grad[1] * grad[1]);
        v.push_back(q);
    }
    v.push_back(p1);

    return v;
}

int main() {
    openWindow(w, h);
    Image<float> D(w, h);
    Image<float> W(w, h);
    vector<FloatPoint2> v;
    W.fill(1.0f);

    cout << "Placez des cercles, clic droit pour terminer" << endl;
    int xc, yc;
    float r;


    while (selectionCercle(xc, yc, r)) {
        ajouteGaussienne(W, xc, yc, r);
    }

    affiche(W);

    cout << "Cliquez pour determiner les points de depart et d'arrivee" << endl;
    IntPoint2 p1, p2;
    getMouse(p2);
    fillCircle(p2, 2, GREEN);
    getMouse(p1);
    fillCircle(p1, 2, GREEN);
    vector<PointDist> niv0;
    niv0.push_back(PointDist(p1[0], p1[1], 1.0f));
    D = fastMarching(W, niv0);
    v = geodesique(D, p1, p2);
    for (int i = 0; i < v.size(); i++) {
        drawPoint(arrondi(v[i]), BLACK);
    }
    endGraphics();
    return 0;
}