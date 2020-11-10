#pragma once
#include <vector>

using namespace std;

template <class T> void selectionSortMinByMethod(vector<T> &data) {
    int j = 0;
    int tmp = 0;
    for(int i = 0; i < data.size(); i++) {
        j = i;
        for(int k = i; k < data.size(); k++) {
            if(data.at(j) < data.at(k)) {
                j = k;
            }
        }
        tmp = data.at(i);
        data.at(i) = data.at(j);
        data.at(j) = tmp;
    }
}