#pragma comment(lib, "lib/epsteinproject.lib")
/*
 * Программа для тестирования модуля подсчёта вхождений подстроки.
 *
 * Назначение: запрашивает у пользователя имя входного файла (содержащего
 * подстроку и последовательность) и имя выходного файла для отчёта,
 * вызывает функцию count_subsequence_in_file (из модуля arr_proc.h)
 * и записывает в выходной файл результаты выполнения (код возврата,
 * входные данные, количество вхождений). В консоль выводится краткая
 * информация на английском языке.
 *
 * Обрабатываемые коды возврата:
 *   0 – успех,
 *  -1 – ошибка открытия файла,
 *  -2 – файл пуст,
 *  -3 – некорректные данные (пустая подстрока/последовательность,
 *        последовательность короче подстроки),
 *  -4 – повторяющиеся символы в подстроке,
 *   other – неизвестная ошибка.
 *
 * Примечание: выходной файл открывается в режиме перезаписи (создаётся заново).
 */

#include <iostream>
#include <fstream>
#include <string>
#include "dota2.h"

using namespace std;

int main() {
    int code, count;
    string infilename, outfilename, pattern, array;
    cout << "Enter input filename: ";
    cin >> infilename;
    infilename += ".txt";
    ofstream output;
    while (true) {
        cout << "\nEnter output filename: ";
        cin >> outfilename;
        outfilename += ".txt";
        output.open(outfilename, ios::app);
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

    code = count_subsequence_in_file(infilename.c_str(), count);

    if (pattern.length() > 10) {
        pattern.resize(10);
        pattern += "...";
    }

    if (array.length() > 10) {
        array.resize(10);
        array += "...";
    }

    output << "\n==========================\n\n Результат: ";

    switch (code) {
    case 0:
        output << "\nПоследовательность: " << array
            << "\nПодпоследовательность: " << pattern
            << "\nКоличество вхождений: " << count << endl;
        cout << "\nThe program completed successfully! The results have been written to file " << outfilename;
        break;

    case -1:
        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
        output << "\nКод ошибки: -1. Не удалось открыть файл. \nПуть или имя файла: " << infilename;
        break;

    case -2:
        cout << "\nThe program terminated with an error. The report has been written to file " << outfilename;
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
    }

    output.close();
    return 0;
}