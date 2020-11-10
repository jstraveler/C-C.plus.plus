#include <iostream>
#include <string>
#include "cs.h"

/** ������: ������ ��������� �������� ������� (����) ������������� ������ ����������������� ����� ��� ����������
 *  ��������������� ������� ��������� ������ ��������������� ��������� �����������:
 * �) ��� ������� ������ ������� ������ ��������� ������� �������� ���������, ������������ �� ������ ���������
 * ��������� G � ��������� ������;
 * �) ��� ����������� ���������� �������� ������� ����� ������������ ��������� ��������� �������� �������:
 * 1) �������� �������������;
 * 2) �������� ����������;
 * 3) ��������� ��������;
 * �) ������� ������ ���������� �-������������ �������� ������� (������������) ��� ������� ��������� ��������� �
 * ��������� �� �� ������������ ����������� ��������� ������� (�������������);
 * �) �� ���������� �������� ���������� � ������������ � ������������ �������� ������� ������ �������� ���������� ������.
 * ����������� ������ ����� ����������� ��������� ����� ������ � ������ ������ �������.
 */

using namespace std;

// ������ ������� ���������
const int size_matrix = 9;

int main() {
    system("chcp 1251");
    string country[size_matrix] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    string country2[size_matrix] = {"CAN", "USA", "CHE", "SGP", "NZL", "GBR", "JPN", "CZE", "DNK"};
    string characteristic[size_matrix] = {"��������� �������", "������� ���������������", "��������� ��������� ����, ������",
                                          "���������� � �����������", "������� �����", "��������� �����������",
                                          "��������� �����", "������, �����������������", "������������"};

    // ������� ���������� ��������������, ��� ���� ��������, ��� ����� ����������
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

    int *array_of_pointers_bo[size_matrix]; // ������ ���������� �� ������� ��

    int bo_strict_laws[size_matrix][size_matrix]; // �� ��������� �������
    array_of_pointers_bo[0] = *bo_strict_laws;

    int bo_tax_rate[size_matrix][size_matrix]; // �� ������� ���������������
    array_of_pointers_bo[1] = *bo_tax_rate;

    int bo_difficulty_getting_visa_job[size_matrix][size_matrix]; // �� ��������� ��������� ����, ������
    array_of_pointers_bo[2] = *bo_difficulty_getting_visa_job;

    int bo_immigrants_requirements[size_matrix][size_matrix]; // �� ���������� � �����������
    array_of_pointers_bo[3] = *bo_immigrants_requirements;

    int bo_standard_of_living[size_matrix][size_matrix]; // �� ������� �����
    array_of_pointers_bo[4] = *bo_standard_of_living;

    int bo_difficulty_assimilation[size_matrix][size_matrix]; // �� ��������� �����������
    array_of_pointers_bo[5] = *bo_difficulty_assimilation;

    int bo_cost_of_housing[size_matrix][size_matrix]; // �� ��������� �����
    array_of_pointers_bo[6] = *bo_cost_of_housing;

    int bo_climate_location[size_matrix][size_matrix]; // �� ������, �����������������
    array_of_pointers_bo[7] = *bo_climate_location;

    int bo_safety[size_matrix][size_matrix]; // �� ������������
    array_of_pointers_bo[8] = *bo_safety;

    // ������ �� ����������
    for(int column = 0; column < size_matrix; column++) {
        init_bo_matrix(*matrix, array_of_pointers_bo[column], size_matrix, column);
    }

    // ����� ������ ��
    /*for(int i = 0; i < size_matrix; i++) {
        cout << "������� �� " << characteristic[i] << "\n";
        print_bo_matrix(array_of_pointers_bo[i], size_matrix);
        cout << "\n";
    }*/

    // ������ �� ��������� �������������
    for(int i = 0; i < size_matrix; i++) {
        dominance_mechanism(array_of_pointers_bo[i], dominance_characteristic, characteristic[i], dominance_vector, size_matrix);
    }

    cout << "\n" << "��������� ������ ��������� �������������" << "\n";
    print_two_vectors(country, dominance_vector, dominance_characteristic, size_matrix);

    // ������ �� ��������� ����������
    for(int i = 0; i < size_matrix; i++) {
        locking_mechanism(array_of_pointers_bo[i], locking_characteristic, characteristic[i], locking_vector, size_matrix);
    }

    cout << "\n" << "��������� ������ ��������� ����������" << "\n";
    print_two_vectors(country, locking_vector, locking_characteristic, size_matrix);

    // ������ �� ���������� ���������
    for(int i = 0; i < size_matrix; i++) {
        tournament_mechanism(array_of_pointers_bo[i], *tournament_matrix, i, size_matrix);
    }

    cout << "\n" << "��������� ������ ���������� ���������" << "\n";
    //print_matrix(*tournament_matrix, size_matrix);

    // ��������� ������� ������������ ��� ���������� ���������
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            tournament_matrix_priority[j][i] = tournament_matrix[j][i] * weighting_factors_vector[i];
        }
    }

    cout << "\n" << "��������� ������ ���������� ��������� � ������ ������� �������������" << "\n";
    //print_matrix(*tournament_matrix_priority, size_matrix);

    // ������������ ���������� ��������� �� �������
    for (int i = 0; i < size_matrix; i++) {
        for (int j = 0; j < size_matrix; j++) {
            tournament_vector_priority[i] += tournament_matrix_priority[i][j];
        }
    }

    /*cout << "����� ����������� ��� ����������" << endl;
    for (int i = 0; i < size_matrix; i++) {
        cout << tournament_vector_priority[i] << '\t' << country[i] << endl;
    }
    cout << endl;*/

    // ����������
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

    string empty[size_matrix]; // ��� �� ������������ ������� print_two_vectors �� ����� ��
    cout << "\n" << "�������� ��������� ������ ���������� ���������" << "\n";
    print_two_vectors(country2, tournament_vector_priority, empty, size_matrix);

    // ������ ������� �-������������
    for(int column = 0; column < size_matrix; column++) {
        k_max_mechanism(array_of_pointers_bo[column], **k_max_matrix, column, size_matrix);
    }

    // ����� �-������������ �� ���� ��
    for (int i = 0; i < size_matrix; i++) {
        cout << "�-������������ ��� ���������: " <<  characteristic[i] << "\n";
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

    cout << "\n" << "���� �-������������ �� �������" << "\n";
    // ����� �-���� �� �������
    cout << right << setw(6) << "|" << setw(5) << "K1" << "|" << setw(5) << "K2" << "|" << setw(5) << "K3" << "|" << setw(5) << "K4" << "|" << "\n";
    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << setw(5) << k_1[i] << "|" << setw(5) << k_2[i] << "|" << setw(5) << k_3[i] << "|" << setw(5) << k_4[i] << "|" << "\n";
    }
    cout << "\n";

    // ����� ��������� �1 � �3
    /*for (int i = 0; i < size_matrix; i++) {
            cout << right << setw(5) << country[i] << "|" << " ����� �� �1 " << ": " << k_1[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " ����� �� �2 " << ": " << k_2[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " ����� �� �3 " << ": " << k_3[i]  << endl;
    }
    cout << endl;

    for (int i = 0; i < size_matrix; i++) {
        cout << right << setw(5) << country[i] << "|" << " ����� �� �4 " << ": " << k_4[i]  << endl;
    }
    cout << endl;*/

    // ����� ��������� �2 � �4
    /*for (int i = 0; i < size_matrix; i++) {
            cout << right << setw(5) << country[i] << "|" << " ������� �� �2 � �4 " << ": " << k_2_4_optimum[i] << " ���" << endl;
    }*/


    return 0;
}

