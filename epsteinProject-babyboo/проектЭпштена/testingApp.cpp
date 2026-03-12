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
    ofstream output;
    while (true) {
        cout << "\nEnter output filename (f.e. output.txt): ";
        cin >> outfilename;
        output.open(outfilename);
        if (output.is_open()) break;
        cout << "\nCannot write to file. Wrong file name or access denied. \nFilename: " << outfilename;
    }
        
    
    ifstream input(infilename);
    if (input.is_open()) {
        getline(input, pattern);
        getline(input, array);
        input.close();
    }
    else {
        pattern = "";
        array = "";
    }

    code = array_proc_code(infilename.c_str(), count);
    

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
    case -4:
        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
        output << "\nКод ошибки: -4. Некорректные данные. \nСимволы в подпоследовательности повторяются. \nПуть или имя файла: " << infilename
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

    output.close();
    return 0;
}