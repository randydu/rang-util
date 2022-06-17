# rang-util

Header-only Utility Project for Colorful Terminal Support (based on Rang)

## Get Started

```cpp
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

    // let's rock!
    std::cout << title("******** COOL APP ********\n\n");
    std::cout << info("app starting...\n");
    std::cout << warn("some parameters not specified, fall back to default value.\n");
    std::cout << error("oops, unexpected error detected!\n\n");

    return 0;
}


```

As you can see, you can predefine view styles to make the output code more maintainable. If you want to change the color of all error messages, just change the error style.


## Dependencies

This project is an add-on utility for the "_rang_" library: 
https://github.com/agauniyal/rang.git

## Compiler

Any c++20 compatible compilers.

## Installation

Just copy the single header file "rang_util.hpp" to the folder where you include headers.
Usually it can be copied side by side with the _rang_ header file ("rang.hpp")

If you use meson-build:

* Copy rang_util.wrap to the "subprojects" folder of your project;
* In your meson.build file, import the dependency:
```meson-build

rang_util_dep = dependency('rang_util')

executable('myproject', srcs, dependencies: [rang_util_dep, ...])
```

## Usage

In rang-util, you can define a style with a single api:

```cpp
auto style_object = make_style(x0, x1, x2, ... );
```

The input parameters can be of __any__ c++ data type supports streaming operator "<<":
```cpp
std::ostream os;

os << x;
```

So you can compose multiple streamable objects into a bundle as another single streamable object. 

```cpp
auto H1 = make_style(style::bold, fg::green);  //H1 with a bold font & green color text
auto H1_black = make_style(H1, bg::black);    // subclass H1 with a black background 
```

In rang-util all style objects are streamble, so they can be used in the original rang's manipulator style:

```cpp
// rang-util style object used as manipulator:
std::cout << H1 << "Hello World" << style::reset << std::endl;
```

Another unique feature of rang-util style object is that: they can work in OOP style:

```cpp
// rang-util style object work in OOP style:
std::cout << H1("Hello World") << std::endl;
```

They encapsulate the rendered content inside the style object and __auto-reset__ the ostream settings at the end of content rendering.

Because a style object with a captured content is also streamable, it can be combined with other style objects as usual:

```cpp
auto prefix = make_style(style::bold, fg::green)("[myapp]: ");
auto log_error = make_style(prefix, fg::red, bg::black); 

std::cout << log_error("file not found!");  // [myapp]: file not found!
```
