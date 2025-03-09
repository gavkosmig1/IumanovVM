#include <iostream>

int N = 10;

int &foo()
{
    return N;
}

int baz()
{
    return 42;
}

namespace temp {
    struct Base {
        double number = 42;
    };

    void foo(Base *obj, double num) {
        std::cout << "temp::foo\n" << "Base::number = " << obj->number
                  << "\nnum = " << num << std::endl;
    }
}

namespace temp2 {
    int baz(temp::Base *obj) {
        return 1000 + obj->number;
    }

    struct Derived {
        temp::Base *m_obj;

        Derived(temp::Base *obj) : m_obj(obj) {}

        operator temp::Base *() const {
            return m_obj;
        }
    };

    template <class T>
    int foo(const T &obj, double num) {
        std::cout << "temp2::foo" << typeid(T).name()
                  << ">\nnum = " << num << std::endl;
        return 10;
    }

    bool foo(Derived *obj) {
        std::cout << "temp2::foo\n"
                  << "Derived::m_obj::number" << obj->m_obj->number << std::endl;
        return true;
    }
}

namespace ca {
    template <class T>
    class ConstArray {
        public:
            ConstArray(std::size_t n; const T& value)
            : m_data(new T[n]), m_size(n)
            {
                for (std::size_t i = 0; i < n; i++) {
                    m_data[i] = value;
                }
            }
            ~ConstArray() {
                delete[] m_data;
            }

            std::size_t size()
        private:
            T* m_data;
            std::size_t m_size;
    }
}

int main()
{
    // lvalue
    int a = 10;      // переменная
    int &ref = a;    // ссылка - тоже переменная
    int &&rref = 10; // правая ссылка - тоже переменная
    foo() = 20;      // функция, возвращающая левую ссылку

    // rvalue
    2, a + 1; // литерали и выражения над ними
    baz();    // функция, возвращающая не ссылочный тип
    static_cast<int &&>(a);
    // --------

    const char str[] = "simple string";
    std::cout << &str << std::endl;
    std::cout << &"string literal" << std::endl;

    temp::Base b;
    foo(&b, 10);\

    std::cout << "hello";

    std::cout << std::endl;
    temp2::Derived d(&b);

    /*
    * 1. Поиск имён (lookup)
    * Порядок поиска: текущая область видимости, глобальная область видимости,
    * пространство имен аргументов (ADL - argument dependent lookup).
    * 2. Раскрытие концептов
    * 3. Раскрытие шаблонных аргументов
    * 4. Разрешение перегрузок
    * */


    return 0;

    
}
