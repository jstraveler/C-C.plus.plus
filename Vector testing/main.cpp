/** 1) Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя оператор operator[].
    2) Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя метод at().
    3) Напишите алгоритм сортировки (любой простейший) содержимого вектора целых чисел, используя для доступа к содержимому
    вектора только итераторы. Для работы с итераторами допустимо использовать только операторы получения текущего элемента
    и перехода в следующему (подсказка, можно сохранять копию итератора указывающего на некоторый элемент).
    4) Прочитайте во встроенный массив С содержимое текстового файлы, скопируйте данные в вектор одной строкой кода
    (без циклов и алгоритмов STL)
    5) Напишите программу, сохраняющую в векторе числа, полученные из стандартного ввода (окончанием ввода является число 0).
    Удалите все элементы, которые делятся на 2 (не используете стандартные алгоритмы STL), если последнее число 1.
    Если последнее число 2, добавьте после каждого числа которое делится на 3 три единицы.
    6) Напишите функцию void fillRandom(double* array, int sizeArr) заполняющую массив случайными значениями в интервале
    от -1.0 до 1.0. Заполните с помощью заданной функции вектора размером 5,10,25,50,100 и отсортируйте его содержимое
    (с помощью любого разработанного ранее алгоритма модифицированного для сортировки действительных чисел).
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstring>
//*************User library*************
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#include "Task5.h"
#include "Task6.h"
#include "Print.h"

using namespace std;

int main() {
    int sizeArr_vec = 10000;
    clock_t t;
    vector<int> Dec = vector<int>(sizeArr_vec);
    for (int i = sizeArr_vec, j = 0; j < Dec.size(); i--, j++) {
            Dec[j] = i;
    }
    printf("Before sorting\n");
    //printArray(Dec);
    printf("SortMaxByIndex\n");
    t = clock(); // Замеряем время до выполнения алгоритма
    selectionSortMaxByIndex(Dec); // Сорировка через оператор[]
    t = clock() - t; // Вычилсяем разницу по времени
    printf("Working time: %f, sec.\n", ((float)t) / CLOCKS_PER_SEC);
    //printArray(Dec);
    printf("SortMinByMethod\n");
    t = clock();
    selectionSortMinByMethod(Dec); // Сорировка с помощью функции at()
    t = clock() - t;
    printf("Working time: %f, sec.\n", ((float)t) / CLOCKS_PER_SEC);
    //printArray(Dec);
    printf("SortMaxByIterator\n");
    t = clock();
    selectionSortMaxByIterator(Dec); // Сорировка с помощью итераторов
    t = clock() - t;
    printf("Working time: %f, sec.\n", ((float)t) / CLOCKS_PER_SEC);
    //printArray(Dec);
    printf("SortBySTL\n");
    t = clock();
    sort(Dec.begin(), Dec.end()); // Сортировка стандартным алгоритмом sort()
    t = clock() - t;
    printf("Working time: %f, sec.\n", ((float)t) / CLOCKS_PER_SEC);
    //printArray(Dec);
    //printArray(Dec);

    //4.
    string a = "input.txt";
    vector<int> vec(0);
    readArray(a, vec);
    printArray(vec);

    //5.
    vector <int> Svec (0);
    modifyArray(Svec);
    printArray(Svec);

    //6.
    int sizeArr[5]; sizeArr[0] = 5, sizeArr[1] = 10, sizeArr[2] = 25, sizeArr[3] = 50, sizeArr[4] = 100;
    for (int i = 0; i < 5; i++) {
        double array[sizeArr[i]];
        fillRandom(array, sizeArr[i]);
        vector <double> Dvec(array, array + sizeArr[i]);
        selectionSortMinByMethod(Dvec);
        cout << "\n" << "New vector size of: " << Dvec.size() << "\n" ;
        printArray(Dvec);
    }
    return 0;
}