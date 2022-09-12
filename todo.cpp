#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>

#include "color.h"

#ifdef DEBUG
void test_colors(std::ostream& out) {
    out << "COLOR TEST\n";

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
//workaround for lack of c++20 text formatting support
void pad(std::string& target, size_t width) {
    while (target.size() < width) {
        target.push_back(' ');
    }
}
//insertion operator overload that prints date in YYYY/MM/DD format
std::ostream& operator<< (std::ostream& out, const std::chrono::year_month_day& date) {
    return out << std::setw(4) << std::setfill('0') << int(date.year()) << '/' <<
        std::setw(2) << unsigned(date.month()) << '/' <<
        std::setw(2) << unsigned(date.day());
}
//addition operator to add days to year_month_day, I don't know how to modify
struct Task {
    std::chrono::year_month_day date;
    std::string description;
};
//reads tasks from in into vector, returns length of longest task description
size_t read_list(std::istream& in, std::vector<Task>& tasks) {
    int year, month, day;
    char slash;
    size_t longest_description = 0;
    while (in >> year >> slash >> month >> slash >> day) {
        std::string description;
        std::getline(in, description);
        tasks.push_back(Task{std::chrono::year_month_day(std::chrono::year(year), std::chrono::month(month),
            std::chrono::day(day)), description});
        if (description.size() > longest_description) longest_description = description.size();
    }
    return longest_description;
}
//print todo list in a formatted way
void print_list(std::ostream& out, std::vector<Task>& tasks, size_t description_width) {
    using namespace std::chrono;
    out << std::setfill(' ');
    auto task = tasks.begin();
    //advance iterator to upper bound, printing each step
    auto print_block = [&](const sys_days& upper_bound, const char* color) {
        while (task != tasks.end() && task->date < upper_bound) {
            std::string& description = task->description;
            pad(description, description_width);
            out << color << year_month_day{task->date} << description << RESET "\n";
            ++task;
        }
    };
    //Get current date:
    //I think I can't use this because of clang's partial c++20 support
    //auto today = year_month_day{floor<days>(current_zone()->to_local(system_clock::now()))};
    //std::time_t c_time = system_clock::to_time_t(system_clock::now());
    //std::tm* tm = std::localtime(&c_time);
    //auto today = year_month_day{year{tm->tm_year + 1900}, month(tm->tm_mon + 1), day(tm->tm_mday)};
    auto const now = system_clock::now();
    sys_days today = floor<days>(now);
    print_block(today, BACK_RED); //print overdue tasks
    print_block(today += days{7}, BACK_MAGENTA); //print one week
    print_block(today += days{14}, BACK_BLUE); //print another 2 weeks
    print_block(today += days{365}, BACK_CYAN);
}
int main() {
#ifdef DEBUG
    test_colors(std::cout);
#endif
    std::ifstream file("list.txt");
    std::vector<Task> tasks;
    size_t description_width = read_list(file, tasks);
    std::sort(tasks.begin(), tasks.end(), [](const Task& left, const Task& right) {
        return left.date < right.date;
    });
    print_list(std::cout, tasks, description_width + 5);
    file.close();
    return 0;
}
