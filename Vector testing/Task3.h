#pragma once
#include <vector>

using namespace std;

template <class T> void selectionSortMaxByIterator(vector<T>& data) {
    vector<int>::iterator iter;
    iter = data.begin();
    vector<int>::iterator im_iter;
    im_iter = data.begin();
    int tmp = 0;
    while (im_iter != data.end()) {
        while (iter != data.end()) {
            if (*im_iter > *iter) {
                tmp = *im_iter;
                *im_iter = *iter;
                *iter = tmp;
            }
            iter++;
        }
        iter = data.begin();
        im_iter++;
    }
}