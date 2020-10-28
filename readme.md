# typestring
typestring converts a type to its name as a constexpr std::string_view.

````c++
namespace N { struct S{ struct R; }; }
using T = N::S::R;
std::cout << typestring::name<int>;     // prints int
std::cout << typestring::name<N::S::R>; // prints N::S::R
std::cout << typestring::name<T>;       // prints N::S::R
````

The name is unique unless there are `auto` or lambda parameters

````c++
template<auto> struct S;
std::cout << typestring::name<S<0>>;            // prints S<0>
std::cout << typestring::name<S<0u>>;           // prints S<0>
std::cout << typestring::name<decltype([]{})>;  // prints <lambda()> on gcc
                                                // prints (lambda at file.cpp:10:20) on clang
````

The name can be used as a ordering on types, provided as `less`

````c++
std::cout << typestring::less<int, void>;   // 1
std::cout << typestring::less<void, int>;   // 0
````

Supports gcc, clang and msvc.
