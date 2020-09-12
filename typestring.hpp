##ifndef TYPESTRING_HPP_INCLUDED
#define TYPESTRING_HPP_INCLUDED

#include<string_view>

namespace typestring
{
    template<typename T>
    inline constexpr auto nameof()
    {
    #if defined(__clang__)
        // 0         1         2         3
        // 0123456789012345678901234567890123456789
        // auto typestring::nameof() [T = T]
        auto sv = std::string_view(__PRETTY_FUNCTION__);
        return sv.substr(31, sv.size() - 32);
    #elif defined(__GNUC__) || defined(__GNUG__)
        // 0         1         2         3         4
        // 01234567890123456789012345678901234567890123456789
        // constexpr auto typestring::nameof() [with T = T]
        auto sv = std::string_view(__PRETTY_FUNCTION__);
        return sv.substr(46, sv.size() - 47);
    #elif defined(_MSC_VER)
        // MSVC has this great idea that we need to know
        // if a type is a union, enum, struct or class.
        // 0         1         2         3
        // 0123456789012345678901234567890123456789
        // auto __cdecl typestring::nameof<T>(void)
        auto sv = std::string_view(__FUNCSIG__);
        sv = sv.substr(32, sv.size() - 39);
        if(sv.find("struct ") != std::string_view::npos)
            return sv.substr(7);
        if(sv.find("class ") != std::string_view::npos)
            return sv.substr(6);
        if(sv.find("union ") != std::string_view::npos)
            return sv.substr(6);
        if(sv.find("enum ") != std::string_view::npos)
            return sv.substr(5);
        return sv;
    #else
    #error "Unsupported compiler"
    #endif
    }

    template<typename T>
    inline constexpr auto name = nameof<T>();

    template<typename T, typename U>
    inline constexpr bool less = name<T> < name<U>;
}

#endif // TYPESTRING_HPP_INCLUDED
