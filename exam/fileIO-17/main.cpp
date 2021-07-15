#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

const int MAX_LINE_LEN = 80;
const int MAX_OUT_LINE_LEN = 256;

void copyFileAndLowercase(const string &src, const string &dest) {
    ifstream inFile(src);
    ofstream outFile(dest);

    if(!inFile) {
        throw "Could not open file " + src + ".";
    }

    if(!outFile) {
        throw "Could not open file " + dest + ".";
    }

    char c;
    while(inFile.get(c)) {
        if(!outFile.put(tolower(c))) {
            throw "Could not write to file " + src + ".";
        }
    }

    if(!inFile.eof()) {
        throw "An error occured when reading the file " + src + ".";
    }

    inFile.close();
    outFile.close();
}

int main(int argc, const char *argv[]) {
    if(argc < 3) {
        cerr << "Aufruf: " << argv[0] << " inFile outFile" << endl;
        return 0;
    }

    try {
        copyFileAndLowercase(argv[1], argv[2]);
    } catch (string &err) {
        cerr << err << endl;
    }

    return 0;
}
