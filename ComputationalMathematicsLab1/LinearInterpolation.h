#pragma once
#include <vector>
#include <string>
#include "Menu.h"


namespace KHAS {
    class LinearInterpolation final {
    public:

        LinearInterpolation(size_t width_screen);
       void run() const noexcept;
    private:
        void showHeader(std::ostream& out = std::cout) const noexcept;
    private:
        size_t width_screen_;
        Menu menu_;
    };
}

