#include <iostream>
#include <iomanip>

using namespace std;

/** Задача с последействием.
 * Определить оптимальный объем заказа автомобилей в условиях неравномерного спроса.
 */

void init_matrix_first_year(int *matrix, int size);
void init_matrix_second_year(int *matrix, int size);
void init_probability_matrix(double *probability_matrix, int const *init_matrix, double const *vector, int size);
void mathematical_expectation(double *matrix, int *mathematical_expectation, int size);
void final_mathematical_expectation(int *mathematical_expectation_first_year, int *mathematical_expectation_second_year, int size);
template<class T> void print_matrix(T *matrix, int size);
template<class T> void print_vector(T *matrix, int size);

int main() {
    // Init variables
    int size = 7;
    int matrix_first_year[size][size];
    int matrix_second_year[size][size];
    double probability_matrix_first_year[size][size];
    double probability_matrix_second_year[size][size];
    double probability_first_year[7] = {0.3, 0.25, 0.2, 0.13, 0.08, 0.03, 0.01};
    double probability_second_year[7] = {0.01, 0.02, 0.07, 0.15, 0.2, 0.25, 0.3};
    int mathematical_expectation_first_year[7] = {0, 0, 0, 0, 0, 0, 0};
    int mathematical_expectation_second_year[7] = {0, 0, 0, 0, 0, 0, 0};
    // Init matrix
    init_matrix_first_year(*matrix_first_year, size);
    init_matrix_second_year(*matrix_second_year, size);
    // Print matrix
    cout << "Matrix first year" << "\n";
    print_matrix(*matrix_first_year, size);
    cout << "Matrix second year" << "\n";
    print_matrix(*matrix_second_year, size);
    // Init probability matrix
    init_probability_matrix(*probability_matrix_first_year, *matrix_first_year, probability_first_year, size);
    init_probability_matrix(*probability_matrix_second_year, *matrix_second_year, probability_second_year, size);
    // Print probability matrix
    cout << "Probability matrix first year" << "\n";
    print_matrix(*probability_matrix_first_year, size);
    cout << "Probability matrix second year" << "\n";
    print_matrix(*probability_matrix_second_year, size);
    // Evaluate mathematical expectation
    mathematical_expectation(*probability_matrix_first_year, mathematical_expectation_first_year, size);
    mathematical_expectation(*probability_matrix_second_year, mathematical_expectation_second_year, size);
    // Print mathematical expectation
    cout << "Mathematical expectation matrix first year" << "\n";
    print_vector(mathematical_expectation_first_year, size);
    cout << "Mathematical expectation matrix second year" << "\n";
    print_vector(mathematical_expectation_second_year, size);
    // Evaluate final mathematical expectation
    final_mathematical_expectation(mathematical_expectation_first_year, mathematical_expectation_second_year, size);
    // Print final mathematical expectation
    cout << "Final mathematical expectation matrix second year" << "\n";
    print_vector(mathematical_expectation_first_year, size);
    return 0;
}

void init_matrix_first_year(int *matrix, int size) {
    int demand = 0; // спрос
    int order = 0;  // заказ
    int price = 25000; // стоимость одной машины 1 год
    int seb = 15000; // себестоимость 1 автомобиля
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i*size+j] = ((demand * price) - (order * seb));
            if(demand > order){
                matrix[i*size+j] = matrix[i*size+j] - ((demand - order) * price);
            }
                demand = demand + 50;
            }
        demand = 0;
        order = order + 50;
    }
}

void init_matrix_second_year(int *matrix, int size) {
    int demand = 0; // спрос
    int order = 0;  // заказ
    int price_second_year = 10000; // стоимость одной машины 2 год
    int price_third_year = 1000; // стоимость одной машины 3 год
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i*size+j] = (demand * price_second_year);
            if (demand > order) {
                matrix[i*size+j] = matrix[i*size+j] - ((demand - order) * price_second_year);
            }
            if((order - demand) > 0) {
                matrix[i*size+j] = matrix[i*size+j] + ((order - demand) * price_third_year);
            }
            demand = demand + 50;
        }
        demand = 0;
        order = order + 50;
    }
}

void init_probability_matrix(double *probability_matrix, int const *init_matrix, double const *vector, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            probability_matrix[i*size+j] = (double) init_matrix[i*size+j] * vector[j];
        }
    }
}

void mathematical_expectation(double *matrix, int *mathematical_expectation, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mathematical_expectation[i] = mathematical_expectation[i] + matrix[i*size+j];
        }
    }
}

void final_mathematical_expectation(int *mathematical_expectation_first_year, int *mathematical_expectation_second_year, int size){
    for (int i = 0; i < size; i++) {
        mathematical_expectation_first_year[i] = mathematical_expectation_first_year[i] + mathematical_expectation_second_year[i];
    }
}

template<class T> void print_matrix(T *matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout.precision(10);
            cout << right << setw(10) << matrix[i*size+j] << "|";
        }
        cout << "\n";
    }
}

template<class T> void print_vector(T *matrix, int size) {
    for (int i = 0; i < size; i++) {
        cout.precision(10);
        cout << right << setw(10) << matrix[i] << "|" << "\n";
    }
}


/*
 * void init_probability_vector(double *vector, int size){
    int parts = 0;
    double sum = 0;
    for (int i = 0; i < size; i++) {
        parts = parts + i;
    }
    for (int i = 0; i < size; i++){
        vector[i] = (double)i/parts;
        sum = sum + vector[i];
    }
    if (sum < 1) {
        double diff = 1.0 - sum;
        vector[size] = vector[size] + diff;
    }
}
 */
