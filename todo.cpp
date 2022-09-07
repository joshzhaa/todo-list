#include <iostream>
#include <chrono>
#include "color.h"

#ifdef DEBUG
void test_colors(std::ostream& out) {
    out << FORE_RED     "RED text"     RESET "\n";
    out << FORE_GREEN   "GREEN text"   RESET "\n";
    out << FORE_YELLOW  "YELLOW text"  RESET "\n";
    out << FORE_BLUE    "BLUE text"    RESET "\n";
    out << FORE_MAGENTA "MAGENTA text" RESET "\n";
    out << FORE_CYAN    "CYAN text"    RESET "\n";

    out << BACK_RED     "RED background"     RESET "\n";
    out << BACK_GREEN   "GREEN background"   RESET "\n";
    out << BACK_YELLOW  "YELLOW background"  RESET "\n";
    out << BACK_BLUE    "BLUE background"    RESET "\n";
    out << BACK_MAGENTA "MAGENTA background" RESET "\n";
    out << BACK_CYAN    "CYAN background"    RESET "\n";
}
#endif

int main() {
#ifdef DEBUG
    test_colors(std::cout);
#endif
    std::chrono::day d(7);
    std::chrono::day next = d++;
    //std::cout << d << '\n';
    std::chrono::month m(9);
    std::cout << unsigned(m) << '\n';
    std::chrono::year y(2022);
    //std::cout << y << '\n';
    std::chrono::year_month_day date(y, m, d);
    //std::cout << date << '\n';
    return 0;
}
