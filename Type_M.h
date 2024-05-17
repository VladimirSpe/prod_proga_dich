#pragma once

#include <unordered_map>
#include <variant>
#include "Type_L.h"

template <class T, class... Ts>
struct typemap {
    char value[sizeof(T)];
    typemap<Ts...> *tail;
};

template<typename... V>
class TypeMap{
public:
    TypeMap() = default;

    template<typename T>
    void AddValue(T value){
        constexpr size_t index = types::template GetIndex<T>();
        values.insert({index, value});
    }

    template<typename T>
    T GetValue(){
        try {
            constexpr size_t index = types::template GetIndex<T>();
            std::variant<V...> variantValue = values.at(index);
            return std::get<T>(variantValue);
        } catch (...) {
            std::cout << "Invalid Value" << std::endl;
        }
    }

    template<typename T>
    bool Contains(){
        return types::template IsIncluded<T>;
    }

    template<typename T>
    void RemoveValue(){
        constexpr size_t index = types::template GetIndex<T>();
        values.erase(index);
    }

private:
    std::unordered_map<size_t, std::variant<V...>> values;
    using types = TypeList<V...>;

};