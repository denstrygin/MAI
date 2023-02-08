#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace NVector {
    template <class T>
    class TVector {
        public:
            typedef T* iterator;
            explicit TVector () noexcept;
            explicit TVector (unsigned long long size) noexcept;
            explicit TVector (unsigned long long size, const T& el) noexcept;
            explicit TVector (const TVector<T>& vec) noexcept;
            ~TVector () noexcept;
            iterator begin () const;
            iterator end () const;
            unsigned long long Size () const;
            unsigned long long Capacity () const;
            bool Empty () const;
            void Reserve (unsigned long long newCap);
            void PushBack (const T& el);
            void PopBack ();
            T& At (unsigned long long i) const;
            void Resize (unsigned long long new_size);
            void Resize (unsigned long long new_size, const T& new_el);
            T& Back () const;
            T& Front () const;
            void Clear ();
            T& operator[] (unsigned long long i);
        private:
            unsigned long long vecSize;
            unsigned long long vecCap;
            T *buff;
    };

//реализация
    template <class T>
    TVector<T>::TVector () noexcept {
        vecSize = 0;
        vecCap = 0;
        buff = nullptr;
    }

    template <class T>
    TVector<T>::TVector (unsigned long long size) noexcept {
        vecSize = 0;
        vecCap = size;
        buff = new T[size];
    }

    template <class T>
    TVector<T>::TVector (unsigned long long size, const T& el) noexcept {
        vecSize = size;
        vecCap = size;
        buff = new T[vecSize];
        for (unsigned long long i = 0; i < vecSize; ++i) {
            buff[i] = el;
        }
    }

    template <class T>
    TVector<T>::TVector (const TVector<T>& vec) noexcept {
        vecSize = vec.vecSize;
        vecCap = vec.vecCap;
        buff = new T[vecSize];
        for (unsigned long long i = 0; i < vecSize; ++i) {
            buff[i] = vec.buff[i];
        }
    }

    template <class T>
    TVector<T>::~TVector () noexcept {
        delete[] buff;
        vecSize = 0;
        vecCap = 0;
        buff = nullptr;
    }
 
    template <class T>
    typename TVector<T>::iterator TVector<T>::begin () const {        
        return buff ; 
    }
     
    template <class T>
    typename TVector<T>::iterator TVector<T>::end () const{
        return buff + vecSize;
    }

    template <class T>
    unsigned long long TVector<T>::Size () const {
        return vecSize;
    }

    template <class T>
    unsigned long long TVector<T>::Capacity () const {
        return vecCap;
    }

    template <class T>
    bool TVector<T>::Empty () const {
        return vecSize == 0 ? true : false;
    }

    template <class T>
    void TVector<T>::Reserve (unsigned long long newCap) {
        if (vecCap == 0) {
            vecCap = 10;
            buff = new T[vecCap];
            return;
        }
        T *newBuff = new T[newCap];
        unsigned long long size = vecSize > newCap ? newCap : vecSize;
        for (unsigned long long i = 0; i < size; ++i) {
            newBuff[i] = buff[i];
        }
        delete[] buff;
        buff = newBuff;
        vecCap = newCap;
    }

    template <class T>
    void TVector<T>::PushBack (const T& el) {
        if (vecSize == vecCap) {
            Reserve (vecCap * 2);
        }
        buff[vecSize] = el;
        vecSize++;
    }

    template <class T>
    void TVector<T>::PopBack () {
        vecSize--;
    }

    template <class T>
    T& TVector<T>::At (unsigned long long i) const {
        return buff[i];
    }

    template <class T>
    void TVector<T>::Resize (unsigned long long new_size) {
        Reserve (new_size);
        vecSize = new_size;    
    }

    template <class T>
    void TVector<T>::Resize (unsigned long long new_size, const T& new_el) {
        Reserve (new_size);
        for (unsigned long long i = vecSize; i < new_size; ++i) {
            buff[i] = new_el;
        }
        vecSize = new_size;
    }

    template <class T>
    T& TVector<T>::Back () const {
        return buff[vecSize - 1];
    }

    template <class T>
    T& TVector<T>::Front () const {
        return buff[0];
    }

    template <class T>
    void TVector<T>::Clear () {
        if (vecSize == 0) {
            return;
        }
        delete[] buff;
        vecSize = 0;
        vecCap = 0;
        buff = nullptr;
    }

    template <class T>
    T& TVector<T>::operator[] (unsigned long long i) {
        return buff[i];
    }
}

#endif
