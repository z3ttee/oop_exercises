#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_LINE_LEN 80

using namespace std;

void centerFile(const string &filenamePath) {
    ifstream file(filenamePath);

    if(!file) {
        cerr << "File '" << filenamePath << "' cannot be accessed." << endl;
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN + 1];
    while(file.getline(line, sizeof(line))) {

        for(int i = 0; i < (MAX_LINE_LEN - strlen(line)) / 2; ++i) {
            cout << " ";
        }

        cout << line << endl;
    }

    if((file.fail() || file.bad()) && !file.eof()) {
        cerr << "File '" << filenamePath << "' cannot be read. Is there a line that exceeds the length of " << MAX_LINE_LEN << "?" << endl;
        exit(EXIT_FAILURE);
    }

    file.close();
}

int main(const int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " file1" << endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; ++i) {
        cout << "\n[]=== File: '" << argv[i] << "' ===[]" << endl;
        centerFile(argv[i]);
    }

    return 0;
}
