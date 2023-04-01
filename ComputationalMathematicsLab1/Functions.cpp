#include <string>

namespace KHAS {

    std::string delimiter(char c, size_t width_screen) noexcept
    {
        return std::string(width_screen, c);
    }
}