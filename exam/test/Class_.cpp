//
// Created by Cedric Zitzmann on 13.07.2021.
//

#include "Class_.h"

template <typename T>
void Try<T>::setA(T x){
    this->a = x;
}

template <typename T>

void Try<T>::setB(T x) {
    a = x;
}
template <typename T>

ostream &operator<<(ostream &oF,const Try<T> &x) {
    oF << "A:" << x.getA() << "B:" << x.getB() << endl;
    return oF;
}