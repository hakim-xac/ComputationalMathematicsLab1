#include "LinearInterpolation.h"
#include "InputData.h"



int main() {
    std::setlocale(LC_ALL, "Russian");
    KHAS::LinearInterpolation lip{ KHAS::InputData{ 63, 2.0, 2.21, 0.014 } };
    lip.loop();

    return 0;
}