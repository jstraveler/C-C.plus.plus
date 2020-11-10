#pragma once
#include <vector>
#include <iostream>

using namespace std;

template<typename T1,typename T2> struct Pair {
    T1 a;
    T2 b;
};

template <class T> int printArray(vector<T> &data) {
    for (T iterator : data) {
        try {
            if (iterator != data.back()) {
                cout << iterator << "\n";
            }
            else {
                cout << iterator;
            }
        }
        catch(out_of_range& e) {
            cout << "out_of_range" << "\n";
            return 1;
        }
    }
    return 0;
}

int printString(string &data) {
    for (auto iterator : data) {
        try {
            if (iterator != data.back()) {
                cout << iterator;
            }
            else {
                cout << iterator << "\n";
            }
        }
        catch(out_of_range& e) {
            cout << "out_of_range" << "\n";
            return 1;
        }
    }
    return 0;
}

auto read(const string& file_location, string &input_text, vector<string> &formatted_text) {
    int i = 0; // Counter for lines
    ifstream in(file_location, ios::in | ios::binary);
    if(!in.is_open()) {
        cout << "failed to open " << file_location << '\n';
    }
    else {
        while (in) {
            string line;
            in >> line;
            input_text.append(line + " ");
            i++;
            formatted_text.push_back(line);
        }
    }
    //cout << i << ", " << formatted_text.size() << ", " << input_text.size() << "\n";
    Pair<string, vector<string>> pair;
    pair.a = input_text;
    pair.b = formatted_text;
    return pair;
}