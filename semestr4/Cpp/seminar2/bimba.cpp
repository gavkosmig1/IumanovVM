// #include <shared_ptr>
// #include <unique_ptr>

#include <memory>
#include <iostream>


class OtherClass{};

OtherClass *ptr_global = new OtherClass;


class MyObject {

    std::unique_ptr<OtherClass> ptr = std::make_unique<OtherClass>());

};


template<typename T>
class MyShared {
    T* ptr_ = nullptr;

    unsigned int * counter_ = nullptr;

    public:
    MyShared (T * &&ptr):ptr_(ptr), counter_(new unsigned int){
    *counter_ += 1;
    std::cout << "Ctr " << *counter_ << "\n";
    }

    MyShared (MyShared <T> &other){
        counter_ = other.counter_;
        *counter_ += 1;
        ptr_ = other.ptr_;
        std::cout << "Cpy " << *counter_ << "\n";
    }

    ~MyShared(){
        *counter_ -= 1;
        if (*counter_ == 0) {
            std::cout << "DTr " << *counter_ << "\n";
            delete ptr_;
            delete counter_;
            std::cout << "Dtr\n";
        }
    }
};

int main(int argc, char ** argv) {
    MyShared<MyObject> ptr = new MyObject;
    auto simple_ptr = new MyObject;
    std::cout << "wow";
    // MyShared<MyObject> ptr2 = std::move(simple_ptr);

    auto ptr2 = ptr;

    return 0;
}