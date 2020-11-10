#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


// Составление матриц бинарных отношений
void init_bo_matrix(const int *matrix, int *bo_matrix, int size, int column) {
    int characteristic[size];

    for(int i = 0; i < size; i++){
        characteristic[i] = matrix[i*size+column];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(characteristic[i] >= characteristic[j]){
                bo_matrix[i*size+j] = 1;
            }
            else{
                bo_matrix[i*size+j] = 0;
            }
        }
    }
}

// Механизм доминирования
void dominance_mechanism(const int *bo_matrix, string *dominance_characteristic, const string characteristic, int *dominance_vector, int size) {
    for (int i = 0; i < size; i++) {
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (bo_matrix[i*size+j] == 1) {
                k = k + 1;
            }
        }
        if (k == size) {
            dominance_vector[i] = dominance_vector[i] + 1;
            if(dominance_characteristic[i].length() == 0) {
                dominance_characteristic[i] = characteristic;
            }
            else {
                dominance_characteristic[i] = dominance_characteristic[i] + "; " + characteristic;
            }
        }
    }
}

// Механизм блокировки
void locking_mechanism(const int *bo_matrix, string *locking_characteristic, const string characteristic, int *locking_vector, int size) {
    for (int i = 0; i < size; i++) {
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (bo_matrix[j*size+i] == 0) {
                k = k + 1;
            }
        }
        if (k == size - 1) {
            locking_vector[i] = locking_vector[i] + 1;
            if(locking_characteristic[i].length() == 0) {
                locking_characteristic[i] = characteristic;
            }
            else {
                locking_characteristic[i] = locking_characteristic[i] + "; " + characteristic;
            }
        }
    }
}

void tournament_mechanism(const int *bo_matrix, double *arr_turnir, int column, int size) {
    for (int i = 0; i < size; i++) {
        double k = 0;
        for (int j = 0; j < size; j++) {
            if (bo_matrix[i*size+j] == 1 && bo_matrix[j*size+i] == 0) {
                k = k + 1;
            }
            if (bo_matrix[i*size+j] == 1 && bo_matrix[j*size+i] == 1) {
                k = k + 0.5;
            }
        }
        k = k - 0.5;
        arr_turnir[i*size+column] = k;
    }
}

void k_max_mechanism(const int *bo_matrix, int *k_max_matrix, int column, int size) {
    for (int i = 0; i < size; i++) {
        int hor = 0;
        int er = 0;
        int nr = 0;
        for (int j = 0; j < size; j++) {
            if (bo_matrix[i*size+j] == 1 && bo_matrix[j*size+i] == 0) {
                hor = hor + 1;
            }
            if (bo_matrix[i*size+j] == 1 && bo_matrix[j*size+i] == 1) {
                er = er + 1;
            }
            if (bo_matrix[i*size+j] == 0 && bo_matrix[j*size+i] == 0) {
                nr = nr + 1;
            }
        }

        // Для 4 разновидностей к-максимальных
        for (int m = 0; m < 4; m++) {
            if (m == 0) {
                k_max_matrix[(i*size+column)+(size*size*m)] = hor + er + nr;
            }
            else if (m == 1) {
                k_max_matrix[(i*size+column)+(size*size*m)] = hor + nr;
            }
            else if (m == 2) {
                k_max_matrix[(i*size+column)+(size*size*m)] = hor + er;
            }
            else if (m == 3) {
                k_max_matrix[(i*size+column)+(size*size*m)] = hor;
            }
        }
    }
}

