#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int main(const int argc, const char *argv[]) {
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << " file1 file2" << endl;
        exit(EXIT_FAILURE);
    }

    ifstream inFile(argv[1]);
    if(!inFile) {
        cerr << "File '" << argv[1] << "' cannot be accessed." << endl;
        exit(EXIT_FAILURE);
    }

    ofstream outFile(argv[2]);
    if(!outFile) {
        cerr << "File '" << argv[2] << "' cannot be accessed." << endl;
        exit(EXIT_FAILURE);
    }

    char c;
    while(inFile.get(c)) {
        if(!outFile.put(tolower(c))) {
            cerr << "Error when writing character '" << c << "' to lowercase.";
            exit(EXIT_FAILURE);
        }
    }

    inFile.close();
    outFile.close();

    cout << "Successfully lowercased file '" << argv[1] << "' into file '" << argv[2] << "'." << endl;
    return 0;
}
