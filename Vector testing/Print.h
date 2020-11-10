#pragma once
#include <vector>
#include <iostream>

using namespace std;

template <class T> int printArray(vector<T> &data) {
    for (T iterator : data) {
        try {
            if (iterator == data.back()) {
                cout << iterator;
            }
            else {
                cout << iterator << ", ";
            }
        }
        catch(out_of_range& e) {
            cout << "out_of_range" << "\n";
            return 1;
        }
    }
}