#include "Filter.h"

bool Filter::filter_true_false(const Pipe& pipe, bool repair) {
    return repair == pipe.repair_or_not;
}

bool Filter::Filter_by_percentworkshops(const CS& cs, double left_border_percent) {
    double y = ((double)cs.count_ready_workshops / cs.count_workshops) * 100;
    if (y > left_border_percent && y < left_border_percent + 10) {
        return true;
    }
    else {
        return false;
    }
}

void Filter::switch_Pipe_true_false(GTS& Gts, std::vector<int>& id_vec) {
    if (!id_vec.empty()) {
        Console_func::Pipe_table();
        for (auto id : id_vec) {
            std::cout << Gts.pipes.at(id);
        }
        char menu_pointer2;
        Console_func::Edit_menu("pipes");
        Console_func::Choise_table_point(menu_pointer2);
        switch (menu_pointer2) {
        case '1': {
            bool repair;
            std::cout << "Choose which pipes you want in repair or not (if in repair push 'y', if not in repair push 'n': ";
            verification::true_false(repair);
            for (auto id : id_vec) {
                Gts.pipes[id].repair_or_not = repair;
            }
            Console_func::return_to_menu();
            break;
        }
        case '2': {
            bool repair;
            std::unordered_set<int> table_pos;
            std::cout << "Enter the serial number of the pipe in the table which you want to change "
                "if you enter the wrong number, an error will occur and you will need to re-enter: ";
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
                std::cout << "Enter the serial number of the pipe in the table: ";
            }
            std::cout << std::endl << "Choose which pipes you want in repair or not (if in repair push 'y', if not in repair push 'n': ";
            verification::true_false(repair);
            for (auto id : table_pos) {
                Gts.pipes[id].repair_or_not = repair;
            }
            Console_func::return_to_menu();
            break;
        }
        case '0': {
            break;
        }
        }
    }
}

void Filter::Choose_Pipe_filter(const std::unordered_map<int, Pipe>& pipes, std::vector<int>& id_vec) {
    Console_func::Filter_Pipe_menu();
    char menu_pointer2;
    Console_func::Choise_table_point(menu_pointer2);
    switch (menu_pointer2) {
    case '1': {
        Console_func::Clear_console();
        bool repair;
        std::cout
            << "Choose which pipes you want in repair or not (if in repair push 'y', if not in repair push 'n': ";
        verification::true_false(repair);
        Filter_id(pipes, filter_true_false, id_vec, repair);

        if (id_vec.empty()) {
            if (repair) {
                std::cout << "You dont have Pipe in repair";
            }
            else {
                std::cout << "You dont have Pipe not in repair";
            }
            std::cout << std::endl;
            Console_func::return_to_menu();
            break;
        }
        break;
    }
    case '2': {
        Console_func::Clear_console();
        std::string name;
        std::cout << "Enter Pipe name: ";
        verification::check_string(name, 10);
        Filter_id(pipes, Filter_by_name, id_vec, name);
        if (id_vec.empty()) {
            std::cout << "You dont have Pipe with such name" << std::endl;
            Console_func::return_to_menu();
        }
        break;
    }
    case '0': {
        break;
    }
    }
}

void Filter::Choose_CS_filter(const std::unordered_map<int, CS>& cs, std::vector<int>& id_vec) {
    Console_func::Filter_CS_menu();
    char menu_pointer2;
    Console_func::Choise_table_point(menu_pointer2);
    switch (menu_pointer2) {
    case '1': {
        Console_func::Clear_console();
        double percent;
        std::cout
            << "Enter the number of percent of ready workshops: ";
        verification::add_attributes(percent, 0, 100);
        Filter_id(cs, Filter_by_percentworkshops, id_vec, percent);
        if (id_vec.empty()) {
            std::cout << "You dont have compressors with such count workshops" << std::endl;
            Console_func::return_to_menu();
            break;
        }
        break;
    }
    case '2': {
        Console_func::Clear_console();
        std::string name;
        std::cout << "Enter Pipe name: ";
        verification::check_string(name, 10);
        Filter_id(cs, Filter_by_name, id_vec, name);
        if (id_vec.empty()) {
            std::cout << "You dont have Compressors with such name" << std::endl;
            Console_func::return_to_menu();
        }
        break;
    }
    case '0': {
        break;
    }
    }
}

void Filter::switch_CS_workshops(GTS& Gts, std::vector<int>& id_vec) {
    if (!id_vec.empty()) {
        Console_func::CS_table();
        for (auto id : id_vec) {
            std::cout << Gts.compressors.at(id);
        }
        char menu_pointer2;
        Console_func::Edit_menu("compressors");
        Console_func::Choise_table_point(menu_pointer2);
        switch (menu_pointer2) {
        case '1': {
            for (const auto& cs_id : id_vec) {
                Gts.compressors[cs_id].change_workshops();
            }
            Console_func::return_to_menu();
            break;
        }
        case '2': {
            std::unordered_set<int> table_pos;
            std::cout << "Enter the serial number of the pipe in the table which you want to change "
                "if you enter the wrong number, an error will occur and you will need to re-enter: ";
            while (true) {
                int x;
                verification::add_attributes(x, 0, id_vec.size());
                table_pos.insert(id_vec[x - 1]);
                std::cout << "if you want to continue press '1', otherwise press'0': ";
                char menu_pointer3;
                while (true) {
                    std::cin >> std::ws;
                    menu_pointer3 = std::cin.get();
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
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
                std::cout << "Enter the serial number of the pipe in the table: ";
            }
            for (const auto& cs_id : table_pos) {
                Gts.compressors[cs_id].change_workshops();
            }
            break;
        }
        default: {
            break;
        }
        }
    }
}
