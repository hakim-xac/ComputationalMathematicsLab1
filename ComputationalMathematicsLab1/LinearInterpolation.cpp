#include "LinearInterpolation.h"
#include "Functions.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cassert>

namespace KHAS {

    void LinearInterpolation::loop() const noexcept
    {
        size_t cmd{};
        while (cmd != 3) {
            system("cls");
            showHeader();

            if (!menu_.runCommand(cmd)) showUnknownCommand();
            menu_.show();
            cmd = showReadCommand();
        }
    }

    void LinearInterpolation::showHeader(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', data_.width_screen) };
        std::string subject_header{ "Дисциплина:" };
        std::string subject_name{ "Вычислительная математика" };
        std::string student_header{ "Студент:" };
        std::string student_name{ "Хакимов А.С." };
        std::string group_header{ "Группа:" };
        std::string group_name{ "ПБ-11" };
        std::string variant_header{ "Вариант:" };
        std::string variant_name{ "№1" };
        std::string theme_header{ "Тема:" };
        std::string theme_name{ "Линейная интерполяция" };

        size_t width{ (data_.width_screen - 3) / 2 - 2 };

        assert(width >= 0 && "you need to increase the width of the output on the screen");
        assert(subject_header.size() <= width && subject_name.size() <= width);
        assert(student_header.size() <= width && student_name.size() <= width);
        assert(group_header.size() <= width && group_name.size() <= width);
        assert(variant_header.size() <= width && variant_name.size() <= width);
        assert(theme_header.size() <= width && theme_name.size() <= width);


        out << delim  << "\n"; 
        out << "| " << std::setw(width) << std::left << subject_header  << " | " << std::setw(width) << std::right << subject_name  << " |\n";
        out << "| " << std::setw(width) << std::left << student_header  << " | " << std::setw(width) << std::right << student_name  << " |\n";
        out << "| " << std::setw(width) << std::left << group_header    << " | " << std::setw(width) << std::right << group_name    << " |\n";
        out << "| " << std::setw(width) << std::left << variant_header << " | " << std::setw(width) << std::right << variant_name << " |\n";
        out << "| " << std::setw(width) << std::left << theme_header    << " | " << std::setw(width) << std::right << theme_name    << " |\n";
        out << delim << "\n";
    }

    void LinearInterpolation::showUnknownCommand(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', data_.width_screen) };
        out << delim << "\n";
        out << generateString("Неизвестная команда", data_.width_screen) << "\n";
        out << delim << "\n";
    }

    void LinearInterpolation::printValueTable(std::ostream& out) const noexcept
    {
        size_t width_all{ (data_.width_screen - 3) / 2 - 2 };
        size_t width_left_part{ width_all / 2 + 4 };
        size_t width_right_part{ width_all - width_left_part + 3 };

        auto delim{ delimiter('-', data_.width_screen) };
        out << delim << "\n";
        out << generateString("Таблицы значений функции с рассчитанным шагом", data_.width_screen) << "\n";
        out << delim << "\n";
        out << "| " << std::setw(width_left_part) << std::right << " Xi " << std::setw(width_right_part) << " | "
            << std::setw(width_left_part) << std::right << "f(Xi)" << std::setw(width_right_part) << " |\n"
            << delim << "\n";

        for (auto&& [xi, fxi]: value_table_) {
            out << "| " << std::fixed << std::setprecision(4)
                << std::setw(width_left_part) << std::right << xi  << std::setw(width_right_part) << " | "
                << std::setw(width_left_part) << std::right  << fxi << std::setw(width_right_part) << " |\n";
            out << delim << "\n";
        }
    }
    void LinearInterpolation::printExactAndApproximate(std::ostream& out) const noexcept
    {
        size_t width_all{ (data_.width_screen - 6) / 3 - 2 };
        size_t width_left_part{ width_all / 2 + 4 };
        size_t width_right_part{ width_all - width_left_part+3 };


        auto delim{ delimiter('-', data_.width_screen) };
        out << delim << "\n";
        out << generateString("Таблица точных и приближенных значений функции", data_.width_screen) << "\n";
        out << delim << "\n";
        out << "| " << std::setw(width_left_part) << std::right << " x " << std::setw(width_right_part) << " | "
            << std::setw(width_left_part) << std::right << "f(x) точн." << std::setw(width_right_part) << " | "
            << std::setw(width_left_part) << std::right << "f(x) прибл." << std::setw(width_right_part+2) << " |\n"
            << delim << "\n";

        for (auto&& [x, fxe, fxa]: table_exact_and_approximate_values_) {
            out << std::fixed << "| " << std::setw(width_left_part) << std::right << std::setprecision(4) << x  << std::setw(width_right_part) << " | "
                << std::setw(width_left_part) << std::right << std::setprecision(6) << fxe << std::setw(width_right_part) << " | "
                << std::setw(width_left_part) << std::right << std::setprecision(6) << fxa << std::setw(width_right_part+2) << " |\n";
            out << delim << "\n";
        }
    }

    double LinearInterpolation::mathFunc(double x) const noexcept
    {
        return 8 * std::cos((x + 20) / 2);
    }

    double LinearInterpolation::linearInterpolation(double x, std::pair<double, double> x2, std::pair<double, double> x3) const noexcept
    {
        double tmp{ (x - x2.first) / data_.step };
        return x2.second + tmp * (x3.second - x2.second);
    }

    void LinearInterpolation::init() noexcept
    {
        assert(data_.right_range > data_.left_range);
        assert(data_.step > 0);

        size_t size_data{ static_cast<size_t>(std::round((data_.right_range - data_.left_range) / data_.step)) };

        value_table_.reserve(size_data);
        for (auto i{ data_.left_range }, ie{ data_.right_range }, step{ data_.step }; i < ie; i += step) {
            value_table_.emplace_back(std::make_pair(i, precision(mathFunc(i), 4)));
        }

        table_exact_and_approximate_values_.reserve(size_data-1);
        for (size_t i{}, ie{ size_data-1 }; i != ie; ++i) {
            double x{ precision(2 + 0.6*data_.step*(i+1), 4) };

            auto&& [left_range, right_range] { findRange(x) };
            
            double x_exact{ precision(mathFunc(x), 6) };
            double x_approximate{ precision(linearInterpolation(x, left_range, right_range), 6) };
            table_exact_and_approximate_values_.emplace_back(std::array<double, 3>{ x, x_exact, x_approximate });
        }
        menu_.insert("Вывод таблицы значений функции с рассчитанным шагом", [&]() { printValueTable();  });
        menu_.insert("Вывод таблицы точных и приближенных значений функции", [&] { printExactAndApproximate();  });
        menu_.insert("Выход", [] {});

    }

    size_t LinearInterpolation::showReadCommand(std::istream& in) const noexcept
    {
        size_t cmd;
        std::string cmd_name{ "Введите команду:" };
        std::cout << cmd_name << delimiter('_', data_.width_screen - cmd_name.size())
            << delimiter('\b', data_.width_screen - cmd_name.size());

        if (!(in >> cmd)) cmd = -1;
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return cmd;
    }

    std::pair<std::pair<double, double>, std::pair<double, double>> LinearInterpolation::findRange(double x) const noexcept
    {
        assert(value_table_.size() > 0);

        for (size_t i{}, ie{ value_table_.size() - 1 }; i != ie; ++i) {
            if (x >= value_table_[i].first)
                return { { value_table_[i].first, value_table_[i].second }
                        , { value_table_[i+1].first, value_table_[i+1].second } };
        }
        return { {0, 0}, {0, 0} };
    }

}