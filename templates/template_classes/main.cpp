#include <iostream>

using namespace std;

template<typename T1, typename T2>
class Pair {

public:
    Pair(){};
    Pair(T1 first, T2 second): first(first), second(second){};

    T1 getFirst() {
        return this->first;
    }

    T2 getSecond() {
        return this->second;
    }

    bool operator==(const Pair &pair) const {
        return pair.first == this->first;
    }
    bool operator<(const Pair &pair) const {
        return this->first < pair.first;
    }
    
private:
    T1 first;
    T2 second;
    
};

template<typename T>
class Array {

public:
    Array(int size): size(size), totalElements(0) {
        this->arr = new T[size];
    }

    ~Array() {
        // TODO
    }

    bool add(T element) {
        if(totalElements == size) return false;

        this->arr[totalElements] = element;
        ++(this->totalElements);
        return true;
    }

    T *min();
    T *maxAs(const T &compare);

private:
    T *arr;
    int size;
    int totalElements;
};

template<typename T>
T* Array<T>::min() {
    if(this->totalElements == 0) return nullptr;
    T *result = &(this->arr[0]);

    for(int i = 1; i < this->totalElements; ++i) {
        if(this->arr[i] < *result) {
            result = &(this->arr[i]);
        }
    }

    return result;
}

template<typename T>
T* Array<T>::maxAs(const T &compare) {
    if(this->totalElements == 0) return nullptr;

    T *result = nullptr;

    for(int i = 0; i < this->totalElements; ++i) {
        if(compare < this->arr[i]) {
            result = &(this->arr[i]);
        }
    }

    return result;
}

typedef Pair<string, int> pair_t;

int main(const int argc, const char *argv[]) {

    Array<pair_t> array(argc - 1);

    for(int i = 1; i < argc; ++i) {
        Pair<string, int> pair(argv[i], argc - 1);
        array.add(pair);
    }

    for(pair_t *maxPair = array.min(); maxPair != nullptr; maxPair = array.maxAs(*maxPair)) {
        cout << maxPair->getFirst() << ": " << maxPair->getSecond() << endl;
    }

    return 0;
}
