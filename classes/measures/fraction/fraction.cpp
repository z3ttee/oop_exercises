//
// Created by Cedric Zitzmann on 02.07.2021.
//
#include "fraction.h"
#include "cstring"

ostream &operator<<(ostream &outFile, const Fraction &fraction) {
    if(fraction.denominator != 1) {
        outFile << fraction.numerator << "/" << fraction.denominator;
    } else {
        outFile << fraction.numerator;
    }

    return outFile;
}

Fraction::Fraction(const char *input) {
    this->numerator = atoi(input);
    const char *divider = strchr(input, '/');

    if(divider == nullptr) {
        this->denominator = 1;
    } else {
        this->denominator = atoi(divider + 1);
    }
}
