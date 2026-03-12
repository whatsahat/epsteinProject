#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>


using namespace std;


/*
    Модуль для генерации тестовых файлов
    Настраиваемые характеристики для генерации:
    1. Файл вывода
    2. Длина последовательности
    3. Длина подпоследоватеьности для автоматической генерации, либо ручной ввод
    4. Количество вхождений подпоследовательности
*/

char randASCII() {
    return static_cast<char>(32 + rand() % 95);
}

int Generate_Arrays(string& array, string& pattern, int length, int pattern_l, int pattern_q) {
    if (pattern.empty()) {
        while (pattern.size() < pattern_l) {
            char c = randASCII();
            bool isUsed = false;
            for (char ex : pattern) {
                if (ex == c) {
                    isUsed = true;
                    break;
                }
            }
            if (!isUsed) {
                pattern += c;
            }
        }
    }

    for (int i = 0; i < length; i++) {
        array += randASCII();
    }

    if (pattern_q > 0) {
        int step = length / pattern_q;
        if (step < pattern_l) step = pattern_l;
        for (int i = 0; i < pattern_q; i++) {
            int pos = i * step;
            if (pos + pattern_l > length) pos = length - pattern_l;
            for (int j = 0; j < pattern_l; j++) {
                array[pos + j] = pattern[j];
            }
        }
    }
    
}

void  AutoGen(int& length, int& pattern_l, int& pattern_q){
    length = 1 + rand() % 1000;
    pattern_l = 1 + rand() % length;
    pattern_q = rand() % (length / pattern_l + 1);
}

int safeInput() {
    int value;
    while (true) {
        cin >> value;
        if (value >= 1 && value <= 1000) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        else {
            cout << "Error. The number must be between 1 and 1000.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void ManualInput(string& pattern, int& length, int& pattern_l, int& pattern_q) {
    
    cout << "\nEnter main array length: ";
    length = safeInput();
    cout << "\nEnter custom pattern (empty for auto): ";
    getline(cin, pattern);
    if (pattern.empty()) {
        cout << "\nEnter pattern array length: ";
        pattern_l = safeInput();
        cout << "\nEnter the number of pattern repetitions (from 0 to " << length / pattern_l << "): ";
        pattern_q = safeInput();
    }
    else {
    }
            cout << "\nInvalid value. length of subsequence cannot be greater that main sequence"
                << "\nMain sequence length: " << length
                << "\nSubsequence length: " << pattern_l
                << "\nNumber of occurences: " << pattern_q
                << "\nSubceq * occur: " << pattern_l * pattern_q;
            //добавить проверки
}

void GenerateFiles() {
    string array, pattern;
    int length, pattern_l, pattern_q;
    string filename;
    int choice;
    cout << "Enter filename for saving result: ";
    cin >> filename;
    ofstream output(filename + ".txt");
    //добавить проверку что файл читается 
    while (true) {
        cout << "\nChoose option: \n1. Auto generation. \n2. Manual input.";
        cin >> choice;
        if (choice == 1) {
            AutoGen(length, pattern_l, pattern_q); break;
        }
        else if (choice == 2) {
            ManualInput(pattern, length, pattern_l, pattern_q); break;
        }
        cout << "Wrong choice. Try again";
    }    
    Generate_Arrays(array, pattern, length, pattern_l, pattern_q);
    if (!output) {
        cout << "Error. Cannot create file " << filename << endl; return;
    }
    output << pattern << endl << array;
    output.close();
    cout << "File " << " created successfuly.";
}



int main() {

    srand(static_cast<unsigned>(time(nullptr)));
    GenerateFiles();
	return 0;
}