#pragma once
#include <vector>

using namespace std;

template <class T> void selectionSortMaxByIndex(vector<T> &data) {
    int j = 0;
    int tmp = 0;
    for(int i = 0; i < data.size(); i++) {
        j = i;
        for(int k = i; k < data.size(); k++) {
            if(data[j] > data[k]) {
                j = k;
            }
        }
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}