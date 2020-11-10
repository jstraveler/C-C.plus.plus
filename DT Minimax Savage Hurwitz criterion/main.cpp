#include <iostream>

/** Задача: Строки отражают варианты решений, доступные для выбора. Столбцы показывают возможные условия.
 * Требуется, применяя критерии минимакса, Сэвиджа и Гурвица, выбрать варианты решений, являющиеся оптимальными
 * согласно рассматриваемому критерию.
 */

using namespace std;

void minimax(int const [], int rows);
void savage(int *matrix, int rows, int columns);
void hurwitz(int *matrix, int rows, int columns, float c);

int main() {
    // Init variables
    int rows = 4;
    int columns = 5;
    int matrix[4][5] = {{ 15, 10,  0, -6, 17},
                         { 3, 14,  8,  9,  2},
                         { 1,  5, 14, 20, -3},
                         { 7, 19, 10,  2,  0}};
    float c = 0.48;

    cout << "\n" << "------------Minimax criterion-------------" << "\n";
    minimax(*matrix, rows);

    cout << "\n" << "------------Savage criterion-------------" << "\n";
    savage(*matrix, rows, columns);

    cout << "\n" << "------------Hurwitz criterion-------------" << "\n";
    hurwitz(*matrix, rows, columns, c);

    return 0;
}

void minimax(int const *matrix, int rows) {
    int k;
    int column[rows];
    int min;
    for (int i = 0; i < rows; i++) {
        min = matrix[i*5];
        for (int j = 0; j < 5; j++) {
            if (matrix[i*5+j] < min) {
                min = matrix[i*5+j];
            }
        }
        column[i] = min; // формируем столбец строчных минимумов
    }

    cout << "Column of min:" << "\n";
    for (int i = 0; i < rows; i++) {
        cout << "for row " << i + 1 << " = " << column[i] << "\n";
    }

    int max = column[0];
    for (int i = 1; i < rows; i++) {
        if (column[i] > max) {
            max = column[i]; // находим максимум из полученного столбца
            k = i;
        }
    }
    cout << "The max value among the min row elements: " << max << "\n";
    cout << "The optimal solution is located in " << k + 1 << " row" << "\n";
}

void savage(int *matrix, int rows, int columns) {
    int k;
    int max_1[columns];
    int arr2[rows][columns];
    int column_max[rows];
    int min;

    int max;
    for (int j = 0; j < columns; j++) {
        max = matrix[j];
        for (int i = 0; i < rows; i++) {
            if (matrix[i * columns + j] > max) {
                max = matrix[i * columns + j];
            }
        }
        max_1[j] = max; // сформируем строку столбцовых максимумов
    }

    cout << "Row of column max: " << "\n";
    for (int i = 0; i < columns; i++) {
        cout << max_1[i] << "\t";
    }

    cout << "\n" << "Matrix after subtracting column elements from column maximum:" << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            arr2[i][j] = max_1[j] - matrix[i * columns + j]; // из максимума вычли каждый элемент столбца
            cout << arr2[i][j] << "\t";
        }
        cout << "\n";
    }

// выбрать макисимум в каждой строке
    for (int i = 0; i < rows; i++) {
        int max = arr2[i][0];
        for (int j = 1; j < columns; j++) {
            if (arr2[i][j] > max) {
                max = arr2[i][j];
            }
        }
        column_max[i] = max; // составили столбец строчных максимумов
    }
    cout << "Column of max from the elements of each row:" << "\n";
    for (int i = 0; i < rows; i++) {
        cout << column_max[i] << endl;
    }

// выбрать из них минимум
    min = column_max[0];
    for (int i = 1; i < rows; i++) {
        if (column_max[i] < min) {
            min = column_max[i];
            k = i;
        }
    }
    cout << "The min value obtained by the Savage criterion is " << min << "\n";
    cout << "The optimal solution is located in " << k + 1 << " row" << "\n";
}

void hurwitz(int *matrix, int rows, int columns, float c) {
    int k;
    float anti_c = 1 - c;
    int stolbec_min[rows];
    int stolbec_max[rows];
    float stolbec_sum[rows];
    float max;

    int min;
    // найдём столбец строчных минимумов
    for (int i = 0; i < rows; i++) {
        min = matrix[i*columns];
        for (int j = 0; j < columns; j++) {
            if (matrix[i * columns + j] < min) {
                min = matrix[i * columns + j];
            }
        }
        stolbec_min[i] = min;
    }

    cout << "Column of min from the elements of each row:" << "\n";

    for (int i = 0; i < rows; i++) {
        cout << stolbec_min[i] << "\n";
    }

    // найдём столбец строчных максимумов
    int maximum;
    for (int i = 0; i < rows; i++) {
        maximum = matrix[i*columns];
        for (int j = 0; j < columns; j++) {
            if (matrix[i * columns + j] > maximum) {
                maximum = matrix[i * columns + j];
            }
        }
        stolbec_max[i] = maximum;
    }

    cout << "Column of max from the elements of each row:" << "\n";
    for (int i = 0; i < rows; i++) {
        cout << stolbec_max[i] << "\n";
    }

    // найдём столбец суммы мин и макс (с коэффициентом)
    for (int i = 0; i < rows; i++) {
        stolbec_sum[i] = stolbec_min[i] * c + stolbec_max[i] * anti_c;
    }

    cout << "Column of the sums of max and min from the elements of each row: " << "\n";
    for (int i = 0; i < rows; i++) {
        cout << stolbec_sum[i] << "\n";
    }

    // поиск максимума в столбце суммы
    max = stolbec_sum[0];
    for (int i = 0; i < rows; i++) {
        if (stolbec_sum[i] > max) {
            max = stolbec_sum[i];
            k = i;
        }
    }
    cout << "The max value obtained by the Hurwitz criterion is " << max << "\n";
    cout << "The optimal solution is located in " << k + 1 << " row" << endl;
}
