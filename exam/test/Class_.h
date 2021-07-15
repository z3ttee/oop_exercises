//
// Created by Cedric Zitzmann on 13.07.2021.
//

#ifndef CLION_CLASS__H
#define CLION_CLASS__H
#include <iostream>

using namespace std;

template <class T>
class Try{
    friend  ostream &operator<<(ostream &oF, const Try<T> &x);
public:
    Try(T a, T b) : a(a), b(b) {}
    T getA() const {return a;}
    T getB() const {return b;}
    void setA(T x);
    void setB(T x);
private:
    T a;
    T b;
};/*
template <typename T>
void Try<T>::setA(T x){
  this->a = x;
}
template <typename T>

ostream &operator<<(ostream &oF,const Try<T> &x) {
  oF << "A:" << x.getA() << "B:" << x.getB() << endl;
  return oF;
}
 */
#endif //CLION_CLASS__H

