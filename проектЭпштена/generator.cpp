


#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

const int ALPHABET_SIZE = 95;

char randASCII() {
    return static_cast<char>(32 + rand() % ALPHABET_SIZE);
}

bool hasUniqueChars(const string& s) {
    for (size_t i = 0; i < s.length(); ++i) {
        for (size_t j = i + 1; j < s.length(); ++j) {
            if (s[i] == s[j]) return false;
        }
    }
    return true;
}

void Generate_Arrays(string& array, string& pattern, int length, int pattern_l, int pattern_q) {
    if (pattern.empty()) {
        if (pattern_l > ALPHABET_SIZE) {
            cerr << "Error: cannot generate unique pattern of length " << pattern_l
                 << ". Maximum length = " << ALPHABET_SIZE << endl;
            pattern_l = ALPHABET_SIZE;
        }
        while (pattern.size() < static_cast<size_t>(pattern_l)) {
            char c = randASCII();
            bool used = false;
            for (char ex : pattern) {
                if (ex == c) {
                    used = true;
                    break;
                }
            }
            if (!used) pattern += c;
        }
    }

    array.clear();
    array.reserve(length);
    for (int i = 0; i < length; ++i) {
        array += randASCII();
    }

    if (pattern_q > 0) {
        int step = length / pattern_q;
        if (step < pattern_l) step = pattern_l;
        for (int i = 0; i < pattern_q; ++i) {
            int pos = i * step;
            if (pos + pattern_l > length)
                pos = length - pattern_l;
            for (int j = 0; j < pattern_l; ++j) {
                array[pos + j] = pattern[j];
            }
        }
    }
}

void AutoGen(int& length, int& pattern_l, int& pattern_q) {
    length = 1 + rand() % 1000;
    pattern_l = 1 + rand() % min(length, ALPHABET_SIZE);
    pattern_q = rand() % (length / pattern_l + 1);
}

int safeInput(int minVal, int maxVal, const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            else {
                cout << "Error: number must be between " << minVal << " and " << maxVal << ". Try again.\n";
            }
        }
        else {
            cout << "Input error. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void ManualInput(string& pattern, int& length, int& pattern_l, int& pattern_q) {
    length = safeInput(1, 1000, "Enter main sequence length (1-1000): ");

    cout << "Enter subsequence (leave empty for auto generation): ";
    getline(cin, pattern);

    if (pattern.empty()) {
        pattern_l = safeInput(1, min(length, ALPHABET_SIZE),
                              "Enter subsequence length (1-" + to_string(min(length, ALPHABET_SIZE)) + "): ");
    }
    else {
        // Проверка уникальности и длины введённой подстроки
        pattern_l = pattern.length();
        while (!hasUniqueChars(pattern) || pattern_l > length) {
            cout << "Error: characters in subsequence must be unique and shorter that sequence. Please enter another subsequence: ";
            getline(cin, pattern);
            pattern_l = pattern.length();
        }
        if (pattern_l > ALPHABET_SIZE) {
            cout << "Warning: subsequence length exceeds alphabet size (" << ALPHABET_SIZE
                 << "). Uniqueness of characters is not guaranteed.\n";
        }
    }

    int maxQ = length / pattern_l;
    pattern_q = safeInput(0, maxQ, "Enter number of occurrences (0-" + to_string(maxQ) + "): ");
}

/*
 * Программа-генератор тестовых файлов для лабораторной работы.
 *
 * Назначение: создаёт текстовый файл, содержащий последовательность символов,
 * в которой гарантированно присутствует заданное количество вхождений указанной
 * подстроки (или сгенерированной автоматически). Подстрока может быть введена
 * пользователем или сгенерирована автоматически с уникальными символами.
 *
 * Формат выходного файла:
 *   первая строка – искомая подстрока (pattern),
 *   вторая строка – последовательность символов (array).
 *
 * Режимы работы:
 *   1. Автоматическая генерация – все параметры (длина последовательности,
 *      длина подстроки, количество вхождений) выбираются случайным образом
 *      в разумных пределах. Подстрока генерируется автоматически.
 *   2. Ручной ввод – пользователь последовательно задаёт:
 *      - длину последовательности (целое число от 1 до 1000);
 *      - подстроку (может быть пустой, тогда она генерируется автоматически);
 *      - если подстрока введена вручную, её длина определяется автоматически,
 *        и выполняется проверка уникальности символов (повтор символов не допускается);
 *      - количество вхождений (от 0 до максимально возможного, определяемого
 *        длинами последовательности и подстроки).
 *
 * Генерация символов: используются печатные ASCII-символы с кодами 32–126.
 * При автоматической генерации подстроки гарантируется уникальность символов.
 *
 * Обработка ошибок: проверяется корректность ввода, создание файла.
 * При неверных данных программа запрашивает повторный ввод.
 */
void GenerateFiles() {
    string array, pattern;
    int length = 0, pattern_l = 0, pattern_q = 0;
    string filename;
    int choice;

    cout << "Enter output file name (without extension): ";
    cin >> filename;
    filename += ".txt";

    while (true) {
        cout << "\nChoose mode:\n1. Auto generation\n2. Manual input\nYour choice: ";
        if (cin >> choice) {
            if (choice == 1 || choice == 2) {
                cin.ignore();
                break;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid choice. Try again.\n";
    }

    if (choice == 1) {
        AutoGen(length, pattern_l, pattern_q);
        pattern = "";
    }
    else {
        ManualInput(pattern, length, pattern_l, pattern_q);
    }

    Generate_Arrays(array, pattern, length, pattern_l, pattern_q);

    ofstream output(filename);
    if (!output) {
        cout << "Error: cannot create file " << filename << endl;
        return;
    }

    output << pattern << endl << array;
    output.close();

    cout << "=============================";
    cout << "\nFile " << filename << " created successfully.\n";
    cout << "Subsequence: \"" << pattern << "\"\n";
    cout << "Sequence length: " << length << "\n";
    cout << "Number of occurrences: " << pattern_q << "\n";
    cout << "=============================";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    GenerateFiles();
    return 0;
}
