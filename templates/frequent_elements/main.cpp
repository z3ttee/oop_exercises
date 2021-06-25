#include <iostream>
#include <string.h>

using namespace std;

template<typename T>
T freqency(T arr[], int size, T nullValue, int &maxAmount) {

    T result = nullValue;
    maxAmount = 0;

    for(int i = 0; i < size; ++i) {
        int frequency = 1;

        for(int k = i; k < size; ++k) {
            if(arr[i] == arr[k]) {
                ++frequency;
            }
        }

        if(frequency > maxAmount) {
            result = arr[i];
            maxAmount = frequency;
        }
    }

    return result;
}

int main(const int argc, const char *argv[]) {

    string *words = new string[argc - 1];
    int *wordLengths = new int[argc - 1];

    for(int i = 1; i < argc; ++i) {
        words[i] = argv[i];
        wordLengths[i] = strlen(argv[i]);
    }

    int maxAmount;

    string maxWord = freqency<string>(words, argc - 1, "", maxAmount);
    int maxLen = freqency<int>(wordLengths, argc - 1, 0, maxAmount);

    cout << "Haeufigstes Wort: " << maxWord << endl;
    cout << "Haeufigste Laenge: " << maxLen << endl;

    return 0;
}
