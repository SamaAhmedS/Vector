#include<iostream>
using namespace std;
//#define T* iterator;
template<class T>
class MyVector {
private:
    T* vec;
    int Size = -1;
    int capacity;
public:
    typedef T* iterator;
    MyVector(int cap);// Initialize by specific capacity //No content is added, size = 0
    // Assign a default size value

    MyVector(T* arr, int  n); // Initialize by n items from array

    MyVector(const MyVector& other);//Initialize with a copy (Copy Constructor)

    ~MyVector() { delete[] vec; }			// Delete allocated memory

    MyVector& operator=(const MyVector&);// Copy assignment

    MyVector& operator=(MyVector&&); // Move assignment

    // Access operations
    T& operator[](int); // Access item by reference
    // Throw an exception if out of range
    const T& operator[](int)const;
// Modifying operations
    int push_back(T other);// Add item to end of vec & return # of items
    // Increase capacity of needed
    T pop_back();    // Remove and return last element in vec
    void erase(iterator);       // Remove item at iterator
    // Throw exception if invalid iter
    void erase(iterator t1, iterator t2);// Remove items between
// iterator 1 <= iterator 2 otherwise do nothing
// Throw exception if any iterator outside range
    void clear();    // Delete all vector content
    void insert(iterator, T) ;      // Insert item at iterator
    // Throw exception if invalid

// Iterators 		// Supports *, + and ++ operations at least
     // Can use: typedef T* iterator
    // Or u can use std::iterator so you can
   // apply STL algorithms on XYVector
    iterator begin() {return vec;}// Return an iterator (T*)
    iterator end() {
        T* pt = &vec[capacity-1];
        pt++;
        return pt;
    }	// Return an iterator (T*)

// Comparison operations
    bool operator==(const MyVector<T>&); // Return true if ==
    bool operator< (const MyVector<T>&); // Compares item by item
    // Return true if first different item in this is < in other

// Capacity operations
    int size() const { return Size+1; }   // Return current size of vec
    int Capacity() const { return capacity; } // Return size of current allocated array
    int resize();        // Relocate to bigger space
    bool empty() { return (Size == -1); }         // Return true if size is 0

// Friends
    friend ostream& operator << (ostream& out,const MyVector<T>& v) {
        if (v.Size != -1) {
            out << "{";
            for (int i = 0; i < v.Size; i++) {
                out << v.vec[i] << ",";
            }
            out << v.vec[v.Size] << "}";
        }
        return out;
    }
};

class outOfRange :public exception {
public:
    virtual const char* what() const throw() {
        return "error, out of range\n";
    }
};
//class BadIterator :public exception {
//public:
//    virtual const char* what() const throw() {
//        return "Error, Invalid iterator\n";
//    }
//};
class BadIterator {
    string str;
public:
    BadIterator(string s):str(s){}
    string what() const throw() {
        return str;
    }
};

template<class T>MyVector<T>::MyVector(int cap) {
    capacity = cap;
    vec = new T[cap];
    for (int i = 0; i < cap; i++) {
        vec[i] = 0;
    }
    Size = cap - 1;
}
template<class T>MyVector<T>::MyVector(T* arr, int  n) {
    capacity = n;
    vec = new T[n];
    for (int i = 0; i < n; i++) {
        vec[i] = arr[i];
    }
    Size = n - 1;
}
template<class T>MyVector<T>:: MyVector(const MyVector<T>& other) {
    Size = other.Size;
    capacity = other.capacity;
    vec = new T[capacity];
    for (int i = 0; i < capacity; i++) {
        vec[i] = other.vec[i];
    }
}
template<class T>MyVector<T>& MyVector<T>:: operator=(const MyVector<T>& other) {
    if (this != &other) {
        delete vec;
        Size = other.Size;
        capacity = other.capacity;
        vec = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            vec[i] = other.vec[i];
        }
    }
    return *this;
}
template<class T>MyVector<T>& MyVector<T>:: operator=(MyVector<T>&& other) {
    delete vec;
    vec = other.vec;
    Size = other.Size;
    capacity = other.capacity;
    other.vec = nullptr;
    return *this;
}

template<class T> int MyVector<T>::push_back(T element) {
    if (Size >= capacity-1) {
        this->resize();
        vec[++Size] = element;
    }
    else {
        vec[++Size] = element;
    }
    return Size + 1;
}

template<class T>
int MyVector<T>::resize() {
    capacity = capacity * 2;
    T* arr = new T[capacity];
    for (int i = 0; i < Size + 1; ++i) {
        arr[i] = vec[i];
    }
    delete[] vec;
    vec = arr;
    arr = nullptr;
    return capacity;
}

