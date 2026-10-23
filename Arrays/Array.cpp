
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <cstddef>

template <typename T>
class Array {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void ensureCapacity(std::size_t required) {
        if (required <= capacity_)
            return;

        std::size_t newCapacity = capacity_ == 0 ? 1 : capacity_;

        while (newCapacity < required)
            newCapacity *= 2;

        T* newData = new T[newCapacity];

        try {
            for (std::size_t i = 0; i < size_; ++i)
                newData[i] = data_[i];
        } catch (...) {
            delete[] newData;
            throw;
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void checkIndex(std::size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Array index out of range");
    }

public:
    // Constructors
    explicit Array(std::size_t capacity = 4)
        : data_(capacity ? new T[capacity] : nullptr),
          size_(0),
          capacity_(capacity) {}

    Array(std::initializer_list<T> values)
        : Array(values.size()) {
        for (const T& value : values)
            append(value);
    }

    // Copy constructor
    Array(const Array& other)
        : data_(other.capacity_
                    ? new T[other.capacity_]
                    : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        try {
            for (std::size_t i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        } catch (...) {
            delete[] data_;
            throw;
        }
    }

    // Move constructor
    Array(Array&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    // Copy assignment
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            swap(temp);
        }
        return *this;
    }

    // Move assignment
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            size_ = std::exchange(other.size_, 0);
            capacity_ = std::exchange(other.capacity_, 0);
        }
        return *this;
    }

    // Destructor
    ~Array() {
        delete[] data_;
    }

    void swap(Array& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Basic operations
    void display() const {
        std::cout << "[ ";
        for (std::size_t i = 0; i < size_; ++i)
            std::cout << data_[i] << ' ';
        std::cout << "]\n";
    }

    void append(const T& value) {
        ensureCapacity(size_ + 1);
        data_[size_++] = value;
    }

    void add(const T& value) {
        append(value);
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_)
            throw std::out_of_range("Invalid insertion index");

        ensureCapacity(size_ + 1);

        for (std::size_t i = size_; i > index; --i)
            data_[i] = std::move(data_[i - 1]);

        data_[index] = value;
        ++size_;
    }

