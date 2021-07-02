//
// Created by Cedric Zitzmann on 02.07.2021.
//
#pragma once

#ifndef MEASURES_FRACTION_H
#define MEASURES_FRACTION_H

#include "fstream"

using namespace std;

class Fraction;
ostream &operator<<(ostream &outFile, const Fraction &fraction);

class Fraction {

    // Make this a friend of the Fraction class, so we can access private members
    friend ostream &operator<<(ostream &outFile, const Fraction &fraction);

public:
    Fraction(const char *input);
    Fraction(int numerator = 0, int denominator = 1): numerator(numerator), denominator(denominator){}

    Fraction operator+(const Fraction &fraction) const {
        int a = (numerator * fraction.denominator) + (fraction.numerator * denominator);
        int b = denominator * fraction.denominator;
        return {a, b};
    }

    Fraction operator-(const Fraction &fraction) const {
        int a = (numerator * fraction.denominator) - (fraction.numerator * denominator);
        int b = denominator * fraction.denominator;
        return {a, b};
    }

    Fraction operator*(const Fraction &fraction) const {
        int a = numerator * fraction.numerator;
        int b = denominator * fraction.denominator;
        return {a, b};
    }

    Fraction operator/(const Fraction &fraction) const {
        int a = numerator * fraction.denominator;
        int b = denominator * fraction.numerator;
        return {a, b};
    }

    explicit operator double() const {
        return double(numerator) / double(denominator);
    }

private:
    int numerator;
    int denominator;
};

#endif //MEASURES_FRACTION_H
