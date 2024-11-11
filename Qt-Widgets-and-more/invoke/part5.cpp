/* MIT License

Copyright (C) 2023 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Foo.h"
#include <algorithm>
#include <iostream>
#include <vector>

// clang-format off
namespace {

template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::true_type /* is_member_function_pointer<Function> */)
{
    return (o.*f)();
}

template <typename Function, typename Object>
auto invoke_helper(Function f, const Object &o,
                   std::false_type /* is_member_function_pointer<Function> */)
{
    return o.*f;
}

template <typename Function, typename Object>
auto invoke(Function f, const Object &o)
{
    return invoke_helper(f, o,
                         std::is_member_function_pointer<Function>{});
}

template <typename Container, typename Member>
void sort_by(Container &container, Member member)
{
    std::sort(container.begin(), container.end(), [member](const auto &x, const auto &y) {
        return ::invoke(member, x) < ::invoke(member, y);
    });
}
} // end namespace
// clang-format on

void part5()
{
    std::cout << "\n========== invoke - part5 ==========\n";
    std::vector<Foo> v{{12, 100}, {20, 3}, {30, 30}};

    sort_by(v, &Foo::second);
    print("sort by member variable", v);

    sort_by(v, &Foo::fraction);
    print("sort by member function", v);
}