template<class T> T MyVector<T>:: pop_back() {
    if (Size < 0) {
        cout << "There is no elements in this vector \n";
        exit(1);
    }
    else {
        T element = vec[Size];
        T* arr = new T[capacity];
        for (int i = 0; i < Size; ++i) {
            arr[i] = vec[i];
        }
        delete[]vec;
        vec = arr;
        arr = nullptr;
        Size--;
        return element;
    }
    /*
    else {
        T element = vec[Size];
        vec[Size].~T;
        Size--;
        return element;
    }*/
}

template<class T>
void MyVector<T>::clear() {
    Size = -1;
    delete[]vec;
    vec = new T[capacity];
}

template<class T>
bool MyVector<T>::operator==(const MyVector<T>& other) {
    if (Size == other.Size) {
        for (int i = 0; i <= Size; ++i) {
            if (vec[i] != other.vec[i]) {
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}

template<class T>
bool MyVector<T>::operator<(const MyVector<T>& other) {
    if (Size == other.Size) {
        for (int i = 0; i <= Size; ++i) {
            if (vec[i] < other.vec[i]) {
                return true;
            }
        }
    }
    else {
        int Min = min(Size, other.Size);
        for (int i = 0; i < Min; ++i) {
            if (vec[i] > other.vec[i]) {
                return false;
            }
        }
        if (Size > other.Size) {
            return false;
        }
        return true;
    }
    return false;
}
template<class T>T& MyVector<T>::operator[](int index)throw(outOfRange) {
    try
    {
        if (index <= Size) {
            return vec[index];
        }
        else {
            throw(outOfRange());
        }
    }
    catch (outOfRange& o)
    {
        cout << o.what();
    }
}
template<class T>const T& MyVector<T>::operator[](int index)const throw(outOfRange) {
    try
    {
        if (index <= Size) {
            return vec[index];
        }
        else {
            throw(outOfRange());
        }
    }
    catch (outOfRange& o)
    {
        cout << o.what();
    }
}
template<class T> void MyVector<T>::erase(iterator it)throw(BadIterator) {
    T* arr = new T[capacity];
    bool found = 0;
    for (int i = 0,ind=0; i < Size + 1;ind++, i++) {
        if(&vec[i]!=it){
            arr[ind] = move(vec[i]);
        }
        else {
            found = 1;
            ind--;
        }
    }
    try
    {
        if (found) {
            Size--;
            delete[]vec;
            vec = arr;
            arr = nullptr;
        }
        else {
            throw BadIterator("Error, Invalid iterator\n");
        }
    }
    catch (const BadIterator& It)
    {
        cout << It.what();
    }
}

template<class T> void MyVector<T>::erase(iterator it1, iterator it2)throw(BadIterator) {
    T* arr = new T[capacity];
    int found = 0;
    int sz = -1;
    for (int i = 0; i < Size + 1; i++) {
        if (&vec[i] != it1 && found == 0) {
            arr[++sz] = move(vec[i]);
        }
        else if (&vec[i] == it1) {
            found = 1;
        }
        else if (&vec[i] == it2&&found!=2 ) {
            found = 2; 
        }
        else  if (&vec[i] != it2 && found == 2) {
            arr[++sz] = move(vec[i]);
        }
    }
    try
    {
        if (found==2) {
            Size = sz;
            delete[] vec; 
            vec = arr; arr = nullptr;
        }
        else {
            throw BadIterator("Error, Invalid iterator\n");
        }
    }
    catch (const BadIterator& It)
    {
        cout << It.what();
    }
}
template<class T> void MyVector<T>:: insert(iterator it, T ele)throw(BadIterator) {
    T* arr = new T[capacity+1];
    bool found = 0;
    int i = 0;
    for (; i < Size + 1; i++) {
        if (&vec[i] == it) {
            found = 1;
            break;
        }
        else {
            arr[i] = move(vec[i]);
        }
    }
    try
    {
        if (found) {
            arr[i] = ele;
            int index = i + 1;
            for (; i < Size + 1;index++, i++) {
                arr[index] = move(vec[i]);
            }
            delete[]vec;  Size++; capacity++;
            vec = arr;
            arr = nullptr;
        }
        else {
            throw BadIterator("Error in Insert, Invalid iterator\n");
        }
    }
    catch (const BadIterator& It)
    {
        cout << It.what();
    }

}
template<class T>
void print(const MyVector<T>& v) {
    int sz = v.size()+1;
    for (int i = 0; i < sz; i++) {
        cout << v[i];
        cout << ",";
    }
    cout << "\n";
}



