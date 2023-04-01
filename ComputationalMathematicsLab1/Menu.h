#pragma once
#include <vector>
#include <string>
#include "MenuItem.h"

namespace KHAS {
    class Menu final
    {
    public:
        explicit Menu(size_t width_screen);

        void show(std::ostream& out = std::cout) const noexcept;
    private:
        size_t width_screen_;
        std::vector<MenuItem> buffer_;
    };

}

#include "Menu.hpp"