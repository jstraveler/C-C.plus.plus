#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

double rand_double(double a, double b);

void fillRandom(double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand_double(-1.0, 1.0);
    }
}

double rand_double(double a, double b) {
    //srand(time(0));
    return 0.0 + ((double)rand() / (double)RAND_MAX) * (b - a) + a;
}