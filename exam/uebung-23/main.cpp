#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_LINE_LEN = 4096;

template<typename T>

struct WertePaar {
    T val;
    int cnt;
};

template<typename T, int size>
class Messwert;

template<typename T, int size>
ostream &operator<<(ostream &outFile, const Messwert<T, size> &value);

template<typename T, int size>
class Messwert {

    friend ostream &operator<< <T, size>(ostream &outFile, const Messwert<T, size> &value);

public:
    Messwert(): used(0){}

    void count(const T &value);
    // void print();

private:
    WertePaar<T> arr[size];
    int used;
};

template<typename T, int size>
void Messwert<T, size>::count(const T &value) {
    for(int i = 0; i < used; ++i) {
        if(arr[i].val == value) {
            ++arr[i].cnt;
            return;
        }
    }

    if(used >= size){
        cerr << "Fehler: Array voll!" << endl;
        exit(EXIT_FAILURE);
    }

    arr[used].val = value;
    arr[used].cnt = 1;
    ++used;
}

/*template<typename T, int size>
void Messwert<T, size>::print() {
    for(int i = 0; i < used; ++i) {
        cout << "Wert: " << arr[i].val << " - Anzahl: " << arr[i].cnt << endl;
    }
}*/

template<typename T, int size>
ostream &operator<<(ostream &outFile, const Messwert<T, size> &value) {
    for(int i = 0; i < value.used; ++i) {
        outFile << "Wert: " << value.arr[i].val << " - Anzahl: " << value.arr[i].cnt << endl;
    }

    return outFile;
}

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " <inFile>" << endl;
        return 0;
    }

    ifstream inFile(argv[1]);

    if(!inFile) {
        cerr << "Error: Datei kann nicht geöffnet werden." << endl;
        return 0;
    }

    Messwert<char, 30> charArray;
    Messwert<string, 1000> stringArray;
    Messwert<int, 30> lenArray;

    char input[MAX_LINE_LEN];
    while(inFile.getline(input, MAX_LINE_LEN)) {

        int inEinemWort = -1;
        for(int i = 0; i <= strlen(input); ++i) {
            // Enthält Index des 1. Buchstabens eines Wortes oder -1 wenn derzeit kein Wort

            if(isalpha(input[i])) {
                if(inEinemWort == -1) {
                    inEinemWort = i;
                }

                // Buchstabe zählen
                charArray.count(tolower(input[i]));
            } else {
                if(inEinemWort != -1) {
                    string word(&(input[inEinemWort]), i - inEinemWort);
                    stringArray.count(word);
                    lenArray.count(word.length());
                    inEinemWort = -1;
                }
            }
        }

    }

    if(!inFile.eof()) {
        cerr << "Fehler: Zeile konnte nicht gelesen werden." << endl;
        return 0;
    }

    cout << "======= Buchstaben =======" << endl;
    // charArray.print();
    cout << charArray << endl;

    cout << endl << "======= Woerter =======" << endl << endl;
    // stringArray.print();
    cout << stringArray << endl;

    cout << endl << "======= Laengen =======" << endl << endl;
    // lenArray.print();
    cout << lenArray << endl;

    return 0;
}
