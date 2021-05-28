#include <iostream>
#include <cstdlib>

#define MAX_NUMBERS 30

using namespace std;

typedef struct Number {
    int value;
    int occurance;
} Number;

typedef struct NumberList {
    Number numbers[MAX_NUMBERS];
    int elementsCount;
} NumberList;

Number &search(NumberList &hayStack, int needle);
Number &insertAndSort(NumberList &haystack, int needle);
void output(NumberList &hayStack);

int main(int argc, const char *argv[]) {
    if(argc <= 1) {
        cout << "Please enter at least one number." << endl;
        return 0;
    }

    NumberList list;
    list.elementsCount = 0;

    for(int i = 0; i < argc; ++i) {
        // Returned references can directly be accessed
        ++(search(list, atoi(argv[i])).occurance);

        // Other solution:
        // Number &number = search(list, atoi(argv[i]));
        // ++number.occurance;
    }

    output(list);
    return 0;
}

Number &search(NumberList &hayStack, int needle) {
    int i;

    // Search for Number
    for(i = 0; i < hayStack.elementsCount; ++i) {
        if(hayStack.numbers[i].value == needle) {
            return hayStack.numbers[i];
        }
    }

    return insertAndSort(hayStack, needle);
}

Number &insertAndSort(NumberList &haystack, int needle) {
    Number newNumber = { needle, 0 };
    int i;

    for(i = 0; i < haystack.elementsCount; ++i) {
        // After this point, insert needle
        if(haystack.numbers[i].value > needle) {
            break;
        }
    }

    if(haystack.elementsCount >= MAX_NUMBERS) {
        cout << "Too many elements!" << endl;
        exit(EXIT_FAILURE);
    }

    // Move all numbers to last place (make space for number at i)
    for(int k = haystack.elementsCount; k > i; --k) {
        haystack.numbers[k] = haystack.numbers[k - 1];
    }

    // Insert new number at position i
    haystack.numbers[i] = newNumber;
    ++haystack.elementsCount;
    return haystack.numbers[i];
}

void output(NumberList &hayStack) {
    for(int i = 0; i < hayStack.elementsCount; ++i) {
        cout << "#" << i + 1 << " - " << hayStack.numbers[i].value << " (x" << hayStack.numbers[i].occurance << ")" << endl;
    }
}
