#include <iostream>
#include <fstream>

using namespace std;

class Exa {
public:
    // Virtual methods
    virtual void cow() {
        cout << "Muh" << endl;
    }

    virtual void bark() {
        cout << "Wuff (escalation)" << endl;
    }

    // Purely virtual method -> Not possible anymore to create objects from this class
    // Even if only one purely virtual method exists
    virtual void saySomething() = 0;
};

class Example: Exa {
public:
    // Constructor with Default params -> Default constructor
    Example(int a = 0, int b = 0, int c = 0, int d = 0): a(a), b(b), c(c), d(d) {}

    int a;
    int b;

    int getC() const { return c; }
    int getD() const { return d; }

    virtual void cow() {
        cout << "Muh" << endl;
    }

    void bark() override {
        Exa::bark();
        cout << "Wuff" << endl;
    }

    void saySomething() override {
        cout << "I'm saying something" << endl;
    }
protected:
    int c;
private:
    int d;
};

void openAndCloseFile() {
    fstream file; // Input and Output
    ifstream inFile; // Input only, alternative: istream("...")
    ofstream outFile; // Output only, alternative: ostream("...")

    // Open using no constructor
    inFile.open("test.txt");
    file.open("test.txt");
    outFile.open("test_of.txt");

    if(!file) {
        cerr << "Error: File could not be opened" << endl;
        return;
    }

    // Write to file
    file << "Hello World!" << endl << "Hello there" << endl;

    // Read from file
    char buffer[512] = {0};
    while(!inFile.eof()) {
        inFile.getline(buffer, 512);
        cout << buffer << endl;
    }

    // Close file
    file.close();
    inFile.close();
    outFile.close();
}

void checklist() {
    Example example;
    Example *ex = new Example();
    Example **c = &ex;

    // . only if we have no pointers
    example.a = 10;
    (*ex).a = 12;
    (**c).a = 15;

    // -> only if pointer on object
    (&example)->b = 88;
    ex->b = 18;
    (*c)->b = 19;

    example.saySomething();
    ex->bark();
    (**c).cow();
}

int main() {
    openAndCloseFile();
    return 0;
}
