#ifndef LZ78_HPP
#define LZ78_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <map>
#include <vector>

//Часть текста, подгружаемая для архивации
const uint64_t SIZE_OF_TEXTPART = (1 << 10) * 64;
//Словарь
const uint64_t DICT_SIZE = 1 << 16;

namespace NComp {
    //Класс, объектами которого являются узлы, хронящие текущу позицию и следущий символ
    class TId {
    public:
        uint16_t pos;
        char next;

        TId ();
        TId (uint16_t pos, char next);
        ~TId ();

        static uint64_t SizeOfNode ();
        
        friend std::ifstream &operator>> (std::ifstream &input, TId &node);
        friend std::ofstream &operator<< (std::ofstream &output, const TId &node);
    };
    uint64_t Compress (const std::string &filename);
    uint64_t Decompress (const std::string &filename);
}

#endif