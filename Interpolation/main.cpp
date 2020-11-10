#include <iostream>
#include <math.h>
#include <stdio.h>
#include "spline.c"
#include "quanc8.c,v"

/** Задача: По заданной таблице построить полином Лагранжа и сплайн-функцию. Вычислить значения обеих функций в
 * точках xk = −1 + 0.1*k (k=1,2, … ,19). Построить графики. Используя программу QUANC8,
 * вычислить интеграл: ∫_1^2 tan(x)/x dx
 */

using namespace std;

double Lagrange(double x, double const *X, double const *F);
void Spline(double *S, double *Xk, double *X, double *F);
void Integral(double *X, double *F);
double Fun(double d);
double b;

int main() {
    double X[7] = {-1.000, -0.960, -0.860, -0.790, 0.220, 0.500,  0.930};
    double F[7] = {-1.000, -0.151,  0.894,  0.986, 0.895, 0.500, -0.306};
    double Xk[19] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4,
                     0.5, 0.6, 0.7, 0.8};
    double Lag[19]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for(int i = 0; i < 19; i++){
        Lag[i] = Lagrange(Xk[i], X, F);
        printf("Lag= %.8f\n", Lag[i]);
    }

    double S[19];
    Spline(S, Xk, X, F);

    for(int i = 0; i < 19; i++){
        printf("Spline= %.8f\n", S[i]);
    }

    double a = tan(1)/1;
    double aa = tan(2)/2;
    printf("Integ= %.8f\n", aa-a);

    Integral(X, F);

    return 0;
}

double Lagrange(double x, double const *X, double const *F) {
    int ndim = 7;
    double Q = 0;
    double WkX[19] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double WkXk[19] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int i, j;
    for (i = 0; i < ndim; i++){
        for (j = 0; j < ndim; j++)
            if (i != j){
                WkX[i] *= (x - X[j]);
                WkXk[i] *= X[i] - X[j];
            }
        if (WkXk[i] != 0)
            Q += (WkX[i] / WkXk[i])*F[i];
    }
    return Q;
}

void Spline(double *S, double *Xk, double *X, double *F){
    int ndim = 7;
    double b[ndim], c[ndim], d[ndim];
    int last, flag;
    spline((ndim), 1, 1, 1, 1, X, F, b, c, d, &flag);
    //CalcValue();
    for (int i = 0; i < 19; i++)
        S[i] = seval(ndim, Xk[i], X, F, b, c, d, &last);
}


void Integral(double *X, double *F) {
    printf(" QUANC8: THE INTEGRAL VALUES \n\n");
    double a, epsabs, epsrel, result, errest, posn;
    int nfe, flag;
    a = 1.0;
    b = 1.0;
    epsrel = 1.0e-10;
    epsabs = 0.0;
    int i = 0;
    while (b < 2.1){
        quanc8(Fun, a, b, epsabs, epsrel, &result, &errest, &nfe, &posn, &flag);
        X[i] = b;
        F[i] = result;
        printf(" x= %.1f", b);
        printf(" y = %.8f\n", result);
        b = b + 0.1;
        i++;
    }
}

double Fun(double z) {
    double f;
    f = tan(b) / b;
    return f;
}

