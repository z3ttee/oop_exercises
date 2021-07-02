#include <iostream>
#include "messw/messw.h"
#include "fraction/fraction.h"

using namespace std;

istream &operator>>(istream &inFile, Fraction &a){
    string str;
    inFile >> str;
    a = Fraction(str.c_str());

    return inFile;
}

int main(const int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " datei1 datei2 ..." << endl;
        exit(EXIT_FAILURE);
    }

    Messw<Fraction> ges;

    for(int i = 1; i < argc; ++i) {
        cout << "================== Lesen... ==================" << endl;
        ifstream file(argv[i]);

        if(!file) {
            cerr << "Could not read file '" << argv[i] << "'.";
            continue;
        }

        Messw<Fraction> messw;
        Fraction a;

        while(file >> a) {
            messw = messw + a;
        }

        if(!messw) {
            cerr << "Keine gültigen Werte aus Datei '" << argv[i] << "' gelesen." << endl;
            ges = ges + messw;
            continue;
        }

        cout << "Messwerte: " << messw << endl;
        cout << "Gesamtzahl Elemente: " << ~messw << endl;
        cout << "Mittelwert: " << Fraction(messw) << endl;

        ges = ges + messw;
    }

    cout << "================== GESAMT ==================" << endl;
    cout << "Erstes Element: " << ges[0] << endl;
    cout << "Letztes Element: " << ges[~ges - 1] << endl;
    cout << "Mittelwert: " << Fraction(ges) << endl;

    return 0;
}
