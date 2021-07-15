#include <iostream>
#include <fstream>

using namespace std;

class Messwert {

    friend ostream &operator<<(ostream &outFile, const Messwert &messw);

public:
    Messwert(): size(0), vals(nullptr){}
    Messwert(const Messwert &orig);
    ~Messwert() {
        delete [] vals;
    }

    int operator~() const {
        return size;
    }

    bool operator!() const {
        return size == 0;
    }

    // const am Ende sorgt dafür, dass nicht verändert werden kann
    // -> operator[] nur zum Lesen
    double operator[](const int index) const {
        if(index >= size || index < 0) return 0;
        return vals[index];
    }

    Messwert operator+(double a) const;
    Messwert operator+(const Messwert &a) const;
    Messwert &operator=(const Messwert &orig);

    operator double() const;

private:
    Messwert(int size): size(size), vals(new double[size]){}
    int size;
    double *vals;
};

Messwert::Messwert(const Messwert &orig): size(orig.size), vals(new double[size]) {
    for(int i = 0; i < size; ++i) {
        vals[i] = orig.vals[i];
    }
}

Messwert Messwert::operator+(double a) const {
    Messwert messw(size + 1);

    for(int i = 0; i < size; ++i) {
        messw.vals[i] = vals[i];
    }

    messw.vals[size] = a;
    return messw;
}

Messwert Messwert::operator+(const Messwert &a) const {
    Messwert messw(size + a.size);

    for(int i = 0; i < size; ++i) {
        messw.vals[i] = vals[i];
    }

    for(int i = 0; i < messw.size; ++i) {
        messw.vals[size + i] = a.vals[i];
    }

    return messw;
}

Messwert &Messwert::operator=(const Messwert &orig) {
    if(this != &orig) {
        // Größe passt nicht
        // -> Array neu anlegen
        if(size != orig.size) {
            delete [] vals;

            size = orig.size;
            vals = new double[size];
        }

        for(int i = 0; i < orig.size; ++i) {
            vals[i] = orig.vals[i];
        }
    }

    return *this;
}

Messwert::operator double() const {
    if(size == 0) return 0;

    double sum = 0;
    for(int i = 0; i < size; ++i) {
        sum += vals[i];
    }

    return sum / size;
}

ostream &operator<<(ostream &outFile, const Messwert &messw) {
    for(int i = 0; i < messw.size; ++i) {
        outFile << "Wert #" << i + 1 << " >> " << messw.vals[i] << endl;
    }

    return outFile;
}

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        cout << "Aufruf: " << argv[0] << " <inFile> <inFile2> ..." << endl;
        return 0;
    }

    Messwert messges;

    for(int i = 1; i < argc; ++i) {
        ifstream file(argv[i]);

        cout << endl << "========= " << argv[i] << " =========" << endl;

        if(!file) {
            cerr << "Could not read file" << endl;
            continue;
        }

        Messwert messw;
        double a;

        while(file >> a) {
            messw = messw + a;
        }

        if(!file.eof()) {
            cerr << "Error occured when reading file" << endl;
            continue;
        }

        if(!messw) {
            cout << "Keine Werte aus " << argv[i] << " gelesen" << endl;
            continue;
        } else {
            cout << ~messw << " Werte eingelesen." << endl;
            cout << "Mittelwert: " << double(messw) << endl << endl;
            cout << messw << endl;
        }

        messges = messges + messw;
    }

    cout << "========= Gesamt =========" << endl;
    cout << "Erster Wert: " << messges[0] << endl;
    cout << "Letzter Wert: " << messges[~messges - 1] << endl;
    cout << "Gesamter Mittelwert: " << double(messges) << endl;
    cout << "Gesamte Anzahl Werte: " << ~messges << endl;

    return 0;
}
