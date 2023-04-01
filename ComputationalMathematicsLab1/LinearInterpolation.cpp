#include "LinearInterpolation.h"
#include "Functions.h"
#include <iostream>
#include <iomanip>
#include <cassert>

namespace KHAS {
    LinearInterpolation::LinearInterpolation(size_t width_screen)
        : width_screen_{ width_screen }
        , menu_ { width_screen } {}

    void LinearInterpolation::run() const noexcept
    {
        showHeader();
        menu_.show();
    }

    void LinearInterpolation::showHeader(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        std::string student_header{ "Студент:" };
        std::string student_name{ "Хакимов А.С." };
        std::string group_header{ "Группа:" };
        std::string group_name{ "ПБ-11" };
        std::string subject_header{ "Тема:" };
        std::string subject_name{ "Линейная интерполяция" };


        assert(width_screen_ >= 63 && "you need to increase the width of the output on the screen");
        assert(student_header.size() <= 28 && student_name.size() <= 28);
        assert(group_header.size() <= 28 && group_name.size() <= 28);
        assert(subject_header.size() <= 28 && subject_name.size() <= 28);


        out << delim  << "\n";
        out << "| " << std::setw(28) << std::left << student_header << " | " << std::setw(width_screen_ - 35) << std::right << student_name << " |\n";
        out << "| " << std::setw(28) << std::left << group_header << " | " << std::setw(width_screen_ - 35) << std::right << group_name << " |\n";
        out << "| " << std::setw(28) << std::left << subject_header << " | " << std::setw(width_screen_ - 35) << std::right << subject_name << " |\n";
        out << delim << "\n";
    }

}