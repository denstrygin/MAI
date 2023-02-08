#include "string.hpp"

namespace NString {
    const char* ERR_MEM = "ERROR: can't allocate memory for string\n";
    const char* ERR_INDEX = "ERROR: string index out of bounds\n";
    TString::TString () {
        buff = nullptr;
        length = 0;
    }
    TString::TString (const char* cstr) noexcept {
        length = std::strlen(cstr);
        buff = new (std::nothrow) char[length + 1];
        if (!buff) {
            std::cerr << ERR_MEM;
            exit(-1);
        }
        std::memcpy(buff, cstr, length);
        buff[length] = '\0';
    }
    TString::TString (const TString& str) noexcept {
        length = str.length;
        buff = new (std::nothrow) char[length + 1];
        if (!buff) {
            std::cerr << ERR_MEM;
            exit(-1);
        }
        std::memcpy(buff, str.buff, length);
        buff[length] = '\0';
    }
    TString::~TString () {
        length = 0;
        delete[] buff;
    }
    unsigned int TString::GetLength () const {
        return length;
    }
    const char* TString::GetStr () const {
        return buff;
    }
    bool TString::Empty () const {
        return length == 0;
    }
    char& TString::operator[] (unsigned int i) const noexcept {
        if (i >= length) {
            std::cerr << ERR_INDEX;
            exit(-1);
        }
        return buff[i];
    }
    TString& TString::operator= (const TString& str) noexcept {
        length = str.length;
        char* newBuff = nullptr;
        if (buff) {
            delete[] buff;
        }
        if (length != 0) {
            newBuff = new (std::nothrow) char[length + 1];
            if (!newBuff) {
                std::cerr << ERR_MEM;
                exit(-1);
            }
            std::memcpy(newBuff, str.buff, length);
            newBuff[length] = '\0';
        }
        buff = newBuff;
        return *this;
    }
    TString& TString::operator= (const char* cstr) noexcept {
        if (buff) {
            delete[] buff;
        }
        length = std::strlen(cstr);
        buff = new (std::nothrow) char[length + 1];
        if (!buff) {
            std::cerr << ERR_MEM;
            exit(-1);
        }
        std::memcpy(buff, cstr, length);
        buff[length] = '\0';
        return *this;
    }
    TString& TString::operator+= (const TString& str) {
        char* newBuff = new (std::nothrow) char[length + str.length + 1];
        if (!newBuff) {
            std::cerr << ERR_MEM;
            exit(-1);
        }
        for (unsigned int i = 0; i < length; ++i) {
            newBuff[i] = buff[i];
        }
        for (unsigned int i = 0; i < str.length; ++i) {
            newBuff[i + length] = str.buff[i];
        }
        length += str.length;
        newBuff[length] = '\0';
        delete[] buff;
        buff = newBuff;
        return *this;
    }
    bool Equal (const TString& str1, const TString& str2) {
        if (str1.length != str2.length) {
            return false;
        } else {
            unsigned int length = str1.length;
            for (unsigned int i = 0; i < length; ++i) {
                if (tolower(str1[i]) != tolower(str2[i])) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator== (const TString& str1, const TString& str2) {
        if (str1.length != str2.length) {
            return false;
        } else {
            unsigned int length = str1.length;
            for (unsigned int i = 0; i < length; ++i) {
                if (str1[i] != str2[i]) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!= (const TString& str1, const TString& str2) {
        return !(str1 == str2);
    }
    std::istream& operator>> (std::istream& input, TString& str) {
        if (str.buff) {
            delete[] str.buff;
            str.buff = nullptr;
            str.length = 0;
        }
        const unsigned int MAX_LEN = 257;
        char tmp[MAX_LEN] = {'\0'};
        input >> tmp;
        if (input.fail()) {
            return input;
        } 
        str.length = std::strlen(tmp);
        str.buff = new (std::nothrow) char[str.length + 1];
        if (!str.buff) {
            std::cerr << ERR_MEM;
            exit(-1);
        }
        std::memcpy(str.buff, tmp, str.length);
        str.buff[str.length] = '\0';
        return input;
    }
    std::ostream& operator<< (std::ostream& output, const TString& str) {
        if (str.buff) {
            output << str.buff;
        }
        return output;
    }
    bool operator< (const TString& str1, const TString& str2) {
        unsigned int str1Len = str1.GetLength();
        unsigned int str2Len = str2.GetLength();
        unsigned int minLen = str1Len > str2Len ? str2Len : str1Len;
        for (unsigned int i = 0; i < minLen; ++i) {
            if (str1[i] < str2[i]) {
                return true;
            } else if (str1[i] > str2[i]) {
                return false;
            }
        }
        if (str1Len < str2Len) {
            return true;
        }
        return false;
    }
    bool operator> (const TString& str1, const TString& str2) {
        unsigned int str1Len = str1.GetLength();
        unsigned int str2Len = str2.GetLength();
        unsigned int minLen = str1Len > str2Len ? str2Len : str1Len;
        for (unsigned int i = 0; i < minLen; ++i) {
            if (str1[i] > str2[i]) {
                return true;
            } else if (str1[i] < str2[i]) {
                return false;
            }
        }
        if (str1Len > str2Len) {
            return true;
        }
        return false;
    }
    bool operator<= (const TString& str1, const TString& str2) {
        return !(str1 > str2);
    }
    bool operator>= (const TString& str1, const TString& str2) {
        return !(str1 < str2);
    }
}
