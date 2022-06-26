#include <iostream>

#if 0

#include <locale>
#include <vector>

namespace {
    std::vector<long long> createRangeOfIntegers() { // C++11 `long long'
        return {1'325'627'888ll, 79'894'576'510'188LL, 6'590'140LL,
                1'704'640ll}; // C++14 quotes (') as digits separator
    }

    std::vector<long long> const &doNothing(std::vector<long long> const &a_vec) {
        return a_vec;
    }

    struct easyReadLargeIntegers : std::numpunct<char> {
        char do_thousands_sep() const override { return '^'; }  // C++11 `override'
        // Hindi uses a 2-digit grouping, except for the 3-digit grouping for denoting hundreds
        std::string do_grouping() const override { return "\x03\x02"; } // "\x3\x2" or "\3\2"
        std::string do_truename() const override { return "Yea"; }  // Old English
        std::string do_falsename() const override { return "Nay"; } // Middle English
    };
} // namespace

int main(int argc, [[maybe_unused]] char *argv[]) { // C++17 attribute `maybe_unused`
    std::locale prevLocale = std::cout.imbue(std::locale{std::cout.getloc(), new easyReadLargeIntegers});
    for (auto &x: createRangeOfIntegers()) {
        std::cout << x << "  ";
    }
    std::cout << "\nAre the number of arguments to the program odd? "
              << std::boolalpha << (argc % 2 == 0) << "!\n";
    std::cout.imbue(prevLocale);
    for (auto &x: createRangeOfIntegers()) {
        std::cout << x << "  ";
    }
    std::cout << "\nAre the number of arguments to the program odd? " << (argc % 2 == 0) << "!\n";
}

#else

#include <string>
#include <utility>

namespace {

    class Galimatias {
        std::string m_str;

    public:
        explicit Galimatias(std::string a_str) : m_str(std::move(a_str)) {}

        [[nodiscard /*("nodiscard from C++17, explanation possible from C++20")*/ ]]
        std::string const &getString() const noexcept {
            return m_str;
        }

    }; // class Galimatias

    Galimatias makeGalimatias() { return Galimatias{"shorty"}; }
} // namespace

int main() {
    auto const &g = makeGalimatias();
    std::cout << "Ref string: `" << g.getString() << "'\n";
    for (auto  &&x:
            makeGalimatias().getString()) { // We have undefined behaviour. Why?
        std::cout << x << ' ';
    }
}

#endif
