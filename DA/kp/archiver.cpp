#include "LZ78.hpp"

using namespace std;
using namespace NComp;

//Справка
void usage () {
    cout << "Usage: ./kp [option] file.."
    << "\nOptions:"
    << "\n\t-h(--help) Display all information about program"
    << "\n\t-c(--compress) [filename] - Only compress file and give new extension \"[filename].cmp\""
    << "\n\t-d(--decompress) [filename] - Only decompress file and give extension \"[filename].dcmp\""
    << "\n\t-t(--test) [filename] - Compress, decompress and then analyze efficiency\n";
}

int main (int argc, char *argv[]) {
    uint64_t sizeOld, sizeNew;
    try {
        //Проверка на корректность кол-ва аргументов
        if (
            argc < 2 ||
            argc > 3 ||
            ((string(argv[1]) == "-h" || string(argv[1]) == "--help") && argc != 2) || 
            ((string(argv[1]) != "-h" && string(argv[1]) != "--help") && argc != 3)
        ) {
            throw -1;
        }
        //Ключи и их функции
        string command(argv[1]);
        if (command == "-h" || command == "--help") {
            usage();
        } else if (command == "-c" || command == "--compress") {
            sizeOld = Compress(argv[2]);
        } else if (command == "-d" || command == "--decompress") {
            sizeNew = Decompress(argv[2]);
        } else if (command == "-t"|| command == "--test") {
            sizeOld = Compress(argv[2]);
            sizeNew = Decompress(string(argv[2]) + ".cmp");
            if (sizeNew == sizeOld) {
                cout << "\nСongratulation\n\n";
            }
            else {
                cerr << "\nFaild and Pain\n\n";
            }
        } else {
            throw -2;
        }
    //Информация об ошибках
    } catch (int a) {
        string error = "For more information use my program with key \"-h\" or \"--help\".\n";
        if (a == -1) {
            cerr << "./kp: error: Incorrect count of arguments.\n" << error;
        } else {
            cerr << "./kp: error: Invalid command.\n" << error;
        }
    }
    return 0;
}