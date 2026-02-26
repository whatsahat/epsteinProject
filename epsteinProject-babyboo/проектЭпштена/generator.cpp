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
    for (int i = 0; i < pattern_l; i++) {
        pattern += randASCII();
    }
    for (int i = 0; i < length - pattern_l*pattern_q; i++) {
        array += randASCII();
    }
    int step = length / pattern_q;
    for (int i; i < pattern_q; i++) {
        array.insert(i * pattern_q, pattern);
    }
}

void  AutoGen(int& length, int& pattern_l, int& pattern_q){
    length = 1 + rand() % 1000;
    pattern_l = 1 + rand() % length;
    pattern_q = rand() % (length / pattern_l + 1);
}

void ManualInput(string& pattern, int& length, int& pattern_l, int& pattern_q) {
    
    cout << "\nEnter main array length: ";
    cin >> length; //min 1
    cout << "\nEnter custom pattern (empty for auto): ";
    cin >> pattern;
    if (pattern == "") {
        while (true) {
            cout << "\nEnter pattern array length: ";
            cin >> pattern_l;
            cout << "\nEnter the number of pattern repetitions: ";
            cin >> pattern_q;
            if (length >= pattern_l * pattern_q) {
                break;
            }
            cout << "\nInvalid value. length of subsequence cannot be gretaer that main sequence"
                << "\nMain sequence length: " << length
                << "\nSubsequence length: " << pattern_l
                << "\nNumber of occurences: " << pattern_q
                << "\nSubceq * occur: " << pattern_l * pattern_q;
        }        
    } //добавить проверки
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
    output << pattern << endl << array;
}



int main() {

    srand(static_cast<unsigned>(time(nullptr)));
    GenerateFiles();
	return 0;
}