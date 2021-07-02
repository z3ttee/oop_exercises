//
// Created by Cedric Zitzmann on 02.07.2021.
//
#pragma once

#ifndef MEASURES_MESSW_H
#define MEASURES_MESSW_H

#include "fstream"

using namespace std;

template <class T>
class Messw;

template <class T>
ostream &operator<<(ostream &outFile, const Messw<T> &messw);

template <class T>
class Messw {

    friend ostream &operator<< <T>(ostream &outFile, const Messw<T> &messw);

public:
    Messw(): elements(0), arr(nullptr) {}
    Messw(const Messw<T> &orig);
    ~Messw(){
        delete [] arr;
    }

    int operator~() const {
        return this->elements;
    }
    bool operator!() const {
        return this->elements == 0;
    }

    Messw<T> operator+(T a) const;
    Messw<T> operator+(const Messw<T> &a) const;
    operator T() const;
    Messw<T> &operator=(const Messw<T> &a);

    // Read-only
    // (zum Lesen und Ändern müsste eine Referenz zurückgegeben werden!)
    double operator[](const int i) const {
        if(i < 0 || i > this->elements - 1) {
            return 0;
        }

        return this->arr[i];
    }

private:
    Messw(int size): elements(size), arr(new T[size]) {}
    T *arr;
    int elements;
};


template <class T>
ostream &operator<<(ostream &outFile, const Messw<T> &messw) {
    for(int i = 0; i < messw.elements; ++i) {
        outFile << messw.arr[i] << " ";
    }
    return outFile;
}

template <class T>
Messw<T>::Messw(const Messw<T> &orig): elements(orig.elements), arr(new double[orig.elements]) {
    for(int i = 0; i < orig.elements; ++i) {
        this->arr[i] = orig.arr[i];
    }
}

template <class T>
Messw<T> Messw<T>::operator+(T a) const {
    Messw messw(this->elements + 1);

    for(int i = 0; i < this->elements; ++i) {
        messw.arr[i] = this->arr[i];
    }

    messw.arr[this->elements] = a;
    return messw;
}

template <class T>
Messw<T> Messw<T>::operator+(const Messw<T> &a) const {
    int newSize = this->elements + a.elements;
    Messw messw = Messw(newSize);

    for(int i = 0; i < this->elements; ++i) {
        messw.arr[i] = this->arr[i];
    }
    for(int i = 0; i < newSize; ++i) {
        messw.arr[this->elements + i] = a.arr[i];
    }

    return messw;
}

template <class T>
Messw<T> &Messw<T>::operator=(const Messw<T> &a) {
    if(&a != this) {
        if (this->elements != a.elements) {
            delete[] this->arr;
            this->elements = a.elements;
            this->arr = new double[this->elements];
        }

        for (int i = 0; i < this->elements; ++i) {
            this->arr[i] = a.arr[i];
        }
    }

    return *this;
}

template <class T>
Messw<T>::operator T() const {
    if(this->elements == 0) return 0;

    double sum = 0;
    for(int i = 0; i < this->elements; ++i) {
        sum += this->arr[i];
    }

    return sum / this->elements;
}


#endif //MEASURES_MESSW_H
