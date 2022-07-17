#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <rang_util.hpp>

using namespace rang;
using namespace rang::util;

namespace ru = rang::util;

namespace
{
    constexpr auto tag = "[rang]";
    //--------- Utilities ------------------
    inline constexpr auto st_temp_normal = ru::make_style(rang::fg::reset);
    inline constexpr auto st_temp_hot = ru::make_style(rang::fg::yellow);
    inline constexpr auto st_temp_dangous = ru::make_style(rang::fg::red);

    inline auto render_temperature(unsigned int t, unsigned int min_temp_warn = 70, unsigned int min_temp_hot = 80)
    {
        return ru::make_style(t < min_temp_warn ? st_temp_normal : (t < min_temp_hot ? st_temp_hot : st_temp_dangous), t);
    }
}

TEST_CASE("issue", tag)
{

    std::cout << render_temperature(90);
}

TEST_CASE("styles", tag)
{
    auto dummy = make_style();
    std::cout << dummy("Hello\n");

    auto bold = make_style(style::bold);

    std::cout << bold << "Hello ";
    std::cout << bold("Hello ");

    int t = 100;
    auto bold1 = make_style(bold);
    std::cout << bold1(t);

    auto H1 = make_style(style::bold, fg::red);
    std::cout << H1 << "World\n";

    auto Title = make_style(H1, fg::red, bg::black);
    std::cout << Title(" Done") << html::BR3;

    std::cout << make_style(rang::fg::green, t);

    SECTION("prefix")
    {
        auto prefix = H1("debug: ");

        std::cout << prefix("error message 1") << html::BR;
        std::cout << prefix("error message 2") << html::BR;
        std::cout << prefix("error message 3") << html::BR;
    }
}