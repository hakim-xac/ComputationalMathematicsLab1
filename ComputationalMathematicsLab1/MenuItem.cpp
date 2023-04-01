#include "MenuItem.h"

namespace KHAS {

    size_t MenuItem::getId() const noexcept
    {
        return id_;
    }

    const std::string& MenuItem::getName() const& noexcept
    {
        return name_;
    }

    const size_t MenuItem::createId() const noexcept
    {
        static size_t base_index{};
        return ++base_index;
    }

}