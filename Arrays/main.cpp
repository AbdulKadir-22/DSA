#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class ArrayBox{
private:
    T*      data;
    size_t  capacity;
    size_t  length;

public:

    // Constructor
    explicit ArrayBox(size_t cap) : 
        data(new T[cap]), 
        capacity(cap), 
        length()
    {}

    ~ArrayBox() {
        delete[] data;
    }

    ArrayBox (const ArrayBox&) = delete;
    ArrayBox& operator = (const ArrayBox&) = delete;

    void display(){
        for(int i = 0; i < length; i++){
            std::cout << data[i] << "\n";
        }
    }

    void append(const T& value);
    
    size_t size() const {return length; }
    size_t max_size() const { return capacity; }

};

template <typename T >
void ArrayBox<T>::append(const T& value){
    if(length == capacity) throw std::out_of_range("ArrayBox is full");

    data[length] = value;
    ++length;
}

int main(){

    ArrayBox<int> numbers(10);
    numbers.append(1);
    numbers.append(2);
    numbers.append(3);
    numbers.display();
    std::cout << numbers.size() << "\n";
    std::cout << numbers.max_size() << "\n";

    ArrayBox<std::string> words(3);
    words.append("Hello, ");
    words.append("World!");

    words.display();

    return 0;
}