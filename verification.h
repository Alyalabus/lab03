#ifndef LAB_VERIFICATION_H
#define LAB_VERIFICATION_H
#pragma once
#include <iostream>
#include <vector>


namespace verification {
    bool check_int_double();
    template <typename T>
    void add_attributes(T& attribute, int left_border, int right_border) {
        bool check;
        while (true) {
            std::cin >> attribute;
            check = check_int_double();
            if (check && (attribute > right_border || attribute < left_border)) {
                std::cout << "YOUR NUMBER IS OUT OF RANGE" << std::endl;
                std::cout << "Enter a new number: ";
            }
            else if (check) {
                break;
            }
        }
    }
    bool choose_id(std::vector<int>& vec_id, int& id);
    void check_string(std::string& string_cin, int max_symbols);
    void true_false(bool& repair);
}

#endif //LAB_VERIFICATION_H


