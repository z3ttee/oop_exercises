#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

void readFile(string file) {
    ifstream inFile(file);

    if(!inFile) {
        throw "Could not open file '" + file + "'.";
    }

    char input[4096];
    while(inFile.getline(input, sizeof(input))) {
        stringstream stream(input);

        int length = strlen(input);
        if(length == 0) break;
        char lastChar = tolower(input[length - 1]);

        int result;
        if(lastChar == 'h') {
            // Hex
            stream >> hex >> result;
        } else if(lastChar == 'o') {
            // Octal
            stream >> oct >> result;
        } else {
            // Decimal
            stream >> dec >> result;
        }

        if(stream.fail() || stream.bad()) {
            cerr << "Failed converting line to decimal: Is there a valid input?" << endl;
            continue;
        }

        cout << input << " --> " << result << endl;
    }

    if(!inFile.eof()) {
        throw "Could not read from file '" + file + "'.";
    }
}

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " inFile" << endl;
        return 0;
    }

    try {
        readFile(argv[1]);
    } catch (string &ex) {
        cerr << ex << endl;
    }

    return 0;
}
