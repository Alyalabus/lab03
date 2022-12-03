#include "verification.h"
#include <string>


bool verification::check_int_double() { //is valid
    if (!std::cin || std::cin.peek() != '\n') {
        std::cout << "YOUR NUMBER IS WRONG" << std::endl;
        std::cin.clear();
        std::cin.ignore(15000, '\n');
        std::cout << "Enter a new number: ";
        return false;
    }
    else {
        return true;
    }
}

void verification::check_string(std::string& string_cin, int max_symbols) { //get string value
    while (true) {
        getline(std::cin >> std::ws, string_cin);
        string_cin.erase(string_cin.find_last_not_of(' ') + 1);
        if (!string_cin.empty() && string_cin.size() <= max_symbols) {
            break;
        }
    }
}

void verification::true_false(bool& repair) {
    char true_false;
    while (true) {
        std::cin >> std::ws;
        true_false = char(std::cin.get());
        std::cin.ignore(10000, '\n');
        if (true_false == 'y') {
            repair = true;
            break;
        }
        else if (true_false == 'n') {
            repair = false;
            break;
        }
        else
            std::cout << "You push the wrong button, please try again: ";
    }
}

bool verification::choose_id(std::vector<int>& vec_id, int& id) {
    std::cin >> id;
    for (const auto& item_id : vec_id) {
        if (item_id == id) {
            vec_id.erase(find(vec_id.begin(), vec_id.end(), item_id));
            return false;
        }
    }
    std::cout << "Choose the wrong id, re-choose: ";
    return true;
}
