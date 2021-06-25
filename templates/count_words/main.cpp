#include <iostream>
#include <fstream>

using namespace std;

const int LINE_WIDTH = 4095;

// Prototyp definieren
template <class T, int size>
class ValCountArr;

// Prototyp definieren
template <typename T, int size>
ostream &operator<<(ostream &outFile, const ValCountArr<T, size> &arr);

template <typename T>
class ValCountPair {

public:
    T value;
    int cnt;
};

template <typename T, int size>
class ValCountArr {
    friend ostream &operator<< <T, size>(ostream &outFile, const ValCountArr<T, size> &a);

public:
    ValCountArr(): used(0){}

    void count(T value);

    void print() {
        for(int i = 0; i < used; ++i) {
            cout << values[i].value << ": " << values[i].cnt << endl;
        }
    }

private:
    ValCountPair<T> values[size];
    int used;
};

template <typename T, int size>
void ValCountArr<T, size>::count(T value) {
    int i;

    for(i = 0; i < used; ++i) {
        if(values[i].value == value) {
            ++values[i].cnt;
            return;
        }
    }

    if(used == size) {
        cout << "Kein Platz mehr im Array!" << endl;
        exit(EXIT_FAILURE);
    }

    values[i].value = value;
    values[i].cnt = 1;
    ++used;
}

template <typename T, int size>
ostream &operator<<(ostream &outFile, const ValCountArr<T, size> &arr) {
    for(int i = 0; i < arr.used; ++i) {
        outFile << arr.values[i].value << ": " << arr.values[i].cnt << endl;
    }

    return outFile;
}

int main(const int argc, const char *argv[]) {
    if(argc < 2) {
        cout << "Aufruf: " << argv[0] << " file1" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream inFile(argv[1]);

    if(!inFile) {
        cout << "Cannot open file " << argv[1] << " to read." << endl;
        exit(EXIT_FAILURE);
    }

    ValCountArr<char, 30> charCountArr;
    ValCountArr<string, 1000> wordCountArr;

    char line[LINE_WIDTH + 1];
    while(inFile.getline(line, LINE_WIDTH)) {
        int indexFirstLetter = -1;
        char c = line[0];
        for(int i = 0; ; ++i, c = line[i]) {
            c = tolower(c);

            if(isalpha(c)) {
                if(indexFirstLetter == -1){
                    indexFirstLetter = i;
                }

                charCountArr.count(c);
                continue;
            } else {
                if(indexFirstLetter != -1) {
                    // Word detected
                    string word(&line[indexFirstLetter], i - indexFirstLetter);
                    wordCountArr.count(word);
                    indexFirstLetter = -1;
                }
            }

            if(c == '\0') {
                break;
            }

        }
    }

    // charCountArr.print();
    // wordCountArr.print();

    cout << charCountArr << endl;
    cout << wordCountArr << endl;

    if(inFile.fail() && !inFile.eof()) {
        // Fehler
        cerr << argv[0] << ": Cannot read " << argv[1] << " (line too long?)" << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
