#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/*генерирует массив с заданной длинной
* имя файла
* длина
* опционально: обязательная подпоследовательность для вхожденния
* опционально: число вхождений конкретной подпоследовательности
*/
void GenerateFiles() {
    string filename, pattern;
    int length, pattern_q;
    cout << "Enter filename: ";
    cin >> filename;
    cout << "\nEnter full array length: ";
    cin >> length;
    cout << "\nEnter pattern array ";
    if(cin.get() != EOF) {
        
        cout << "\nEnter quantity pattern: ";
        cin >> pattern_q;
        //проверка что количество корректное
    }
    
    

}


void TestingProgramm() {

    string filename, array;
    cout << "Enter filename: ";
    cin >> filename;
    ifstream input(filename + ".txt");
    cout << "Enter your array: ";
    cin >> array;
    ProcessArray(input, array);
}

int ProcessArray(ifstream& input, string& array) {

    if (!input.is_open()) return -1;

    char symbol;
    int count = 0;
    while (input.get(symbol)) {

    }

    return 0;
}

int main()
{
    int code;
    int choise;
    cout << "Programm for generatig and processing array\n"
        << "Choose action: \n 1. Generate text files with array \n2. Process array \nYour choice: ";
    while (cin >> choise) {
        if (choise == 1) {
            GenerateFiles();
            break;
        }
        else if (choise == 2) {
            TestingProgramm();
            break;
        }
        else cout << "Wrong number. Try again.\n";
    }
    


    return 0;
}

