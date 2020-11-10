/** Задание: Решение краевой задачи методом стрельбы. (Вариант №24В)
 * ||  Диссипативная функция (функция рассеяния) — функция, вводимая для учёта перехода энергии упорядоченного
 * ||  движения в энергию неупорядоченного движения, в конечном счёте — в тепловую (такой переход, например, имеет
 * ||  место при воздействии на механическую систему сил вязкого трения).
 * Явление теплопередачи в одномерном стационарном потоке без диссипации описывается следующей математической моделью:
 * E * d^2T/dx^2 + x * dT/dx - xT = 0;
 * T(0) = A; T(L) = B.
 * Построить график T(x) на помежутках [0,L], применив для решения этой задачи метод стрельбы с использованием
 * подпрограмм RKF45 и ZEROIN. "Пристрелку" нужно вести по T'(0) в диапазоне стрельбы [F,G]. Значения E, A, B, F, G, L
 * задаются дополнительно.
 * Оценить общую погрешность результата и влияние на точность результата погрешности исходных данных.
 * e = 1.994827 * 0~S~0.5 sqrt(1+x^5)dx; L = 1;
 * Сис-ма ур-ий:
 * 5A + 7B + 6F + 5G = 23;
 * 7A + 10B + 8F + 7G = 32;
 * 6A + 8B + 10F + 9G = 36;
 * 5A + 7B + 9F + 10G = 36.
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include "rkf45.c"
#include "zeroin.c"
#include "quanc8.c"

using namespace std;

int RKF_45();
int RKF(double &R, double &L);
double ZEROIN(double &X, double &E);
int User_function_rkf(int n, double t, double *z, double *dxdt);
double User_function_zeroin(double Z0);
void Integral(double &X);
double User_function_quanc(double b);
int Dec(double &A, double &B, double &F, double &G);
double E, B;
double z[2];


int main() {
    double X, A, F, G, L;
    L = 1.0;
    A = B = F = G = 1.0;
    Integral(X);
    printf("E = %f\n\n", round(E));
    Dec(A, B, F, G);
    printf("A = %.4f, B = %.4f, F = %.4f, G = %.4f\n\n", A, B, F, G);
    double Res;
    Res = (double) ZEROIN(F,G);
    printf("Res = %f\n\n", Res);
    RKF(Res, L);
    return 0;
}

double User_function_quanc(double b) {
    return 1.994827 * sqrt(1 + pow(b, 5.0));
}

void Integral(double &X) {
    double a, b, epsabs, epsrel, result, errest, posn;
    int nfe, flag;
    a = 0.0;
    b = 0.5;
    epsrel = 1.0e-10;
    epsabs = 0.0;
    quanc8(User_function_quanc, a, b, epsabs, epsrel, &result, &errest, &nfe, &posn, &flag);
    X = b;
    E = result;
}

int Dec(double &A, double &BB, double &F, double &G) {
    int n = 4, mdim = 4;
    int pivot[mdim];
    int flag;
    double cond;
    // ______________________________________________________
    //|          Матрица А                                   |
    //|______________________________________________________|
    double a[4][4] = {5 * A,  7 * B,  6 * F,  5 * G,       //|
                      7 * A, 10 * B,  8 * F,  7 * G,       //|
                      6 * A,  8 * B, 10 * F,  9 * G,       //|
                      5 * A,  7 * B,  9 * F, 10 * G};      //|
    //|______________________________________________________|
    //|            Вектор B                                  |
    //|______________________________________________________|
    double b[4] = {23.0, 32.0, 36.0, 36.0};                //|
    //|______________________________________________________|

    try {
        decomp(n, mdim, *a, &cond, pivot, &flag);
    }
    catch (exception &e) {
        if (flag != 0) {
            printf("decomp could not allocate workspace\n");
        }
        if ((cond + 1.0) == cond) {
            printf("Singular Matrix\n");
        }
        return 1;
    }
    solve(n, mdim, *a, b, pivot);

    A = b[0] * - 1.0;
    B = b[1];
    F = b[2];
    G = b[3];
}

int User_function_rkf(int n, double t, double *z, double *dxdt) {
    dxdt[0] = -((t * z[0]) / E) + ((t * z[1]) / E);
    dxdt[1] = z[0];
}

double User_function_zeroin(double Z0) {
    z[0] = Z0;
    z[1] = 0.0;
    RKF_45();
    return z[1] - B;
}

double ZEROIN(double &F, double &G) {
    double left = F; // 1.0
    double right = G; // 2.0
    double tol = 1.0e-6;
    int flag = 0;
    double Res;
    Res = zeroin(left, right, reinterpret_cast<double (*)(double)>(User_function_zeroin), tol, &flag);
    return Res;
}

// Для пристрелки
int RKF_45() { // Решение системы уравнений с помощью библиотечной функции RKF45
    double dxdt[2]; // Результат вычисления функций на i-ом шаге
    double t = 0.0; // Величина шага rkf45
    double x1; // Стартовая точка
    double x2; // Точка выхода, в которой получено решение
    double relerr = 1.0e-4; // Относительная погрешность
    double abserr = 1.0e-4; // Абслютная погрешность
    int fail = 0; // Статус выделения памяти для рабочего пространства
    int step = 0; // Шаг
    int n = 2; // Количестов уравнений
    int flag = 1; // Индикатор статуса интегрирования
    int nfe = 0; // Кол-во выполненных шагов rkf45
    int maxfe = 5000; // Максимальное кол-во шагов
    rkfinit(n, &fail);
    if (fail == 0) { // Проверка статус выделения памяти для рабочего пространства
        printf("      t        z[0]       z[1]\n");
        printf("--------------------------------\n");
        x1 = 0.0; // A = 0.0
        x2 = B; // B = 1.0
        rkf45(User_function_rkf, n, z, dxdt, &x1, x2, &relerr, abserr, &t, &nfe, maxfe, &flag);
        printf("%10.6f %10.6f %10.6f \n", x1, z[0], z[1]); // Значения z0, z1 на i-ом шаге
        rkfend();
        printf("nfe         : %d\n", nfe); // Кол-во выполненных шагов rkf45
        printf("step size   : %f\n\n", t); // Величина шага rkf45
    }
    return 0;
}

// Для вычисления функции
int RKF(double &Res, double &L) { // Решение системы уравнений с помощью библиотечной функции RKF45
    //double z[2]; // Значения z0, z1 на i-ом шаге
    double dxdt[2]; // Результат вычисления функций на i-ом шаге
    double t = 0.0; // Величина шага rkf45
    double x1 = 0.0; // Стартовая точка
    double x2; // Точка выхода, в которой получено решение
    double relerr = 1.0e-6; // Относительная погрешность
    double abserr = 1.0e-6; // Абслютная погрешность
    int fail = 0; // Статус выделения памяти для рабочего пространства
    int n = 2; // Количестов уравнений
    int flag = 1; // Индикатор статуса интегрирования
    int nfe = 0; // Кол-во выполненных шагов rkf45
    int maxfe = 50000; // Максимальное кол-во шагов
    rkfinit(n, &fail);
    int k = 0;
    double H = 0.01; // Шаг печати
    if (fail == 0) { // Проверка статус выделения памяти для рабочего пространства
        z[0] = Res; // Начальное значение z0
        z[1] = 0.0; // Начальное значение z1
        printf("      t        z[0]       z[1]\n");
        printf("--------------------------------\n");
        printf("%10.6f %10.6f %10.6f \n", (x1), z[0], z[1]);
        while (x1 <= L) { // 0.01 - шаг печати
            x2 = x1 + H;
            x1 = x2 - H;
            rkf45(User_function_rkf, n, z, dxdt, &x1, x2, &relerr, abserr, &t, &nfe, maxfe, &flag);
            printf("%10.6f %10.6f %10.6f \n", (x2), z[0], z[1]);
        }
        rkfend();
        printf("nfe         : %d\n", nfe); // Кол-во выполненных шагов rkf45
        printf("step size   : %f\n\n", t); // Величина шага rkf45
    }
    return 0;
}