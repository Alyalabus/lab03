#ifndef LAB_FILTER_H
#define LAB_FILTER_H
#pragma once
#include "consolef.h"
#include <vector>
#include <unordered_set>
#include "verification.h"

namespace Filter {
    bool filter_true_false(const Pipe& pipe, bool repair);

    template <typename T>
    bool Filter_by_name(const T& cs_or_pipe, std::string name) {
        if (name == cs_or_pipe.name) {
            return true;
        }
        else {
            return false;
        }
    }

    bool Filter_by_percentworkshops(const CS& cs, double left_border_percent);

    template <typename T, typename T_param>
    using filter_repair = bool(*)(const T& cs_or_pipe, T_param param);

    template <typename T, typename T_param>
    void Filter_id(const std::unordered_map<int, T>& MAP, filter_repair<T, T_param> filter, std::vector<int>& vec_id, T_param param) {
        for (const auto& item : MAP) {
            if (filter(item.second, param)) {
                vec_id.push_back(item.second.get_id());
            }
        }
    }

    void switch_Pipe_true_false(GTS& Gts, std::vector<int>& id_vec);

    template <typename T>
    void Delete_CS_OR_PIPE(std::unordered_map<int, T>& cs_or_pipe, const std::vector<int>& id_vec) {
        for (const auto& id : id_vec) {
            std::cout << cs_or_pipe.at(id);
        }
        char menu_pointer2;
        Console_func::Delete_menu();
        Console_func::Choise_table_point(menu_pointer2);
        switch (menu_pointer2) {
        case '1': {
            for (auto id : id_vec) {
                cs_or_pipe.erase(cs_or_pipe.find(id));
            }
            Console_func::return_to_menu();
            break;
        }
        case '2': {
            std::unordered_set<int> table_pos;
            std::cout << "Enter the serial number in the table which you want to delete: ";
            while (true) {
                int x;
                verification::add_attributes(x, 0, id_vec.size());
                table_pos.insert(id_vec[x - 1]);
                std::cout << "if you want to continue press '1', otherwise press'0': ";
                char menu_pointer3;
                while (true) {
                    Console_func::Choise_table_point(menu_pointer3);
                    if (menu_pointer3 == '1') {
                        break;
                    }
                    else if (menu_pointer3 == '0') {
                        break;
                    }
                }
                if (menu_pointer3 == '0') {
                    break;
                }
                std::cout << "Enter the serial number in the table: ";
            }
            for (auto id : table_pos) {
                cs_or_pipe.erase(cs_or_pipe.find(id));
            }
            Console_func::return_to_menu();
            break;
        }
        case '0': {
            Console_func::Clear_console();
            Console_func::Menu_out();
            break;
        }
        default: {
            break;
        }
        }
    }

    void Choose_Pipe_filter(const std::unordered_map<int, Pipe>& pipes, std::vector<int>& id_vec);

    void Choose_CS_filter(const std::unordered_map<int, CS>& cs, std::vector<int>& id_vec);

    void switch_CS_workshops(GTS& Gts, std::vector<int>& id_vec);
}

#endif //LAB_FILTER_H

