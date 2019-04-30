#include <iostream>
#include <string>

using namespace std::literals;

struct STA {
    std::pair<int, std::string> current_;
    auto operator* () { return current_; }
};

int main() {
    STA st{std::make_pair(100, "abc"s)};
    auto&& [i, s] = *st;

    std::cout << i << " " << s << "\n";
}
