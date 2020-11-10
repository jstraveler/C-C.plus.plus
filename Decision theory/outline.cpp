
/*const int SIZE = 8;

// к передаётся как аргумент из main
void k_max(int arr[SIZE][SIZE], int k) {
    for (int i = 0; i < SIZE; i++) {
        int hor = 0;
        int er = 0;
        int nr = 0;
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 1 && arr[j][i] == 0) {
                hor = hor + 1;
            }
            if (arr[i][j] == 1 && arr[j][i] == 1) {
                er = er + 1;
            }
            if (arr[i][j] == 0 && arr[j][i] == 0) {
                nr = nr + 1;
            }
        }
        // er = er - 1;

        // т.к. 4 разновидности к-макс
        for (int m = 0; m < 4; m++) {
            if (m == 0 || m == 2) {
                k_max_matrix[k][i][m] = hor + er + nr;
            }
            if (m == 1 || m == 3) {
                k_max_matrix[k][i][m] = hor + nr;
            }
        }
    }
}*/


/*
// вывод к-макс по всем БО
for (int k = 0; k < SIZE; k++) {
    cout << "К-макс для параметра " << "\"" <<  parametr[k] << "\"" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << notebooks[i] << "  " << '\t';
        for (int j = 0; j < 4; j++) {
            cout << k_max_matrix[k][i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

// поиск и вывод к-максимальных
for (int k = 0; k < SIZE; k++) {
    cout << parametr[k] << endl;
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
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][j] == 8 && p == 100) {
                    cout << "K1-max: " << notebooks[i] << ", ";
                    k_1[i] += 1;
                    p = i;
                }
                if (k_max_matrix[k][i][j] == 8 && p != i) {
                    cout << notebooks[i] << ", ";
                    k_1[i] += 1;
                    p = 1;
                }
            }
            cout << endl;
        }
        // блок для обработки К2
        if (m == 1) {
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][j] == 8 && q == 100) {
                    cout << "K2-max: " << notebooks[i] << ", ";
                    k_2[i] += 1;
                    q = i;
                }
                if (k_max_matrix[k][i][j] == 8 && q != i) {
                    cout << notebooks[i] << ", ";
                    k_2[i] += 1;
                    q = 1;
                }
            }
            cout << endl;
        }
        // блок для обработки К3
        if (m == 2) {
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][j] == 8 && r == 100) {
                    cout << "K3-max: " << notebooks[i] << ", ";
                    k_3[i] += 1;
                    r = i;
                }
                if (k_max_matrix[k][i][j] == 8 && r != i) {
                    cout << notebooks[i] << ", ";
                    k_3[i] += 1;
                    r = 1;
                }
            }
            cout << endl;
        }
        // блок для обработки К4
        if (m == 3) {
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][j] == 8 && s == 100) {
                    cout << "K4-max: " << notebooks[i] << ", ";
                    k_4[i] += 1;
                    s = i;
                }
                if (k_max_matrix[k][i][j] == 8 && s != i) {
                    cout << notebooks[i] << ", ";
                    k_4[i] += 1;
                    s = 1;
                }
            }
            cout << endl;
        }
        // блок для поиска и вывода оптимума по К1 и К3
        if (m == 3) {
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][j] == 8 && t == 100) {
                    cout << "ОПТИМУМом по К1 и К3 являются " << notebooks[i] << ", ";
                    t = i;
                }
                if (k_max_matrix[k][i][j] == 8 && t != i) {
                    cout << notebooks[i] << ", ";
                    t = 1;
                }
            }
            cout << endl;
        }
        // блок для поиска и вывода оптимума по К2 и К4
        if (m == 3) {
            for (int i = 0; i < SIZE; i++) {
                if (k_max_matrix[k][i][1] == 7 && u == 100) {
                    cout << "ОПТИМУМом по К2 и К4 являются " << notebooks[i] << ", ";
                    k_2_4_optimum[i] += 1;
                    u = i;
                }
                if (k_max_matrix[k][i][1] == 7 && u != i) {
                    cout << notebooks[i] << ", ";
                    k_2_4_optimum[i] += 1;
                    u = 1;
                }
            }
            if (u == 100) {
                cout << "ОПТИМУМ по К2 и К4 отсутствует." << endl;
            }
            cout << endl << endl;
        }
    }
}

cout << "Таблица К-максимальных по всем моделям" << endl;
// вывод К-макс по ноутбукам
for (int i = 0; i < SIZE; i++) {
    if (i == 3 || i == 7) {
        cout << notebooks[i] << "  " << '\t' << k_1[i] << '\t' << k_2[i] << '\t' << k_3[i] << '\t' << k_4[i] << endl;
    }
    else {
        cout << notebooks[i] << "     " << '\t' << k_1[i] << '\t' << k_2[i] << '\t' << k_3[i] << '\t' << k_4[i] << endl;
    }
}
cout << endl;

// вывод оптимумов К1 и К3
for (int i = 0; i < SIZE; i++) {
    if (i == 3 || i == 7) {
        cout << notebooks[i] << "  " << '\t' << "   ОПТИМУМ по К1 и К3  " << '\t' << k_1[i] << '\t' << " раз(a)" << endl;
    }
    else {
        cout << notebooks[i] << "     " << '\t' << "   ОПТИМУМ по К1 и К3  " << '\t' << k_1[i] << '\t' << " раз(a)" << endl;
    }
}
cout << endl;

// вывод оптимумов К2 и К4
for (int i = 0; i < SIZE; i++) {
    if (i == 3 || i == 7) {
        cout << notebooks[i] << "  " << '\t' << "   ОПТИМУМ по К2 и К4  " << '\t' << k_2_4_optimum[i] << '\t' << " раз(a)" << endl;
    }
    else {
        cout << notebooks[i] << "     " << '\t' << "   ОПТИМУМ по К2 и К4  " << '\t' << k_2_4_optimum[i] << '\t' << " раз(a)" << endl;
    }
}*/