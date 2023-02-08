#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstring>
#include <new>

namespace NString {
    class TString {
        public:
            explicit TString ();
            TString (const char* cstr) noexcept;
            TString (const TString& str) noexcept;
            ~TString ();
            unsigned int GetLength () const;
            const char* GetStr () const;
            bool Empty () const;
            char& operator[] (unsigned int i) const noexcept;
            TString& operator= (const TString& str) noexcept;
            TString& operator= (const char* cstr) noexcept;
            TString& operator+= (const TString& str);
            friend bool Equal (const TString& str1, const TString& str2);
            friend bool operator== (const TString& str1, const TString& str2);
            friend bool operator!= (const TString& str1, const TString& str2);
            friend std::istream& operator>> (std::istream& input, TString& str);
            friend std::ostream& operator<< (std::ostream& output, const TString& str);
            friend bool operator< (const TString& str1, const TString& str2);
            friend bool operator> (const TString& str1, const TString& str2);
            friend bool operator<= (const TString& str1, const TString& str2);
            friend bool operator>= (const TString& str1, const TString& str2);
        private:
            char* buff;
            unsigned int length;
    };
    const unsigned int MAXLEN = 256;
}

#endif
