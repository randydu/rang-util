#include <rang_util.hpp>

using namespace rang;
using namespace rang::util;

int main()
{
    // the original "rang" manipulator style.
    std::cout << style::bold << "Hello World" << style::reset << std::endl << std::endl;

    // the "rang-util" OOP style
    //  define some styles for rendering
    auto title = make_style(style::bold, fg::blue);

    // define a prefix object for every line of outputs
    auto prefix = make_style(style::bold, fg::green)("cool-app: ");
    // different text style with the prefix
    auto info = make_style(prefix, fg::black);
    auto error = make_style(prefix, style::blink, fg::red);
    auto warn = make_style(prefix, style::underline, fg::yellow);

    std::cout << title("******** COOL APP ********\n\n");
    std::cout << info("app starting...\n");
    std::cout << warn("some parameters not specified, fall back to default value.\n");
    std::cout << error("oops, unexpected error detected!\n\n");

    return 0;
}