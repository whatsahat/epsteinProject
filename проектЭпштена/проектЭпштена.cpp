#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "arr_proc.h"


using namespace std;

/* Программа для обработки символьной последовательности
*  Осуществялет поиск вхождений заданной подпоследовательности
*  в основную последовательность
*  
* 
*  Список кодов ошибок:
*  -1 - не удалось открыть файл
*  -2 - файл пуст
*  -3 - некорректные данные 
*/



void ProcessArray(string& array, string& pattern, int& count) {

    count = 0;

    for (int i = 0; i <= array.length() - pattern.length(); i++) {
        bool match = true;
        for (int j = 0; j < pattern.length(); j++) {
            if (array[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

}

int array_proc_code(ifstream& input, int& count)
{



    if (!input.is_open()) return -1;


    if (input.eof()) {
        return -2;
    }

    string pattern, array;

    getline(input, pattern);
    getline(input, array);


    if (array == "" || pattern == "" || array.length() < pattern.length()) {
        return -3;
    }

    ProcessArray(array, pattern, count);

    return 0;
}

