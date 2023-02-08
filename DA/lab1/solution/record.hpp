#ifndef RECORD_HPP
#define RECORD_HPP

#include "string.hpp"

struct Record {
     unsigned long long key;
     NString::TString val;

     Record& operator= (const Record& rec);
};

std::istream& operator>> (std::istream& input, Record& rec) {
    input >> rec.key >> rec.val;
    return input;
}

std::ostream& operator<< (std::ostream& output, const Record& rec) {
    output << rec.key << " " << rec.val;
    return output;
}

bool operator< (const Record& rec1, const Record& rec2) {
     return rec1.key < rec2.key;
}
bool operator> (const Record& rec1, const Record& rec2) {
     return rec1.key > rec2.key;
}
bool operator<= (const Record& rec1, const Record& rec2) {
     return rec1.key <= rec2.key;
}
bool operator>= (const Record& rec1, const Record& rec2) {
     return rec1.key >= rec2.key;
}
Record& Record::operator= (const Record& rec) {
     key = rec.key;
     val = rec.val;
     return *this;
}
#endif