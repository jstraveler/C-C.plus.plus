#include <iostream>
#include <string>
#include "cs.h"

/** Задача: Систем поддержки принятия решений (СППР) «Исследование уровня привлекательности стран для иммиграции»
 *  Разрабатываемая система поддержки должна соответствовать следующим требованиям:
 * А) Как входные данные система должна принимать матрицы бинарных отношений, составленные на основе множества
 * вариантов G и критериев отбора;
 * Б) Для определения наилучшего варианта система будет использовать следующие механизмы принятия решений:
 * 1) Механизм доминирования;
 * 2) Механизм блокировки;
 * 3) Турнирный механизм;
 * В) Система должна определять К-максимальные варианты решений (альтернативы) для каждого бинарного отношения и
 * проверять их на соответствие оптимальным вариантам решения (альтернативам);
 * Г) По завершении процесса вычислений в соответствии с поставленным заданием система должна выводить результаты работы.
 * Результатом работы будет представлен наилучший выбор страны с учетом разных условий.
 */

using namespace std;

// Размер матрицы отношений
const int size_matrix = 9;

int main() {
    system("chcp 1251");
    string country[size_matrix] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    string country2[size_matrix] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    string characteristic[size_matrix] = {"Строгость законов", "Уровень налогооблажения", "Сложность получения визы, работы",
                                          "Требования к иммигрантам", "Уровень жизни", "Сложность ассимиляции",
                                          "Стоимость жилья", "Климат, месторасположение", "Безопасность"};

    // Матрица параметров адаптированная, чем выше значение, тем лучше показатель
    int matrix[size_matrix][size_matrix] = { 3, 2, 3, 3, 5, 3, 3, 4, 5,
                                             3, 1, 2, 2, 5, 2, 3, 3, 3,
                                             2, 2, 2, 1, 5, 2, 1, 5, 5,
                                             1, 1, 2, 2, 4, 3, 1, 2, 5,
                                             4, 3, 4, 3, 4, 3, 3, 2, 5,
                                             3, 1, 2, 2, 5, 3, 1, 2, 4,
                                             2, 1, 2, 1, 5, 2, 1, 1, 4,
                                             4, 3, 4, 4, 4, 4, 4, 4, 4,
                                             4, 2, 3, 2, 5, 3, 2, 4, 5 };

    int dominance_vector[size_matrix] = { 0 };
    string dominance_characteristic[size_matrix];
    int locking_vector[size_matrix] = { 0 };
    string locking_characteristic[size_matrix];
    double tournament_matrix[size_matrix][size_matrix] = { 0 };
    double tournament_matrix_priority[size_matrix][size_matrix] = { 0 };
    double tournament_vector_priority[size_matrix] = { 0 };
    int k_max_matrix[size_matrix][size_matrix][4] = { 0 };
    int k_1[size_matrix] = { 0 };
    int k_2[size_matrix] = { 0 };
    int k_3[size_matrix] = { 0 };
    int k_4[size_matrix] = { 0 };
    int k_2_4_optimum[size_matrix] = { 0 };
    double weighting_factors_vector[size_matrix] = { 0.05, 0.06, 0.2, 0.12, 0.1, 0.12, 0.13, 0.11, 0.11 };

    int *array_of_pointers_bo[size_matrix]; // Массив указателей на матрицы БО

    int bo_strict_laws[size_matrix][size_matrix]; // БО Строгость законов
    array_of_pointers_bo[0] = *bo_strict_laws;

    int bo_tax_rate[size_matrix][size_matrix]; // БО Уровень налогооблажения
    array_of_pointers_bo[1] = *bo_tax_rate;

    int bo_difficulty_getting_visa_job[size_matrix][size_matrix]; // БО Сложность получения визы, работы
    array_of_pointers_bo[2] = *bo_difficulty_getting_visa_job;

    int bo_immigrants_requirements[size_matrix][size_matrix]; // БО Требования к иммигрантам
    array_of_pointers_bo[3] = *bo_immigrants_requirements;

    int bo_standard_of_living[size_matrix][size_matrix]; // БО Уровень жизни
    array_of_pointers_bo[4] = *bo_standard_of_living;

    int bo_difficulty_assimilation[size_matrix][size_matrix]; // БО Сложность ассимиляции
    array_of_pointers_bo[5] = *bo_difficulty_assimilation;

    int bo_cost_of_housing[size_matrix][size_matrix]; // БО Стоимость жилья
    array_of_pointers_bo[6] = *bo_cost_of_housing;

    int bo_climate_location[size_matrix][size_matrix]; // БО Климат, месторасположение
    array_of_pointers_bo[7] = *bo_climate_location;

    int bo_safety[size_matrix][size_matrix]; // БО Безопасность
    array_of_pointers_bo[8] = *bo_safety;

    // Расчет БО параметров
    for(int column = 0; column < size_matrix; column++) {
        init_bo_matrix(*matrix, array_of_pointers_bo[column], size_matrix, column);
    }

    // Вывод матриц БО
    /*for(int i = 0; i < size_matrix; i++) {
        cout << "Матрица БО " << characteristic[i] << "\n";
        print_bo_matrix(array_of_pointers_bo[i], size_matrix);
        cout << "\n";
    }*/

    // Расчет по механизму доминирования
    for(int i = 0; i < size_matrix; i++) {
        dominance_mechanism(array_of_pointers_bo[i], dominance_characteristic, characteristic[i], dominance_vector, size_matrix);
    }

    cout << "\n" << "Результат работы механизма доминирования" << "\n";
    print_two_vectors(country, dominance_vector, dominance_characteristic, size_matrix);

    // Расчет по механизму блокировки
    for(int i = 0; i < size_matrix; i++) {
        locking_mechanism(array_of_pointers_bo[i], locking_characteristic, characteristic[i], locking_vector, size_matrix);
    }

    cout << "\n" << "Результат работы механизма блокировки" << "\n";
    print_two_vectors(country, locking_vector, locking_characteristic, size_matrix);

    // Расчет по турнирному механизму
    for(int i = 0; i < size_matrix; i++) {
        tournament_mechanism(array_of_pointers_bo[i], *tournament_matrix, i, size_matrix);
    }

    cout << "\n" << "Результат работы турнирного механизма" << "\n";
    //print_matrix(*tournament_matrix, size_matrix);

    // Применяем весовые коэффициенты для турнирного механизма
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            tournament_matrix_priority[j][i] = tournament_matrix[j][i] * weighting_factors_vector[i];
        }
    }

    cout << "\n" << "Результат работы турнирного механизма с учетом весовых коэффициентов" << "\n";
    //print_matrix(*tournament_matrix_priority, size_matrix);

    // Суммирование взвешенных элементов по строкам
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            tournament_vector_priority[i] += tournament_matrix_priority[i][j];
        }
    }

    /*cout << "Вывод результатов без сортировки" << endl;
    for (int i = 0; i < size_matrix; i++) {
        cout << tournament_vector_priority[i] << '\t' << country[i] << endl;
    }
    cout << endl;*/

    // Сортировка
    double temp;
    string temp2;
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            if (tournament_vector_priority[i] > tournament_vector_priority[j]) {
                temp = tournament_vector_priority[i];
                tournament_vector_priority[i] = tournament_vector_priority[j];
                tournament_vector_priority[j] = temp;

                temp2 = country2[i];
                country2[i] = country2[j];
                country2[j] = temp2;
            }
        }
    }

    string empty[size_matrix]; // Что бы использовать функцию print_two_vectors не меняя ее
    cout << "\n" << "Итоговый результат работы турнирного механизма" << "\n";
    print_two_vectors(country2, tournament_vector_priority, empty, size_matrix);

    // Расчет матрицы к-максимальных
    for(int column = 0; column < size_matrix; column++) {
        k_max_mechanism(array_of_pointers_bo[column], **k_max_matrix, column, size_matrix);
    }

    // Вывод к-максимальных по всем БО
    for (int i = 0; i < size_matrix; i++) {
        cout << "К-максимальные для параметра: " <<  characteristic[i] << "\n";
        cout << right << setw(6) << "|" << setw(5) << "K1" << "|" << setw(5) << "K2" << "|" << setw(5) << "K3" << "|" << setw(5) << "K4" << "|" << "\n";
        for (int j = 0; j < size_matrix; j++) {
            cout << right << setw(5) << country[j] << "|";
            for (int k = 0; k < 4; k++) {
                cout << right << setw(5) << k_max_matrix[i][j][k] << "|";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    k_max(reinterpret_cast<int *>(*k_max_matrix), k_1, k_2, k_3, k_4, k_2_4_optimum, country, characteristic, size_matrix);

    cout << "\n" << "Итог К-максимальных по странам" << "\n";
    // вывод К-макс по странам
    cout << right << setw(6) << "|" << setw(5) << "K1" << "|" << setw(5) << "K2" << "|" << setw(5) << "K3" << "|" << setw(5) << "K4" << "|" << "\n";
    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << setw(5) << k_1[i] << "|" << setw(5) << k_2[i] << "|" << setw(5) << k_3[i] << "|" << setw(5) << k_4[i] << "|" << "\n";
    }
    cout << "\n";

    // вывод оптимумов К1 и К3
    /*for (int i = 0; i < size_matrix; i++) {
            cout << right << setw(5) << country[i] << "|" << " Сумма по К1 " << ": " << k_1[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " Сумма по К2 " << ": " << k_2[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " Сумма по К3 " << ": " << k_3[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " Сумма по К4 " << ": " << k_4[i]  << endl;
    }
    cout << endl;*/

    // вывод оптимумов К2 и К4
    /*for (int i = 0; i < size_matrix; i++) {
            cout << right << setw(5) << country[i] << "|" << " ОПТИМУМ по К2 и К4 " << ": " << k_2_4_optimum[i] << " раз" << endl;
    }*/


    return 0;
}

