#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class ArrayBox{
private:
    T*      data;
    size_t  capacity;
    size_t  length;

public:

    explicit ArrayBox(size_t cap):
        data(new T[cap]),
        capacity(cap),
        length(0)
    {}

    ~ArrayBox() {
        delete [] data;
    }

    ArrayBox(const ArrayBox&) = delete;
    ArrayBox& operator =(const ArrayBox&) = delete;

    void display(){
        for(int i = 0; i < length; i++){
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }

    void append(const T& value);
    void Insert(const T& value,size_t index);
    void Delete (size_t index);
    int Search (const T& value);
    int BinSearch (const T& value);
    void get(size_t index);
    void set(const T& value, size_t index);
    int max();
    int min();
    int sum();
    int avg();

    size_t size(){ return length;}
    size_t max_size() {return capacity; }
};

template <typename T>
void ArrayBox<T>::append(const T& value){
    if(length == capacity) throw std::out_of_range("Array Out of Range");

    data[length] = value;
    ++length;
}

template <typename T>
void ArrayBox<T>::Insert(const T& value, size_t index) {
    if (length == capacity)
        throw std::out_of_range("Array Capacity Exceeded");

    if (index < 0 || index > length)
        throw std::out_of_range("Invalid Index");

    for (int i = length; i > index; i--) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    ++length;
}

template <typename T>
void ArrayBox<T>::Delete(size_t index){
    if (index < 0 || index > length)
        throw std::out_of_range("Index Out of Range");
    for(int i = index; i < length - 1; i++){
        data[i] = data[i + 1];
    }
    length--;
}

template <typename T>
int ArrayBox<T>::Search(const T& value){
    for (int i = 0; i < length; i++){
        if(data[i] == value)
            return i;
    }
    
    return -1;
}

template <typename T>
int ArrayBox<T>::BinSearch(const T& value){
    int low = 0;
    int high = length - 1;
    

    while (low <= high){
        int mid = low + (high - low) / 2;
        
        if(data[mid] == value)
            return mid;
        else if(data[mid] > value)
            low = mid + 1;
        else if(data[mid] < value)
            high = mid - 1;
    }

    return -1;
}

template <typename T>
void ArrayBox<T>::get(size_t index){
    std::cout << data[index];
}

template <typename T>
void ArrayBox<T>::set(const T& value ,size_t index){
    data[index] = value;

    std::cout << data[index];
} 

template <typename T>
int ArrayBox<T>::min(){
    int min = data[0];
    for(int i = 0; i < length; i++){
        if(min > data[i]){
            min = data[i];
        }
    }
    return min;
}

template <typename T>
int ArrayBox<T>::max(){
    int max = data[0];
    for(int i = 0; i < length; i++){
        if(max < data[i]){
            max = data[i];
        }
    }
    return max;
}

template <typename T>
int ArrayBox<T>::sum(){
    int sum = 0;
    for(int i = 0; i < length; i++){
        sum += data[i];
    }
    return sum;
}

template <typename T>
int ArrayBox<T>::avg(){
    int sum = 0;
    for(int i = 0; i < length; i++){
        sum += data[i];
    }
    return sum/length;
}

int main(){
    ArrayBox<int> numbers(10);
    numbers.append(1);
    numbers.append(3);
    numbers.Insert(2,1);
    numbers.display();
    std::cout << numbers.Search(2);
    std::cout << numbers.BinSearch(2);
    numbers.display();
    
    return 0;
}