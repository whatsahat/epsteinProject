#include <iostream>
#include <fstream>
#include <string>
#include "arr_proc.h"

using namespace std;

int main() {

    int code, count;
    string infilename, outfilename, pattern, array;
    cout << "Enter input filename (f.e. input.txt): ";
    cin >> infilename;
    cout << "\nEnter output filename (f.e. output.txt): ";
    cin >> outfilename;

    ifstream input(infilename);
    ofstream output(outfilename);

    code = array_proc_code(input, count);
    
    getline(input, pattern);
    getline(input, array);

    if (pattern.length() > 10) {
        pattern.resize(10);
        pattern += "...";
    }

    if (array.length() > 10) {
        array.resize(10);
        array += "...";
    }

    output << "Результат: ";

    switch (code) {
    case 0:                    

        output << "\nПоследовательность: " << array
            << "\nПодпоследовательность: " << pattern
            << "\nКоличество вхождений: " << count << endl;

        cout << "\nThe program completed successfully! The results have been written to a file " << outfilename;

        break;

    case -1:

        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
        output << "\nКод ошибки: -1. Не удалось открыть файл. \nПуть или имя файла: " << infilename;
        break;

    case -2:
        cout << "\nThe program terminated with an error. The report has been written to file.";
        output << "\nКод ошибки: -2. Файл пуст. \nПуть или имя файла: " << infilename;
        break;

    case -3: 
        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
        output << "\nКод ошибки: -3. Некорректные данные. \nПуть или имя файла: " << infilename
            << "\nПоследовательность: " << array
            << "\nПодпоследовательность: " << pattern;
        break;

    default:
        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
        output << "\nНеизвестная ошибка. \nПуть или имя файла: " << infilename
            << "\nПоследовательность: " << array
            << "\nПодпоследовательность: " << pattern;
        break;
    };

}