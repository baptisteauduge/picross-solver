#include <iostream>
#include <vector>
#include "Grid.h"

int main() {
    std::vector<int> sequence = {2, 1, 5};
    tomographie::Grid tab(1, 10, tomographie::EMPTY);
    std::cout << tab.line_can_contain_sequence2(0, 9, 3, sequence) << std::endl;

    return 0;
}
