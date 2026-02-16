#include <iostream>
#include <string>

using namespace std;
/*
    Модуль для генерации тестовых файлов
    Настраиваемые характеристики для генерации:
    1. Файл вывода
    2. Длина последовательности
    3. Длина подпоследоватеьности для автоматической генерации, либо ручной ввод
    4. Количество вхождений подпоследовательности
*/

int generate_number(int start, int end) {

}

bool isAutoGen() {

}

void GenerateFiles() {

    string filename, pattern, length, pattern_q;
    cout << "Enter filename for saving result: ";
    cin >> filename;
    cout << "\n(!) You can skip all answer options and choose fully automatic generation. Simply press Enter for each question.";
    cout << "\nEnter main array length: ";
    cin >> length;
    cout << "\nEnter pattern array: ";
    cin >> pattern;
    if (pattern == "") {
        cout << "\nEnter pattern array length: ";
    }
    cout << "\nEnter the number of pattern repetitions: ";
    cin >> pattern_q;
    


}



int main() {

	return 0;
}