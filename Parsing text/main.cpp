/** Задание:_____________Разработать программу, которая должна сделать следующее:__________________________________
 * 1. Прочитать содержимое текстового файла. Файл может содержать:
   a. Слова – состоят из латинских строчных и заглавных букв, а также цифр, длинна слова должна быть не более 20 символов
   b. Знаки препинания – «.», «,» «!» «?» «:» «;»
   c. Пробельные символы – пробел, табуляция, символ новой строки.//
 * 2. Отформатировать текст следующим образом:
   a. Не должно быть  пробельных символов отличных от пробела
   b. Не должно идти подряд более одного пробела
   c. Между словом и знаком препинания не должно быть пробела
   d. После знака препинания всегда должен идти пробел
   e. Слова длиной более 10 символов заменяются на слово «Vau!!!»//
 * 3. Преобразовать полученный текст в набор строк, каждая из которых содержит целое количество строк (слово должно
   целиком находиться в строке) и ее длинна не превышает 40 символов.
   Подсказки:
    - Для хранения всего входного текста можно использовать одну строку
    - Можно создать строки содержащие символы принадлежащие какое либо категории, например знаки препинания
    - Для хранения результирующих строк можно использовать vector<string>
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