#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <rang_util.hpp>

using namespace rang;
using namespace rang::util;

namespace
{
    constexpr auto tag = "[rang]";
}

TEST_CASE("styles", tag)
{
    auto bold = make_style(style::bold);

    std::cout << bold << "Hello ";
    std::cout << bold("Hello ");

    auto H1 = make_style(style::bold, fg::red);
    std::cout << H1 << "World\n";

    auto Title = make_style(H1, fg::red, bg::black);
    std::cout << Title(" Done") << html::BR3;

    SECTION("prefix"){
        auto prefix = H1("debug: ");

        std::cout << prefix("error message 1") << html::BR;
        std::cout << prefix("error message 2") << html::BR;
        std::cout << prefix("error message 3") << html::BR;
    }
}