#pragma once
#include <iostream>
#include <string>
#include <vector>

template<typename... nTypes>
struct TypeList{
public:

    template<size_t i, typename... U>
    struct GetType{};

    template<typename T, typename... U>
    struct GetType<0, T, U...>{
        using ntype = T;
    };

    template<size_t i, typename T, typename... U>
    struct GetType<i, T, U...>{
        using ntype = typename GetType<i - 1, U...>::ntype;
    };

    template<size_t i>
    using GetType_call = typename GetType<i, nTypes...>::ntype;


    static constexpr std::size_t len = sizeof...(nTypes);


    template<typename T>
    static constexpr size_t GetIndex(){
        static_assert(sizeof...(nTypes) > 0, "Incorrect Type");
        if constexpr (std::is_same_v<T, GetType_call<0>>)
            return 0;
        else
            return GetIndex<1, T>();
    }

    template<size_t i, typename T>
    static constexpr size_t GetIndex(){
        static_assert(sizeof...(nTypes) > i, "Incorrect Type");
        if constexpr (std::is_same_v<T, GetType_call<i>>)
            return i;
        else
            return GetIndex<i + 1, T>();
    }

    template<typename T>
    static constexpr bool CheckIsIncluded(){
        return false;
    }

    template<typename T, typename U, typename... V>
    static constexpr bool CheckIsIncluded(){
        return std::is_same_v<T, U> || CheckIsIncluded<T, V...>();
    }

    template<typename T>
    static constexpr bool IsIncluded = CheckIsIncluded<T, nTypes...>();


    template<typename T>
    using Append = TypeList<nTypes..., T>;


    template<typename T>
    using BeginAdd = TypeList<T, nTypes...>;
};
namespace tests {
    void test1() {
        using nList0 = TypeList<>;
        static_assert(nList0::len == 0);
        static_assert(!nList0::IsIncluded < int > );

        using nList1 = nList0::Append<int>;
        using nList2 = nList1::Append<char>;
        using nList3 = nList2::Append<double>;
        using nList4 = nList3::Append<std::vector<int>>;

        static_assert(std::is_same_v<nList4::GetType_call < 0>, int > );
        static_assert(std::is_same_v<nList4::GetType_call < 1>, char > );
        static_assert(std::is_same_v<nList4::GetType_call < 2>, double > );
        static_assert(std::is_same_v<nList4::GetType_call < 3>, std::vector<int>>);
        static_assert(nList4::len == 4);
        static_assert(nList4::GetIndex<int>() == 0);
        static_assert(nList4::GetIndex<char>() == 1);
        static_assert(nList4::GetIndex<double>() == 2);
        static_assert(nList4::GetIndex<std::vector<int>>() == 3);
        static_assert(nList4::IsIncluded < int > );
        static_assert(nList4::IsIncluded < char > );
        static_assert(nList4::IsIncluded < double > );
        static_assert(nList4::IsIncluded < std::vector<int>>);
        static_assert(!nList4::IsIncluded < float > );

        using nList5 = nList4::BeginAdd<std::string>;
        using nList6 = nList5::BeginAdd<std::vector<std::string>>;

        static_assert(std::is_same_v<nList6::GetType_call < 0>, std::vector<std::string>>);
        static_assert(std::is_same_v<nList6::GetType_call < 1>, std::string > );
        static_assert(std::is_same_v<nList6::GetType_call < 2>, int > );
        static_assert(std::is_same_v<nList6::GetType_call < 3>, char > );
        static_assert(std::is_same_v<nList6::GetType_call < 4>, double > );
        static_assert(std::is_same_v<nList6::GetType_call < 5>, std::vector<int>>);
        static_assert(nList6::len == 6);
        static_assert(nList6::GetIndex<std::vector<std::string>>() == 0);
        static_assert(nList6::GetIndex<std::string>() == 1);
        static_assert(nList6::GetIndex<int>() == 2);
        static_assert(nList6::GetIndex<char>() == 3);
        static_assert(nList6::GetIndex<double>() == 4);
        static_assert(nList6::GetIndex<std::vector<int>>() == 5);
        static_assert(nList6::IsIncluded < std::vector<std::string>>);
        static_assert(nList6::IsIncluded < std::string > );
        static_assert(!nList6::IsIncluded < float > );

    }
}