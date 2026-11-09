#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

void printPoint(Point p) {
    printf("(%.2f, %.2f)\n", p.x, p.y);
}

Point createPoint(double x, double y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

double getDistance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void) {
    /* Pagal 1d punktą taškai tiesiogiai sukuriami getDistance funkcijos kvietime. */
    printf("Atstumas: %.2f\n",
           getDistance(createPoint(2.0, -3.0), createPoint(-4.0, 5.0)));

    return 0;
}
