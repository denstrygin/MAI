#include "LZ78.hpp"

namespace NComp {
    //Конструкторы/Деструкторы
    TId::TId () : pos(0), next('\0') {}

    TId::TId (uint16_t pos, char next) : pos(pos), next(next) {}

    TId::~TId () {}

    uint64_t TId::SizeOfNode () {
        return sizeof(pos) + sizeof(next);
    }
    //Перегрузка для потока из файла и в файл
    std::ifstream &operator>> (std::ifstream &input, TId &node) {
        input.read(reinterpret_cast<char*>(&node.pos), sizeof(node.pos));
        input.read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        return input;
    }

    std::ofstream &operator<< (std::ofstream &output, const TId &node) {
        output.write(reinterpret_cast<const char*>(&node.pos), sizeof(node.pos));
        output.write(reinterpret_cast<const char*>(&node.next), sizeof(node.next));
        return output;
    }

    uint64_t Compress (const std::string &filename) {
        //Читаем из файла
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Can't open file \"" + filename + "\"");
        }
        //Файл записи
        std::ofstream output(filename + ".cmp", std::ios::binary);

        uint64_t oldSize = 0, newSize = 0, toRead = 0;

        file.seekg(0, std::ios::end);
        //Размер текста
        oldSize = file.tellg();
        file.seekg(0);

        std::string str, buffer;
        str.resize(SIZE_OF_TEXTPART);

        char last_char;            
        std::map<std::string, uint64_t> dict;
        //Проверка на велечину текста(больше ли она считываемой части)
        toRead = oldSize > SIZE_OF_TEXTPART ? SIZE_OF_TEXTPART : oldSize;

        file.read(&str[0], toRead);
        uint64_t j = 0;
        for (uint64_t i = 0; i < oldSize; ++i) {
            //Построчно считываем
            if (j == str.size()) {
                j = 0;
                toRead = oldSize - i > SIZE_OF_TEXTPART ? SIZE_OF_TEXTPART : oldSize - i;
                file.read(&str[0], toRead);
            }
            //Пополняем словарь
            if (dict.count(buffer + str[j]) && i != oldSize - 1) {
                buffer += str[j];
            } else {
                uint16_t pos = dict[buffer] == 0 ? 0 : dict[buffer] - 1;
                output << TId(pos, str[j]);
                if (dict.size() != DICT_SIZE) {
                    dict[buffer + str[j]] = dict.size();
                }
                buffer.clear();
                newSize += TId::SizeOfNode();;
            }
            ++j;
        }
        if (buffer != "") {
            last_char = buffer.back();
            buffer.pop_back();
            output << TId(dict[buffer], last_char);
            newSize += TId::SizeOfNode();
        }

        std::cout << "Input filename: " << filename << "\nInput size: " << oldSize
        << "\n\nOutput filename: " << filename + ".cmp" << "\nOutput size: " <<  newSize
        << "\n\nEfficiency: " << (round((double)oldSize / (double)newSize * 10) / 10) << "\n\n";

        file.close();
        output.close();

        return oldSize;
    }

    uint64_t Decompress (const std::string &filename) {
        //Читаем из файла
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Can't open file \"" + filename + "\"");
        }
        //Задаём разархивированному файлу новый формат
        std::string decompfilename = filename;
        decompfilename = std::regex_replace(decompfilename, std::regex(".cmp"), ".dcm");
        std::ofstream output(decompfilename + "p");

        TId node;
        std::string ans, word;
        std::vector<std::string> dict;
        uint64_t inputSize = 0, outputSize = 0;
        dict.push_back("");

        file.seekg(0, std::ios::end);
        inputSize = file.tellg();
        file.seekg(0);

        while (file >> node) {
            //Разархивируем файл, восстанавливая словарь
            word = dict[node.pos] + node.next;
            ans += word;
            if (dict.size() != DICT_SIZE) {
                dict.push_back(word);
            }
            if (ans.size() > SIZE_OF_TEXTPART) {
                outputSize += ans.size();
                output << ans;
                ans.clear();
            }
        }
        if (ans.size() > 0) {
            outputSize += ans.size();
            output << ans;
        }

        std::cout << "Input Filename: " << filename << "\nInput size: " << inputSize
        << "\n\nOutput Filename: " << decompfilename + "p" << "\nOutput size: " << outputSize << "\n";

        file.close();
        output.close();

        return outputSize;
    }
}