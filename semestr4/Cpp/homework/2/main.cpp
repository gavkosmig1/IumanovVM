#include <type_traits>

namespace TypeListImpl {

    template <typename... Types>
    struct TypeList {};


    template <typename TypeList, int Index>
    struct GetType;

    // Рекурсивный случай: "прокручиваем" список, пока Index != 0
    template <typename Head, typename... Tail, int Index>
    struct GetType<TypeList<Head, Tail...>, Index> {
        using type = typename GetType<TypeList<Tail...>, Index - 1>::type;
    };

    // Базовый случай: Index == 0, возвращаем Head
    template <typename Head, typename... Tail>
    struct GetType<TypeList<Head, Tail...>, 0> {
        using type = Head;
    };

    // Ошибка: индекс за пределами
    template <int Index>
    struct GetType<TypeList<>, Index> {
        static_assert(Index < 0, "Index out of bounds");
    };


    template <typename TypeList>
    struct Size; 

    template <typename... Types>
    struct Size<TypeList<Types...>> {
        static constexpr int value = sizeof...(Types);
    };


    template <typename TypeList, typename T>
    struct Contains;

    template <typename T, typename... Types>
    struct Contains<TypeList<Types...>, T> {
        static constexpr bool value = (std::is_same_v<T, Types> || ...);
    };


    template <typename TypeList, typename T, int Index = 0>
    struct IndexOf;

    template <typename T, typename... Types, int Index>
    struct IndexOf<TypeList<T, Types...>, T, Index> {
        static constexpr int value = Index;
    };

    template <typename Head, typename... Tail, typename T, int Index>
    struct IndexOf<TypeList<Head, Tail...>, T, Index> {
        static constexpr int value = IndexOf<TypeList<Tail...>, T, Index + 1>::value;
    };


    template <typename TypeList, typename T>
    struct PushBack;

    template <typename... Types, typename T>
    struct PushBack<TypeList<Types...>, T> {
        using type = TypeList<Types..., T>;
    };

    
    template <typename TypeList, typename T>
    struct PushFront;

    template <typename... Types, typename T>
    struct PushFront<TypeList<Types...>, T> {
        using type = TypeList<T, Types...>;
    };

}

int main() {
    
    using namespace TypeListImpl;

    using MyTypeList = TypeList<int, double, char>;

    static_assert(std::is_same_v<GetType<MyTypeList, 0>::type, int>);
    static_assert(Size<MyTypeList>::value == 3);
    static_assert(Contains<MyTypeList, double>::value);
    static_assert(IndexOf<MyTypeList, char>::value == 2);

    using NewTypeList = PushBack<MyTypeList, float>::type;
    static_assert(std::is_same_v<GetType<NewTypeList, 3>::type, float>);

    using NewTypeList2 = PushFront<MyTypeList, float>::type;
    static_assert(std::is_same_v<GetType<NewTypeList2, 0>::type, float>);

    return 0;
}