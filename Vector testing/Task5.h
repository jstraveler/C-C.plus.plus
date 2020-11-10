#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

int modifyArray(vector<int> &vec) {
    cout << "\n" << "User input data. You may use <int>. For continue input 0." << "\n";
    int data;
    while (cin >> data) { // Считываем значения в вектор, пока не введем 0
        if (data == 0) {
            break;
        }
        vec.push_back(data);
    }
    cout << "Size of vector: " << vec.size() << "\n";
    vector<int> vecTemp(0);
    //vecTemp.reserve(vec.size());
    vector<int>::iterator itTemp;
    itTemp = vecTemp.begin();
    int lastElem = vec.back();

    if (lastElem == 1) {
        for (int iterator : vec) {
            if (iterator % 2 == 1) {
                vecTemp.push_back(iterator);
            }
        }
    }
    else if (lastElem == 2) {
        for (int iterator : vec) {
            if (iterator % 3 == 0) {
                vecTemp.push_back(iterator);
                itTemp++;
                vecTemp.push_back(1);
                vecTemp.push_back(1);
                vecTemp.push_back(1);
                itTemp = itTemp + 3;
            }
            else {
                vecTemp.push_back(iterator);
                itTemp++;
            }
        }
    }
    else {
        vecTemp = vec;
    }
    vec = vecTemp;
    cout << "Size of new vector: " << vecTemp.size() << "\n" ;
    return 0;
}