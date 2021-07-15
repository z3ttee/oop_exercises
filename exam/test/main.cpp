#include <iostream>
#include "Class_.h"
using  namespace  std;

int main() {
    Try<double> X(5,6.77);

    X.setA(8.88);

    cout << X << endl;

    return 0;
}
