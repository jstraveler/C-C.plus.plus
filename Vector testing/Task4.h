#pragma once
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include "Print.h"

using namespace std;

int readArray(string a, vector<int> &vec) {
    ifstream in(a, ios::in | ios::binary);
    if (!in) {
        cout << "Can't read file!\n";
        return 1;
    }
    char *array = new char[10]();
    int i = 0;
    while (in >> reinterpret_cast<int &>(array[i++]));
    vector<int> Vec(array, array + strlen(array));
    delete[] array;
    array = nullptr;
    vec = Vec;
    //printArray(Vec);
    return 0;
}