    void deleteElement(std::size_t index) {
        checkIndex(index);

        for (std::size_t i = index; i + 1 < size_; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
    }

    T& get(std::size_t index) {
        checkIndex(index);
        return data_[index];
    }

    const T& get(std::size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    void set(std::size_t index, const T& value) {
        checkIndex(index);
        data_[index] = value;
    }

    // Searching
    int linearSearch(const T& value) const {
        for (std::size_t i = 0; i < size_; ++i)
            if (data_[i] == value)
                return static_cast<int>(i);

        return -1;
    }

    int binarySearch(const T& value) const {
        std::size_t left = 0, right = size_;

        while (left < right) {
            std::size_t mid = left + (right - left) / 2;

            if (data_[mid] == value)
                return static_cast<int>(mid);

            if (data_[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }

        return -1;
    }

    // Numeric operations
    T max() const {
        if (size_ == 0)
            throw std::runtime_error("Empty array");

        T result = data_[0];

        for (std::size_t i = 1; i < size_; ++i)
            if (data_[i] > result)
                result = data_[i];

        return result;
    }

    T min() const {
        if (size_ == 0)
            throw std::runtime_error("Empty array");

        T result = data_[0];

        for (std::size_t i = 1; i < size_; ++i)
            if (data_[i] < result)
                result = data_[i];

        return result;
    }

    T sum() const {
        T result{};

        for (std::size_t i = 0; i < size_; ++i)
            result += data_[i];

        return result;
    }

    double avg() const {
        if (size_ == 0)
            throw std::runtime_error("Empty array");

        return static_cast<double>(sum()) / size_;
    }

    // Rearrangement
    void reverse() {
        for (std::size_t i = 0; i < size_ / 2; ++i)
            std::swap(data_[i], data_[size_ - 1 - i]);
    }

    void shiftLeft(std::size_t positions = 1) {
        if (size_ == 0)
            return;

        if (positions >= size_) {
            for (std::size_t i = 0; i < size_; ++i)
                data_[i] = T{};
            return;
        }

        for (std::size_t i = 0; i < size_ - positions; ++i)
            data_[i] = std::move(data_[i + positions]);

        for (std::size_t i = size_ - positions; i < size_; ++i)
            data_[i] = T{};
    }

    void shiftRight(std::size_t positions = 1) {
        if (size_ == 0)
            return;

        if (positions >= size_) {
            for (std::size_t i = 0; i < size_; ++i)
                data_[i] = T{};
            return;
        }

        for (std::size_t i = size_; i-- > positions;)
            data_[i] = std::move(data_[i - positions]);

        for (std::size_t i = 0; i < positions; ++i)
            data_[i] = T{};
    }

    void rotateLeft(std::size_t positions = 1) {
        if (size_ == 0)
            return;

        positions %= size_;

        for (std::size_t i = 0; i < positions; ++i) {
            T first = std::move(data_[0]);

            for (std::size_t j = 0; j + 1 < size_; ++j)
                data_[j] = std::move(data_[j + 1]);

            data_[size_ - 1] = std::move(first);
        }
    }

    void rotateRight(std::size_t positions = 1) {
        if (size_ == 0)
            return;

        positions %= size_;

        for (std::size_t i = 0; i < positions; ++i) {
            T last = std::move(data_[size_ - 1]);

            for (std::size_t j = size_ - 1; j > 0; --j)
                data_[j] = std::move(data_[j - 1]);

            data_[0] = std::move(last);
        }
    }

    // Combining arrays
    Array merge(const Array& other) const {
        Array result(size_ + other.size_);

        for (std::size_t i = 0; i < size_; ++i)
            result.append(data_[i]);

        for (std::size_t i = 0; i < other.size_; ++i)
            result.append(other.data_[i]);

        return result;
    }

    Array unionArray(const Array& other) const {
        Array result(size_ + other.size_);

        for (std::size_t i = 0; i < size_; ++i)
            if (result.linearSearch(data_[i]) == -1)
                result.append(data_[i]);

        for (std::size_t i = 0; i < other.size_; ++i)
            if (result.linearSearch(other.data_[i]) == -1)
                result.append(other.data_[i]);

        return result;
    }

    Array intersection(const Array& other) const {
        Array result(size_);

        for (std::size_t i = 0; i < size_; ++i) {
            if (other.linearSearch(data_[i]) != -1 &&
                result.linearSearch(data_[i]) == -1) {
                result.append(data_[i]);
            }
        }

        return result;
    }

    // Metadata
    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }
};

int main() {
    try {
        Array<int> arr{10, 20, 30, 40, 50};

        std::cout << "Original: ";
        arr.display();

        arr.append(60);
        arr.insert(2, 25);

        std::cout << "After append and insert: ";
        arr.display();

        arr.deleteElement(1);
        std::cout << "After deletion: ";
        arr.display();

        std::cout << "Element at index 2: " << arr.get(2) << '\n';
        arr.set(2, 99);

        std::cout << "Linear search for 99: "
                  << arr.linearSearch(99) << '\n';

        std::cout << "Maximum: " << arr.max() << '\n';
        std::cout << "Minimum: " << arr.min() << '\n';
        std::cout << "Sum: " << arr.sum() << '\n';
        std::cout << "Average: " << arr.avg() << '\n';

        arr.reverse();
        std::cout << "Reversed: ";
        arr.display();

        arr.rotateLeft(2);
        std::cout << "Rotated left by 2: ";
        arr.display();

        Array<int> other{20, 30, 70, 80};

        std::cout << "Second array: ";
        other.display();

        std::cout << "Merged: ";
        arr.merge(other).display();

        std::cout << "Union: ";
        arr.unionArray(other).display();

        std::cout << "Intersection: ";
        arr.intersection(other).display();

        // Binary search requires sorted data.
        Array<int> sorted{10, 20, 30, 40, 50};
        std::cout << "Binary search for 30: "
                  << sorted.binarySearch(30) << '\n';

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
