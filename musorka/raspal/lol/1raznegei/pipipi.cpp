#include <math.h>
#include <iostream>

double pipi(double x) {
    return sqrt(4-x*x);
    };

int main() {
    int N = 100000;
    double h = 2.0 / N;
    double S = 0;

    for (int i = 0; i < N-1; i++) {
        S += (pipi(i * h) + pipi(i * h)) * h/2;
    }
    std::cout << S;
}
