//
// Created by Cedric Zitzmann on 02.07.2021.
//

#include "messw.h"

ostream &operator<<(ostream &outFile, const Messw &messw) {
    for(int i = 0; i < messw.elements; ++i) {
        outFile << messw.arr[i] << " ";
    }
    return outFile;
}

Messw::Messw(const Messw &orig): elements(orig.elements), arr(new double[orig.elements]) {
    for(int i = 0; i < orig.elements; ++i) {
        this->arr[i] = orig.arr[i];
    }
}

Messw Messw::operator+(double a) const {
    Messw messw(this->elements + 1);

    for(int i = 0; i < this->elements; ++i) {
        messw.arr[i] = this->arr[i];
    }

    messw.arr[this->elements] = a;
    return messw;
}
Messw Messw::operator+(const Messw &a) const {
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

Messw &Messw::operator=(const Messw &a) {
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

Messw::operator double() const {
    if(this->elements == 0) return 0;

    double sum = 0;
    for(int i = 0; i < this->elements; ++i) {
        sum += this->arr[i];
    }

    return sum / this->elements;
}
