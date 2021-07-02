//
// Created by Cedric Zitzmann on 02.07.2021.
//
#pragma once

#ifndef MEASURES_MESSW_H
#define MEASURES_MESSW_H

#include "fstream"

using namespace std;

class Messw {

    friend ostream &operator<<(ostream &outFile, const Messw &messw);

public:
    Messw(): elements(0), arr(nullptr) {}
    Messw(const Messw &orig);
    ~Messw(){
        delete [] arr;
    }

    int operator~() const {
        return this->elements;
    }
    bool operator!() const {
        return this->elements == 0;
    }

    Messw operator+(double a) const;
    Messw operator+(const Messw &a) const;
    operator double() const;
    Messw &operator=(const Messw &a);

    // Read-only
    // (zum Lesen und Ändern müsste eine Referenz zurückgegeben werden!)
    double operator[](const int i) const {
        if(i < 0 || i > this->elements - 1) {
            return 0;
        }

        return this->arr[i];
    }

private:
    Messw(int size): elements(size), arr(new double[size]) {}
    double *arr;
    int elements;
};

ostream &operator<<(ostream &outFile, const Messw &messw);

#endif //MEASURES_MESSW_H
