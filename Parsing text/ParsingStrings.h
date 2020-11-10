//REFERENCE, ������ ������ ������������ ��� POSIX, The control characters in ASCII:
// \0 - Null, 0, mark the end of a string, ���������� ����� ������� ��������.
// \a - Bell, 07, ����,
// \b - Backspace, 08, ���������� ������� ������ �� ���� ������ �����.
// \f - Form feed, 0D, to cause a printer to eject paper to the top of the next page, or a video terminal to clear the screen, ����������� ������� �������� � �������� ������ �� ���������.
// \n - Line feed, 0B, moves the print head down one line, ���������� ������� ������ �� ���� ������ ����.
// \r - Carriage return, 0E, moves the printing position to the start of the line, allowing overprinting, ���������� ������� ������ � ������� ����� ���������.
// \t - Horizontal tab, 09, ���������� ������� ������ � ��������� ������� �������������� ���������.
// \v - Vertical tab, 0C, ���������� ������� ������ � ��������� ������� ������������ ���������.
// EOF - End-of-file, 26,

#include <string>
#include <cstring>

using namespace std;

#ifndef LAB2_PARSINGSTRINGS_H
#define LAB2_PARSINGSTRINGS_H

string garbage;

string parsing(string &s) {
    string all_valid_symbols(".,!?:;QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789 ");
    string text;
    string space(" ");
    string q("Z");
    auto ch = s[0];
    try {
        for (unsigned int i = 0; i < s.length() - 1; i++) {
            ch = s[i];
            if (all_valid_symbols.find(ch) != -1) {
                text.push_back(ch);
            } else {
                garbage.push_back(ch);
                text.push_back(space.front());
                //text.push_back(q[0]);
            }
        }
    }
    catch (out_of_range &e) {
        cout << "out_of_range: " << e.what() << "\n";
    }
    return text;
}

string get_garbage() {
    return garbage;
}

string editing_spaces(string &s) {
    string symbols("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789");
    string punctuation_marks(".,!?:;");
    string space(" ");
    string empty("");
    string formatted_text;
    string temp = s;
    auto ch = s[0];
    auto ch_next = s[0];
    auto ch_prev = s[0];
    try {
        for (unsigned int i = 0; i < temp.length() - 1; i++) {
            ch = temp[i];
            ch_next = temp[i + 1];

            if ((ch == space.front()) && (ch_next == space.front())) { // "  " - pass spaces when it more then one
                //i++;
            } else {
                formatted_text.push_back(ch);
            }
        }

        temp = formatted_text;
        formatted_text = "";

        for (unsigned int i = 0; i < temp.length() - 1; i++) {
            if (i == 0) {
                ch = temp[i];
                ch_next = temp[i + 1];
            } else {
                ch = temp[i];
                ch_next = temp[i + 1];
                ch_prev = temp[i - 1];
            }

            if ((symbols.find(ch_prev) != -1) && (ch == space.front()) &&
                (punctuation_marks.find(ch_next) != -1)) { // pass space when "A !"
                i++;
            } else {
                formatted_text.push_back(ch);
            }
        }

        temp = formatted_text;
        formatted_text = "";

        for (unsigned int i = 0; i < temp.length() - 1; i++) {
            ch = temp[i];
            ch_next = temp[i + 1];

            if ((punctuation_marks.find(ch) != -1) && (space.find(ch_next) == -1)) { // add space when "!A" || "!!"
                formatted_text.push_back(ch);
                formatted_text.push_back(space.front());
            } else {
                formatted_text.push_back(ch);
            }
        }
    }
    catch (out_of_range &e) {
        cout << "out_of_range: " << e.what() << "\n";
    }
    return formatted_text;
}

vector<string> get_vector_from_string(string &s) {
    vector<string> Text(0);
    string Temp; // ��������� ������ ��� ��������� ��������
    string space(" "); // ����� ��������� ����� �� �������
    unsigned int begin = 0;
    unsigned int end = 0;
    try {
        for (unsigned int i = 0; i < s.length(); i++) {
            if (s.compare(i, 1, space) == 0) {
                end = i;
                Text.push_back(Temp.assign(s, begin, end - begin));
                begin = i + 1;
                //Text.push_back(space);
            }
        }
    }
    catch (length_error &e) {
        cout << "length_error: " << e.what() << "\n";
    }
    catch (out_of_range &e) {
        cout << "out_of_range: " << e.what() << "\n";
    }
    return Text;
}

vector<string> get_formatted_vector(vector<string> &vec) {
    vector<string> Text(0); // ������������ ������
    string Temp; // ��������� ������ ��� ��������� ��������
    string replace("Vau!!!"); // ���������� ������
    try {
        for (string &word : vec) {
            if (word.length() >= 10 && Temp.length() <= (40 - replace.length())) {
                Temp.append(replace);
                Temp.append(" ");
            } else if (Temp.length() <= (40 - word.length())) {
                Temp.append(word);
                Temp.append(" ");
            } else {
                Text.push_back(Temp);
                Temp = "";
            }
        }
        Text.push_back(Temp);
    }
    catch (length_error &e) {
        cout << "length_error: " << e.what() << "\n";
    }
    catch (out_of_range &e) {
        cout << "out_of_range: " << e.what() << "\n";
    }
    return Text;
}

string trim(string &s) {
    if (s.length() == 0) {
        s = s;
    }
    int begin, end;
    // ����� ������� ��������� �� ����������� ������� ��� ���������� �������� ���������� ������, ���������, ������ ����� ������
    begin = s.find_first_not_of("\b\f\n\r\t\v");
    // ����� ���������� ��������� �� ����������� �������
    end = s.find_last_not_of("\b\f\n\r\t\v");
    if ((begin == string::npos) || (end == string::npos)) {
        s = "";
    }
    // �������� �������������� ������ ��� ���������, �� ������ ����������� ������
    return string(s, begin, end - begin + 1);
}

#endif //LAB2_PARSINGSTRINGS_H
