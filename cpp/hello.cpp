#include <iostream>
#include <iomanip>

struct Foo {
int x, y;
Foo(int yp) : y{yp}, x{y} {}
};
int main() {
Foo f(10);
std::cout << f.x << " " << f.y << std::endl;
}