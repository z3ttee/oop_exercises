#include <iostream>
#include <fstream>

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

ostream &operator<<(ostream &outFile, const Messw &messw) {
    for(int i = 0; i < messw.elements; ++i) {
        outFile << messw.arr[i] << " ";
    }
    return outFile;
}

int main(const int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " datei1 datei2 ..." << endl;
        exit(EXIT_FAILURE);
    }

    Messw ges;

    for(int i = 1; i < argc; ++i) {
        cout << "================== Lesen... ==================" << endl;
        ifstream file(argv[i]);

        if(!file) {
            cerr << "Could not read file '" << argv[i] << "'.";
            continue;
        }

        Messw messw;
        double a;
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
        cout << "Mittelwert: " << double(messw) << endl;

        ges = ges + messw;
    }

    cout << "================== GESAMT ==================" << endl;
    cout << "Erstes Element: " << ges[0] << endl;
    cout << "Letztes Element: " << ges[~ges - 1] << endl;
    cout << "Mittelwert: " << double(ges) << endl;

    return 0;
}
