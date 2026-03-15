/*
 * Модуль для подсчёта количества вхождений подстроки в последовательность символов.
 *
 * Основная функция: count_subsequence_in_file(const char* infilename, int& count)
 *
 * Назначение: открывает файл с именем infilename, читает из него первую строку
 * (искомая подстрока pattern) и вторую строку (последовательность символов array),
 * после чего подсчитывает количество вхождений pattern в array.
 * Подсчёт выполняется методом индуктивной функции (конечный автомат),
 * что гарантирует линейную сложность и константную дополнительную память.
 *
 * Входные параметры:
 *   infilename – имя входного файла.
 *   count      – ссылка на целочисленную переменную, в которую будет записан результат.
 *
 * Возвращаемое значение (код завершения):
 *    0 – успешное выполнение, count содержит количество вхождений.
 *   -1 – не удалось открыть файл (не существует, нет прав доступа и т.п.).
 *   -2 – файл пуст (не содержит ни одной строки).
 *   -3 – некорректные данные: пустая подстрока, пустая последовательность,
 *        или длина последовательности меньше длины подстроки.
 *   -4 – в подстроке обнаружены повторяющиеся символы (нарушение условия задачи).
 *
 * Примечание: символы в подстроке должны быть различны; если это условие нарушено,
 * функция возвращает -4, даже если формально подсчёт возможен.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "arr_proc.h"

using namespace std;

static bool hasUniqueChars(const string& s) {
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i + 1; j < s.length(); ++j) {
            if (s[i] == s[j]) return false;
        }
    }
    return true;
}

static int countOccurrencesInString(const string& array, const string& pattern) {
    
    int L = pattern.length();
    int cur_len = 0;
    int cnt = 0;
    for (char ch : array) {
        if (cur_len < L && ch == pattern[cur_len]) {
            ++cur_len;
            if (cur_len == L) {
                ++cnt;
                cur_len = 0;
            }
        }
        else if (ch == pattern[0]) {
            cur_len = 1;
        }
        else {
            cur_len = 0;
        }
    }
    return cnt;
}

int count_subsequence_in_file(const char* infilename, int& count) {
    
    ifstream input(infilename);

    if (!input.is_open()) {
        return -1;
    }

    if (input.peek() == ifstream::traits_type::eof()) {
        return -2;
    }

    string pattern, array;

    if (!getline(input, pattern) || pattern.empty()) {
        return -3;
    }

    if (!hasUniqueChars(pattern)) {
        return -4;
    }

    if (!getline(input, array) || array.empty()) {
        return -3;
    }

    if (array.length() < pattern.length()) {
        return -3;
    }

    count = countOccurrencesInString(array, pattern);
    return 0;
}