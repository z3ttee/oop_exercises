#include <iostream>

using namespace std;

string names[] = { "Franz", "Xaver", "Kevin", "Michael", "Felix", "Andreas" };
int matNr[] = { 1234, 5678, 9876, 3210, 1111, 9999 };
double noten[] = { 6.0, 1.3, 3.6, 1.5, 3.6, 2.0 };

const int students = sizeof(noten) / sizeof(noten[0]);

void print(int index) {
    cout << "#" << index + 1 << ": " << names[index] << " (G" << matNr[index] << "PI) - Note: " << noten[index] << endl;
}

template <typename T>
void sort(T arr[]) {
    bool boolArr[students];

    for (int i = 0; i < students; ++i) {
        boolArr[i] = false;
    }

    for (int i = 0; i < students; ++i) {
        T max = arr[i];

        int k;
        for(k = 0; k < students; ++k) {
            if(arr[k] > max && !boolArr[k]) {
                max = arr[k];
            }
        }

        boolArr[k] = true;
        cout << "Max: " << max << endl;

    }

}

template <typename T>
void find(T arr[]) {
    T search;

    cout << "Suchwert:" << endl;
    cin >> search;

    bool found = false;

    for(int i = 0; i < students; ++i) {
        if(arr[i] == search) {
            found = true;
            print(i);
        }
    }

    if(!found) {
        cout << "Kein Eintrag gefunden!" << endl;
    }
}



int main() {
    char c;

    for(;;) {
        cout << endl;
        cout << "Was möchtest du machen?" << endl;
        cout << "A - Sortierung nach Name" << endl;
        cout << "B - Sortierung nach Matrikelnummer" << endl;
        cout << "C - Sortierung nach Note" << endl;
        cout << "D - Suche nach Name" << endl;
        cout << "E - Suche nach Matrikelnummer" << endl;
        cout << "F - Suche nach Note" << endl;
        cout << "Alles andere beendet das Programm!" << endl;
        cout << endl;

        cin >> c;
        switch (tolower(c)) {
            case 'a':
                sort(names);
                break;
            case 'b':
                sort(matNr);
                break;
            case 'c':
                sort(noten);
                break;
            case 'd':
                find(names);
                break;
            case 'e':
                find(matNr);
                break;
            case 'f':
                find(noten);
                break;
            default:
                exit(EXIT_SUCCESS);
        }
    }
}
