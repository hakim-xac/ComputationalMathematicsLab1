#include <algorithm>
#include <iterator>
#include <iomanip>
#include "Menu.h"
#include "Functions.h"

namespace KHAS {

    Menu::Menu(size_t width_screen)
        : width_screen_{ width_screen }
        , buffer_{} {
        buffer_.reserve(3);
        buffer_.emplace_back(MenuItem{ "Вывод таблицы значений функции с рассчитанным шагом", [] {} });
        buffer_.emplace_back(MenuItem{ "Вывод таблицы точных и приближенных значений функции", [] {} });
        buffer_.emplace_back(MenuItem{ "Выход", [] {} });
    };

    void Menu::show(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        out << delim << "\n";
        out << generateString("Меню", width_screen_) << "\n";
        out << delim << "\n";
        for (auto&& elem : buffer_) {
            auto name{ elem.getName() };
            assert(name.size()+10 <= width_screen_);
            out << std::setw(5) << std::left << elem.getId() << " | " << std::setw(width_screen_-10) << std::right << name << " |\n";
        }
        out << delim << "\n";
    }

}