#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
T haeufigstes(T arr[], int size, T orDefault, int &out) {
    out = 0;
    T result = orDefault;

    if(size <= 0) {
        return result;
    }

    for(int i = 0; i < size; ++i) {
        int occurance = 1;

        for(int k = i; k < size; ++k) {
            if(arr[k] == arr[i]) {
                ++occurance;
            }
        }

        if(occurance > out) {
            out = occurance;
            result = arr[i];
        }
    }

    return result;
}

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " <input>" << endl;
        return 0;
    }

    string *strings = new string[argc - 1];
    int *ints = new int[argc - 1];

    for(int i = 0; i < argc - 1; ++i) {
        strings[i] = argv[i + 1];
        ints[i] = (int) strlen(argv[i + 1]);
    }

    int occurance;
    string haeufigsterString = haeufigstes<string>(strings, argc - 1, "", occurance);
    cout << "Haeufigstes Wort: " << haeufigsterString << " mit " << occurance << " vorkommen." << endl;

    int maxLen = haeufigstes<int>(ints, argc - 1, 0, occurance);
    cout << "Haeufigste Laenge: " << maxLen << " mit " << occurance << " vorkommen." << endl;
    return 0;
}
