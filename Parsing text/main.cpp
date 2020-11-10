/** �������:_____________����������� ���������, ������� ������ ������� ���������:__________________________________
 * 1. ��������� ���������� ���������� �����. ���� ����� ���������:
   a. ����� � ������� �� ��������� �������� � ��������� ����, � ����� ����, ������ ����� ������ ���� �� ����� 20 ��������
   b. ����� ���������� � �.�, �,� �!� �?� �:� �;�
   c. ���������� ������� � ������, ���������, ������ ����� ������.//
 * 2. ��������������� ����� ��������� �������:
   a. �� ������ ����  ���������� �������� �������� �� �������
   b. �� ������ ���� ������ ����� ������ �������
   c. ����� ������ � ������ ���������� �� ������ ���� �������
   d. ����� ����� ���������� ������ ������ ���� ������
   e. ����� ������ ����� 10 �������� ���������� �� ����� �Vau!!!�//
 * 3. ������������� ���������� ����� � ����� �����, ������ �� ������� �������� ����� ���������� ����� (����� ������
   ������� ���������� � ������) � �� ������ �� ��������� 40 ��������.
   ���������:
    - ��� �������� ����� �������� ������ ����� ������������ ���� ������
    - ����� ������� ������ ���������� ������� ������������� ����� ���� ���������, �������� ����� ����������
    - ��� �������� �������������� ����� ����� ������������ vector<string>
  */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//*************User library*************
#include "InputOutput.h"
#include "ParsingStrings.h"

using  namespace std;

int main() {
    system("chcp 1251"); // Encoding for RUS letters
    string file_location = "text.h"; // File location
    string input_text; // String for input text
    string allSymbols(".,!?:;QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789 \n\t"); // All matching symbols
    string punctuation_marks(".,!?:;"); // All matching punctuation marks
    string Temp; // String for parsing
    //string garbage; // String for unmatching symbols
    vector<string> formatted_text; // Vector for processing text after parsing

    read(file_location, input_text, formatted_text); // Read text from file

    Temp = parsing(input_text); // Parsing text
    garbage = get_garbage();

    //cout << "\nParsing text\n" << Temp << "\n";
    //printString(Temp);
    Temp = trim(Temp);
    Temp = editing_spaces(Temp);
    //cout << "\n-----Editing text-----\n" << Temp << "\n";
    //printString(Temp);
    formatted_text = get_vector_from_string(Temp);
    //cout << "\n" << formatted_text.size() << "\n";
    //cout << "\n-----Vector-----\n";
    //printArray(formatted_text);
    formatted_text = get_formatted_vector(formatted_text);
    cout << "\n------Formatted vector-----\n";
    printArray(formatted_text);
    //cout << "\n-----Garbage-----\n" << garbage << "\n";
    return 0;
}