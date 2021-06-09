#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

class Fraction {

    // Make this a friend of the Fraction class, so we can access private members
    friend ostream &operator<<(ostream &outFile, const Fraction &fraction);

public:
    Fraction(const char *input);

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

private:
    Fraction(int numerator = 0, int denominator = 1): numerator(numerator), denominator(denominator){}
    int numerator;
    int denominator;
};

/**
 * Constructor of class Fraction
 * @param input
 */
Fraction::Fraction(const char *input){
    this->numerator = atoi(input);
    const char *divider = strchr(input, '/');

    if(divider == nullptr) {
        this->denominator = 1;
    } else {
        this->denominator = atoi(divider + 1);
    }
}

/**
 * Output fraction. Defines what should happen with the Fraction class if the output operator <<
 * is used in front of the object in code. (Can be seen as equivalent to toString() in Java on every
 * object that can be overwritten)
 * @param outFile Output to write to
 * @param fraction Object to define the << operator for
 * @return outFile as ostream
 */
ostream &operator<<(ostream &outFile, const Fraction &fraction) {
    if(fraction.denominator != 1) {
        outFile << fraction.numerator << "/" << fraction.denominator;
    } else {
        outFile << fraction.numerator;
    }

    return outFile;
}

int main(int argc, const char *argv[]) {
    // double result;  // Bisheriges Zwischenergebnis = linker Operand
    // double input;   // Nächste Zahl = rechter Operand
    int i;

    // 1, 3, 5, ... Eingabeworte (+1 für den Programmnamen) sind ok
    // ==> argc muss gerade sein
    if (argc % 2 != 0) {
        printf("%s: Die Anzahl der Eingaben stimmt nicht!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Fraction result = Fraction(argv[1]); // Erste Zahl
    for (i = 2; i < argc; i += 2) { // in Zweierschritten ab erstem Rechenzeichen
        Fraction input = Fraction(argv[i + 1]);    // nächste Zahl (nach dem Rechenzeichen)
        // Rechenzeichen dazwischen anschauen: 1. Zeichen von i-tem Eingabe-Wort
        // switch geht nur mit einzelnen Zeichen, nicht mit Texten!
        switch (argv[i][0]) {
            case '+':
                result = result + input;
                break;
            case '-':
                result = result - input;
                break;
            case 'x':
                result = result * input;
                break;
            case '/':
                /*if (input == 0) {
                    printf("%s: Division durch 0!\n", argv[0]);
                    exit(EXIT_FAILURE);
                }*/
                result = result / input;
                break;
            /*case 'p':
                result = pow(result, input);
                break;*/
            default:
                cerr << argv[0] << ": " << argv[i][0] << " Kein Rechenzeichen?" << endl;
                exit(EXIT_FAILURE);
        }
    }

    cout << "Ergebnis: " << result;
    exit(EXIT_SUCCESS);
}
