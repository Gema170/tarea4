#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <cfloat>
using namespace std;
using namespace std::chrono;

struct Punto {
    double x, y;
};

bool cmpX(const Punto &a, const Punto &b) { return a.x < b.x; }
bool cmpY(const Punto &a, const Punto &b) { return a.y < b.y; }

double dist(const Punto &a, const Punto &b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double min3(double a, double b) { return (a < b) ? a : b; }

double stripClosest(vector<Punto> &strip, double d) {
    double minVal = d;
    sort(strip.begin(), strip.end(), cmpY);
    for (size_t i = 0; i < strip.size(); i++)
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minVal; j++)
            minVal = min3(minVal, dist(strip[i], strip[j]));
    return minVal;
}

double closestUtil(vector<Punto> &P) {
    int n = P.size();
    if (n <= 3) {
        double minDist = DBL_MAX;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                minDist = min3(minDist, dist(P[i], P[j]));
        return minDist;
    }

    int mid = n / 2;
    Punto midPoint = P[mid];

    vector<Punto> Pl(P.begin(), P.begin() + mid);
    vector<Punto> Pr(P.begin() + mid, P.end());

    double dl = closestUtil(Pl);
    double dr = closestUtil(Pr);
    double d = min3(dl, dr);

    vector<Punto> strip;
    for (auto &p : P)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    return min3(d, stripClosest(strip, d));
}

double closest(vector<Punto> &P) {
    sort(P.begin(), P.end(), cmpX);
    return closestUtil(P);
}

int main() {
    int n;
    cout << "Ingrese el numero de puntos: ";
    cin >> n;
    vector<Punto> P(n);
    cout << "Ingrese los puntos (x y):\n";
    for (int i = 0; i < n; i++) cin >> P[i].x >> P[i].y;

    auto inicio = high_resolution_clock::now();
    double d = closest(P);
    auto fin = high_resolution_clock::now();

    duration<double> tiempo = fin - inicio;
    cout << "Distancia minima: " << d << endl;
    cout << "Tiempo de ejecucion: " << tiempo.count() << " segundos\n";

    return 0;
}
