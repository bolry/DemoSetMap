#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// CRUD

// C++98
// ------------
// inheritance
// classes
// polymorphism
// encapsulation
//
// more things
//
// exceptions
// templates
// function overloads
// inline functions
// STL
// references


// C++03



int main() {
#if __cplusplus < 201103L
    std::vector<int> fib;
    fib.reserve(6);
    fib.push_back(1);
    fib.push_back(1);
    fib.push_back(2);
    fib.push_back(3);
    fib.push_back(5);
    fib.push_back(8);
#else
    std::vector<int> fib = {1, 1, 2, 3, 5, 8,};
#endif

    std::vector<std::string> stringFib;
    stringFib.reserve(fib.size());

#if !defined(__cpp_range_based_for)
    std::vector<int>::iterator it = fib.begin();
    std::vector<int>::iterator itEnd = fib.end();
    for (; it != itEnd; ++it) {
        std::ostringstream ss;
        ss << *it;
        stringFib.push_back(ss.str());
    }
#else  // C++11
    // Short and sweet
    for (auto i: fib) stringFib.push_back(std::to_string(i));

    //  Equivalent to (first time around)
    {
        auto &&r = fib;
        using std::begin;
        using std::end;
        for (auto it = begin(r), itEnd = end(r); it != itEnd; ++it) {
            auto i = *it;
            stringFib.push_back(std::to_string(i));
        }
    }
    // Equivalent to (currently)  Closer to  C++17/20
    {
        auto &&r = fib;
        using std::begin;
        using std::end;
        auto it = begin(r);
        auto itEnd = end(r);
        for (; it != itEnd; ++it) {
            auto i = *it;
            stringFib.push_back(std::to_string(i));
        }
    }
    // Please checkout the `subtletiesrangeloop.cpp' for some caveats
#endif

    for (std::size_t i = 0; i < stringFib.size(); ++i) {
        std::cout << stringFib[i] << ' ';
    }

#if __cplusplus < 201103L  // C++98/03
    std::auto_ptr<int> obj(new int(42));
    std::auto_ptr<int> obj2 = obj;
#else
    std::unique_ptr<int> obj(new int(42));
    std::unique_ptr<int> obj2 = std::move(obj);
#endif

    return obj2.get() ? EXIT_FAILURE : EXIT_SUCCESS;
}
