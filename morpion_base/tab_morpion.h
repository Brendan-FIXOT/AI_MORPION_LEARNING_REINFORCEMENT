#ifndef TAB_MORPION_H
#define TAB_MORPION_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>

class BaseClass {
public :
    BaseClass() {}

    std::vector<int> morpion_choice(std::vector<int> board, int player);

    bool check_win(std::vector<int> board);

    std::string interface_board(std::vector<int> board);

    float relu(float x);

    std::vector<float> softmax(const std::vector<float>& outputs);

};

#endif // TAB_MORPION_H