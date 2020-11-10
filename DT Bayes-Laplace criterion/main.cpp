#include <iostream>
#include <iomanip>

using namespace std;

/** Задача планирования на год
 * Определить оптимальный объем заказа автомобилей в условиях неравномерного спроса.
 */

void init_matrix_first_year(int *matrix, int size);
void init_probability_matrix(double *probability_matrix, int const *init_matrix, double const *vector, int size);
void eval_mathematical_expectation(double *matrix, int *mathematical_expectation, int size);
template<class T> void print_matrix(T *matrix, int size);
template<class T> void print_vector(T *matrix, int size);

int main() {
    // Init variables
    int size = 5;
    int matrix[size][size];
    double probability_matrix[size][size];
    double probability[5] = {0.1, 0.25, 0.3, 0.2, 0.15};
    int mathematical_expectation[5] = {0, 0, 0, 0, 0};

    // Init matrix
    init_matrix_first_year(*matrix, size);

    // Print matrix
    cout << "Matrix" << "\n";
    print_matrix(*matrix, size);

    // Init probability matrix
    init_probability_matrix(*probability_matrix, *matrix, probability, size);

    // Print probability matrix
    cout << "Probability matrix" << "\n";
    print_matrix(*probability_matrix, size);

    // Evaluate mathematical expectation
    eval_mathematical_expectation(*probability_matrix, mathematical_expectation, size);

    // Print mathematical expectation
    cout << "Mathematical expectation matrix" << "\n";
    print_vector(mathematical_expectation, size);

    return 0;
}

void init_matrix_first_year(int *matrix, int size) {
    int demand = 100; // спрос
    int order = 100;  // заказ
    int price = 49000; // стоимость одной машины
    int price_discont = 15000; // дисконтная стоимость одной машины
    int seb = 25000; // себестоимость 1 автомобиля
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (order > demand) {
                matrix[i*size+j] = ((demand * price) + ((order - demand) * price_discont) - (order * seb));
            }
            else {
                matrix[i*size+j] = (order * price) - (order * seb);
            }
            demand = demand + 50;
        }
        demand = 100;
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

void eval_mathematical_expectation(double *matrix, int *mathematical_expectation, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mathematical_expectation[i] = mathematical_expectation[i] + matrix[i*size+j];
        }
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
