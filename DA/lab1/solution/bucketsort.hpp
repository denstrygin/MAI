#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP

#include "vector.hpp"

template <class T>
bool Sorted(NVector::TVector<T>& data) {
    unsigned long long size = data.Size();
   for (unsigned long long i = 1; i < size; ++i) {
        if (data[i] < data[i - 1]) {
            return false; 
        }
   }
   return true;
}

template <class T>
unsigned long long GetKey (const T& el){
    return el.key;
}

template <class T>
void BucketSort (NVector::TVector<T>& data){
    if (Sorted(data)) {
        return;
    }

    unsigned long long size = data.Size();
    const int NUM = 8;
    int n = 64 / NUM;
    unsigned long long x = (1UL << NUM) - 1;

    for(int i = 0; i < n; ++i) {
        NVector::TVector<T> buckets[1UL << NUM];
        for(unsigned long long j = 0; j < size; ++j) {
            auto el = GetKey(data[j]) & x;
            el = el >> (i * NUM);
            buckets[el].PushBack(data[j]);
        }
        x = x << NUM;
        unsigned long long pos = 0;
        unsigned long long count = 1UL << NUM;
        for (unsigned long long i = 0; i < count; ++i){
            int buckSize = buckets[i].Size();
            for (unsigned long long j = 0; j < buckSize; ++j){
                data[pos] = buckets[i][j];
                pos++;
            }
        }
        if(Sorted(data)) {
            break;
        }
    }
}

#endif
