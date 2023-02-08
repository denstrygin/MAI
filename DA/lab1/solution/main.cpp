#include <iostream>
#include "vector.hpp"
#include "record.hpp"
#include "bucketsort.hpp"

int main () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    NVector::TVector<Record> data;
    Record rec;
    while (std::cin >> rec) {
        data.PushBack(rec);
    }
    BucketSort(data);
    unsigned long long size = data.Size();
    for (unsigned int i = 0; i < size; ++i) {
        std::cout << data[i] << "\n";
    }
    return 0;
}
