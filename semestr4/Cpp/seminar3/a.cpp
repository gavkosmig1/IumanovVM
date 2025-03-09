#include <stdint.h>
#include <iostream>

template <typename T>
class MyShared {

    T*            ptr_     = nullptr;
    unsigned int* counter_ = nullptr;
public:
    MyShared() {
        auto ptr = new uint8_t [sizeof (T) + sizeof(*counter_)];    // new

        std::cout << "\talloced ptr:\t" << (void*)ptr << std::endl;
    
        ptr_ = new (ptr + sizeof(*counter_)) T;

        std::cout << "\tobject ptr:\t" << ptr_ << std::endl;

        counter_ = reinterpret_cast<unsigned int*>(ptr);

        std::cout << "\tcounter ptr:\t" << counter_ << std::endl;

        (*counter_)++;
    }

    ~MyShared () {
        if (counter_){
            (*counter)--;
            if (*counter == 0) {
                ptr_->~T();     // Так лучше не делать
                delete [] reinterpret_cast<uint8_t>(counter_);
            }
        }
    }

    T *operator->() {
        return ptr_;
    }
};

class MyClass {
public:
    float b = 5.6;
    int a;
    char c;
    MyClass() {
        std::cout << "MyClass ctr " << std::endl;
    }

    ~MyClass() {
        std::cout << "Myclass dtr " << std::endl;
    }
} ;

int main () {
    std::cout << "Size of MyClass " << sizeof MyClass << std::endl;
    MyShared<MyClass> shared_ptr;
    std::cout << "some data " << shared_ptr->b << std::endl;
}