void k_max(int *k_max_matrix, int *k_1, int *k_2, int *k_3, int *k_4, int *k_2_4_optimum, string *country, string *characteristic, int size){
    // поиск и вывод к-максимальных
    for (int k = 0; k < size; k++) {
        cout << "\n" << characteristic[k] << "\n";
        int j = 0;
        int p = 100; // логические ключи для обработки данных
        int q = 100; // трёхмерного массива в нужном порядке
        int r = 100;
        int s = 100;
        int t = 100;
        int u = 100;

        // количество повторов ограничено количеством К-макс
        for (int m = 0; m < 4; m++) {
            // блок для обработки К1
            if (m == 0) {
                for (int i = 0; i < size; i++) {
                    if (k_max_matrix[(i * size + k) + (size * size * m)] == size && p == 100) {
                        cout << "K1: " << country[i];
                        k_1[i] += 1;
                        p = i;
                    }
                    else if (k_max_matrix[(i * size + k) + (size * size * m)] == size && p != i) {
                        cout << ", " << country[i];
                        k_1[i] += 1;
                        p = 1;
                    }
                }
                cout << "\n";
            }
            // блок для обработки К2
            if (m == 1) {
                for (int i = 0; i < size; i++) {
                    if ((k_max_matrix[(i * size + k) + (size * size * m)] == (size - 1)) && (q == 100)) {
                        cout << "K2: " << country[i];
                        k_2[i] += 1;
                        q = i;
                    }
                    else if ((k_max_matrix[(i * size + k) + (size * size * m)] == (size - 1)) && (q != i)) {
                        cout << ", " << country[i];
                        k_2[i] += 1;
                        q = 1;
                    }
                }
                if (q == 100) {
                    cout << "K2: отсутствует";
                }
                cout << "\n";
            }
            // блок для обработки К3
            if (m == 2) {
                for (int i = 0; i < size; i++) {
                    if (k_max_matrix[(i * size + k) + (size * size * m)] == size && r == 100) {
                        cout << "K3: " << country[i];
                        k_3[i] += 1;
                        r = i;
                    }
                    else if (k_max_matrix[(i * size + k) + (size * size * m)] == size && r != i) {
                        cout << ", " << country[i];
                        k_3[i] += 1;
                        r = 1;
                    }
                }
                cout << "\n";
            }
            // блок для обработки К4
            if (m == 3) {
                for (int i = 0; i < size; i++) {
                    if (k_max_matrix[(i * size + k) + (size * size * m)] == (size - 1) && s == 100) {
                        cout << "K4: " << country[i];
                        k_4[i] += 1;
                        s = i;
                    }
                    else if (k_max_matrix[(i * size + k) + (size * size * m)] == (size - 1) && s != i) {
                        cout << ", " << country[i];
                        k_4[i] += 1;
                        s = 1;
                    }
                }
                if (s == 100) {
                    cout << "K4: отсутствует";
                }
                cout << "\n";
            }
        }
            // блок для поиска и вывода оптимума по К1 и К3
            /*if (m == 3) {
                for (int i = 0; i < size; i++) {
                    if (k_max_matrix[(k*size+i)+(size*size*m)] == size && t == 100) {
                        cout << "ОПТИМУМом по К1 и К3 являются " << country[i] << ", ";
                        t = i;
                    }
                    if (k_max_matrix[(k*size+i)+(size*size*m)] == size && t != i) {
                        cout << country[i] << ", ";
                        t = 1;
                    }
                }
                cout << endl;
            }*/
            // блок для поиска и вывода оптимума по К2 и К4
            /*if (m == 3) {
                for (int i = 0; i < size; i++) {
                    if (k_max_matrix[(k*size+i)+(size*size*m)] == (size-1) && u == 100) {
                        cout << "ОПТИМУМом по К2 и К4 являются " << country[i] << ", ";
                        k_2_4_optimum[i] += 1;
                        u = i;
                    }
                    if (k_max_matrix[(k*size+i)+(size*size*m)] == (size-1) && u != i) {
                        cout << country[i] << ", ";
                        k_2_4_optimum[i] += 1;
                        u = 1;
                    }
                }
                if (u == 100) {
                    cout << "ОПТИМУМ по К2 и К4 отсутствует." << endl;
                }
                cout << endl << endl;
            }*/

    }
}

template<class T> void print_bo_matrix(T *matrix, int size) {
    string country[9] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    for (int i = 0; i <= size; i++) {
        if (i == 0) {
            cout << right << setw(5) << "" << "|";
        } else {
            cout << right << setw(5) << country[i - 1] << "|";
        }
    }
    cout << "\n";
    for (int i = 0; i < size; i++) {
        cout << right << setw(5) << country[(i)] << "|";
        for (int j = 0; j < size; j++) {
            //cout.precision(5);
            cout << right << setw(5) << matrix[(i) * size + j] << "|";
        }
        cout << "\n";
    }
}

template<class T> void print_matrix(T *matrix, int size) {
    string country[9] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    for (int i = 0; i < size; i++) {
        cout << right << setw(5) << country[(i)] << "|";
        for (int j = 0; j < size; j++) {
                cout.precision(5);
                cout << right << setw(5) << matrix[i*size+j] << "|";
        }
        cout << "\n";
    }
}

template<typename T> void print_two_vectors(string *vector_A, T *vector_B, string *vector_C, int size) {
    for (int i = 0; i < size; i++) {
        cout << right << setw(5) << vector_A[i] << "|" << setw(5) << vector_B[i] << "| " << vector_C[i] << "\n";
    }
}

template<class T> void print_vector(T *matrix, int size) {
    for (int i = 0; i < size; i++) {
        cout.precision(5);
        cout << right << setw(5) << matrix[i] << "|" << "\n";
    }
}
