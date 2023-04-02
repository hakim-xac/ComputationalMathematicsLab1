#pragma once
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <cassert>
#include "Menu.h"
#include "InputData.h"


namespace KHAS {
    class LinearInterpolation final {
    public:
        template <typename Data>
            requires std::is_convertible_v<Data, InputData>
        LinearInterpolation(Data&& data);

       void loop() const noexcept;
    private:
        void init() noexcept;
        void showHeader(std::ostream& out = std::cout) const noexcept;
        void showUnknownCommand(std::ostream& out = std::cout) const noexcept;
        void printValueTable(std::ostream& out = std::cout) const noexcept;
        void printExactAndApproximate(std::ostream& out = std::cout) const noexcept;
        double mathFunc(double x) const noexcept;
        double linearInterpolation(double x, std::pair<double, double> x2, std::pair<double, double> x3) const noexcept;
        size_t showReadCommand(std::istream& in = std::cin) const noexcept;
        std::pair<std::pair<double, double>, std::pair<double, double>> findRange(double x) const noexcept;
    private:
        InputData data_;
        Menu menu_;
        std::vector<std::pair<double, double>> value_table_;
        std::vector<std::array<double, 3>> table_exact_and_approximate_values_;
    };







    template <typename Data>
        requires std::is_convertible_v<Data, InputData>
    LinearInterpolation::LinearInterpolation(Data&& data) 
        : data_{ std::forward<Data>(data) }
        , menu_{ data_.width_screen } {

        init();
    }
}

