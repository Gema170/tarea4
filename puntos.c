#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

typedef struct {
    double x, y;
} Punto;

int cmpX(const void *a, const void *b) {
    Punto *p1 = (Punto*)a; Punto *p2 = (Punto*)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int cmpY(const void *a, const void *b) {
    Punto *p1 = (Punto*)a; Punto *p2 = (Punto*)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

double dist(Punto p1, Punto p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

double min(double a, double b) { return (a < b) ? a : b; }

double stripClosest(Punto strip[], int size, double d) {
    double minVal = d;
    qsort(strip, size, sizeof(Punto), cmpY);
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minVal; j++)
            if (dist(strip[i], strip[j]) < minVal)
                minVal = dist(strip[i], strip[j]);
    return minVal;
}

double closestUtil(Punto P[], int n) {
    if (n <= 3) {
        double minDist = DBL_MAX;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (dist(P[i], P[j]) < minDist)
                    minDist = dist(P[i], P[j]);
        return minDist;
    }

    int mid = n / 2;
    Punto midPoint = P[mid];

    double dl = closestUtil(P, mid);
    double dr = closestUtil(P + mid, n - mid);
    double d = min(dl, dr);

    Punto *strip = (Punto*)malloc(n * sizeof(Punto));
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(P[i].x - midPoint.x) < d)
            strip[j++] = P[i];

    double res = min(d, stripClosest(strip, j, d));
    free(strip);
    return res;
}

double closest(Punto P[], int n) {
    qsort(P, n, sizeof(Punto), cmpX);
    return closestUtil(P, n);
}

int main() {
    int n;
    printf("Ingrese el numero de puntos: ");
    scanf("%d", &n);
    Punto *P = (Punto*)malloc(n * sizeof(Punto));

    printf("Ingrese los puntos (x y):\n");
    for (int i = 0; i < n; i++) scanf("%lf %lf", &P[i].x, &P[i].y);

    clock_t inicio = clock();
    double d = closest(P, n);
    clock_t fin = clock();

    printf("Distancia minima: %lf\n", d);
    printf("Tiempo de ejecucion: %.6f segundos\n", (double)(fin - inicio) / CLOCKS_PER_SEC);

    free(P);
    return 0;
}
