#include <iostream>

using namespace std;

template<typename T, typename T2>
class Paar {

public:
    Paar(){}
    Paar(T &erster, T2 &zweiter): erster(erster), zweiter(zweiter){}

    T getErster() const { return erster; }
    T2 getZweiter() { return zweiter; }

    bool operator==(const Paar<T, T2> &paar) const {
        return paar.erster == this->erster;
    }

    bool operator<(const Paar<T, T2> &paar) const {
        return this->erster < paar.erster;
    }

private:
    T erster;
    T2 zweiter;
};

template<typename T>
class Array {
public:
    Array(int size): size(size), arr(new T[size]), used(0){}
    ~Array() {
        delete [] this->arr;
    }

    Array(const Array<T> &orig) = delete;
    Array &operator=(const Array<T> &orig) = delete;

    bool add(const T &value) {
        if(used >= size) return false;

        arr[used] = value;
        ++(this->used);
        return true;
    }

    T *min();
    T *next(const T &nextTo);

private:
    T *arr;
    int size;
    int used;
};

template<typename T>
T *Array<T>::min() {
    if(used == 0) return nullptr;

    T *result = &(arr[0]);

    for(int i = 1; i < used; ++i) {
        if(arr[i] < *result) {
            result = &(arr[i]);
        }
    }

    return result;
}

template<typename T>
T *Array<T>::next(const T &nextTo) {
    T *result = nullptr;

    for(int index = 0; index < used; ++index){
        if ((nextTo < arr[index]) && ((result == nullptr) || (arr[index] < *result))) {
            result = &(arr[index]);
        }
    }

    return result;
}


typedef Paar<string, int> paar_t;
int main(int argc, const char *argv[]) {
    if(argc < 2) {
        cerr << "Aufruf: " << argv[0] << " <input>" << endl;
        return 0;
    }

    Array<paar_t> arr(argc - 1);

    for(int i = 1; i < argc; ++i) {
        string str = argv[i];

        paar_t paar(str, i);
        arr.add(paar);
    }

    for(paar_t *ptr = arr.min(); ptr; ptr = arr.next(*ptr)) {
        cout << "Wort: " << ptr->getErster() << ", Index: " << ptr->getZweiter() << endl;
    }

    return 0;
}
