#include <iostream>
#include <cstring>

using namespace std;

class String {

    friend ostream &operator<<(ostream &outFile, const String &a);

public:
    String(unsigned long long length = 0): value(new char[length + 1]){
        this->value[0] = '\0';
    }

    String(const String &origin): value(new char[strlen(origin.value) + 1]) {
        strcpy(this->value, origin.value);
    }

    String(const char *origin): value(new char[strlen(origin) + 1]) {
        strcpy(this->value, origin);
    }

    ~String() {
        delete[] this->value;
    }

    char *value;

    String operator+(const String &b) const {
        String c(strlen(this->value) + strlen(b.value));

        strcpy(c.value, this->value);
        strcat(c.value, b.value);

        return c;
    }

    String &operator+=(const String &b) {
        char *c = new char[strlen(b.value) + 1];
        strcpy(c, this->value);
        strcat(c, b.value);

        delete [] this->value;
        this->value = c;

        return *this;
    }

    String &operator=(const String &b) {
        if(this != &b) {
            delete [] this->value;
            this->value = new char[strlen(b.value)];
            strcpy(this->value, b.value);
        }

        return *this;
    }

    bool operator==(const String &b) const {
        return (strcmp(this->value, b.value) == 0);
    }

    bool operator<(const String &b) const {
        return (strcmp(this->value, b.value) < 0);
    }

    bool operator!() const {
        return (this->value[0] == '\0');
    }

};

ostream &operator<<(ostream &outFile, const String &a) {
    outFile << a.value;
    return outFile;
}

int main() {
    String nix;
    String a = "Äpfel";
    String aa = a;
    String b = "Birnen";
    String bb;
    String k = "Kompott";
    String ab = "ÄpfelBirnen";
    String res;

    bb = b;
    res = aa + String("") + bb;

    cout << "Ist 'nix' leer? " << (!nix ? "Ja!" : "Nein???") << endl;
    cout << "'" << bb << "' sind " << (!bb ? "auch" : "nicht") << " leer." << endl;
    cout << "'" << a << "' und '" << b << "' sind " <<
         ((a == b) ? "gleich" : "verschieden") << "." << endl;
    cout << "'" << bb << "' sind " << (bb < k ? "kleiner" : "größer") <<
         " als '" << k << "'" << endl;
    cout << "'" << k << "' ist " << (k < b ? "kleiner" : "größer") <<
         " als '" << b << "'" << endl;
    cout << "'" << aa << "' plus '" << bb << "' sind '" << res << "'." << endl;
    cout << "Sind es wirklich 'ÄpfelBirnen'? " <<
         ((ab == res) ? "Ja!" : "Nein???") << endl;

    // ab hier auskommentieren, solange du noch kein += hast
    a += bb;
    a += k;
    cout << "Und jetzt gibt es '" << a << "'." << endl;

    return 0;
}
