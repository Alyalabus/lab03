#include "Pipe.h"
#include "CS.h"
#include "consolef.h"
#include "verification.h"
#include <vector>
#include "Filter.h"
#include "GTS.h"

using namespace std;



int main() {
    GTS Gts;
    char menu_pointer;
    while (true) {
        Console_func::Menu_out();
        Console_func::Choise_table_point(menu_pointer);
        switch (menu_pointer) {
        case '1': {
            Pipe new_pipe;
            new_pipe.Add_pipe_attribute();
            Gts.pipes.insert({ new_pipe.get_id(), new_pipe });
            break;
        }
        case '2': {
            CS new_cs;
            new_cs.Add_CS_attribute();
            Gts.compressors.insert({ new_cs.get_id(), new_cs });
            Console_func::Clear_console();
            Console_func::Menu_out();
            break;
        }
        case '3': {
            Console_func::Clear_console();
            if (!Gts.pipes.empty()) {
                Console_func::Pipe_table();
                for (auto& item : Gts.pipes) {
                    cout << item.second;
                }
                cout << endl;
            }
            if (!Gts.compressors.empty()) {
                Console_func::CS_table();
                for (auto& item : Gts.compressors) {
                    cout << item.second;
                }
                cout << endl;
            }
            if (Gts.pipes.empty() && Gts.compressors.empty()) {
                Console_func::Clear_console();
                cout << "You push wrong point in menu because you don't have pipe or CS\n\n";
                Console_func::Menu_out();
                break;
            }
            Console_func::return_to_menu();
            break;
        }
        case '4': {
            Console_func::Clear_console();
            if (Gts.pipes.empty()) {
                cout << "You push wrong point in menu because you don't have pipe\n\n";
                Console_func::Menu_out();
                break;
            }
            vector<int> vec_id;
            Filter::Choose_Pipe_filter(Gts.pipes, vec_id);
            Filter::switch_Pipe_true_false(Gts, vec_id);
            break;
        }
        case '5': {
            Console_func::Clear_console();
            if (Gts.compressors.empty()) {
                cout << "You push wrong point in menu because you don't have CS\n\n";
                Console_func::Menu_out();
                break;
            }
            vector<int> vec_id;
            Filter::Choose_CS_filter(Gts.compressors, vec_id);
            Filter::switch_CS_workshops(Gts, vec_id);
            break;
        }
        case '6': {
            if (Gts.compressors.empty() && Gts.pipes.empty()) {
                Console_func::Clear_console();
                cout << "You push wrong point in menu because you don't have pipe or CS\n\n";
                Console_func::Menu_out();
                break;
            }
            string file_name;
            Console_func::Clear_console();
            cout << "Enter the file name: ";
            getline(cin, file_name);
            Console_func::Out_to_File(Gts, file_name);
            break;
        }
        case '7': {
            Console_func::Clear_console();
            string file_name;
            cout << "Enter the file name: ";
            getline(cin, file_name);
            Console_func::In_from_file(Gts, file_name);
            break;
        }
        case '8': {
            Console_func::Clear_console();
            if (Gts.pipes.empty()) {
                cout << "You push wrong point in menu because you don't have pipe\n\n";
                Console_func::Menu_out();
                break;
            }
            vector<int> vec_id;
            Filter::Choose_Pipe_filter(Gts.pipes, vec_id);
            for (auto id = vec_id.begin(); id != vec_id.end();) {
                if (Gts.Used_pipes.find(*id) != Gts.Used_pipes.end()) {
                    id = vec_id.erase(find(vec_id.begin(), vec_id.end(), *id));
                    continue;
                }
                ++id;
                std::cout << Gts.pipes.at(*id);
            }
            if (!vec_id.empty()) {
                Console_func::Pipe_table();
                Filter::Delete_CS_OR_PIPE(Gts.pipes, vec_id);
            }
            else {
                cout << "You can't delete Pipes because they are all in GTS" << endl;
            }
            break;
        }
        case '9': {
            Console_func::Clear_console();
            if (Gts.compressors.empty()) {
                cout << "You push wrong point in menu because you don't have compressors\n\n";
                Console_func::Menu_out();
                break;
            }
            vector<int> vec_id;
            Filter::Choose_CS_filter(Gts.compressors, vec_id);
            for (auto id = vec_id.begin(); id != vec_id.end();) {
                if (Gts.Used_compressors.find(*id) != Gts.Used_compressors.end()) {
                    id = vec_id.erase(find(vec_id.begin(), vec_id.end(), *id));
                    continue;
                }
                ++id;
                std::cout << Gts.pipes.at(*id);
            }
            if (!vec_id.empty()) {
                Console_func::CS_table();
                Filter::Delete_CS_OR_PIPE(Gts.compressors, vec_id);
            }
            else {
                cout << "You can't delete Pipes because they are all in GTS" << endl;
            }
            break;
        }
        case '0': {
            Console_func::Clear_console();
            return 0;
        }
        case 'a': {
            if (Gts.compressors.empty() || Gts.compressors.size() < 2 || Gts.pipes.empty() || Gts.Used_pipes.size() == Gts.pipes.size()) {
                Console_func::Clear_console();
                cout << "You can't do a link" << endl;
                Console_func::Menu_out();
                break;
            }

            vector<int> vec_cs_id;
            Console_func::CS_table();
            for (const auto& item : Gts.compressors) {
                if (item.second.get_degree_out() + item.second.get_degree_in() != item.second.count_ready_workshops) {
                    cout << item.second;
                    vec_cs_id.push_back(item.first);
                }
            }
            if (vec_cs_id.empty() || vec_cs_id.size() == 1) {
                cout << "You dont have 2 vertex" << endl;
                Console_func::return_to_menu();
                break;
            }
            cout << endl;
            int cs_out_id;
            bool ch = true;
            cout << "Choose CS_out from table by id: ";
            while (ch) {
                ch = verification::choose_id(vec_cs_id, cs_out_id);
            }
            int cs_in_id;
            ch = true;
            cout << "Choose CS_in from table by id: ";
            while (ch) {
                ch = verification::choose_id(vec_cs_id, cs_in_id);
            }
            Console_func::Clear_console();
            vector<int> vec_pipe_id;
            Console_func::Pipe_table();
            for (const auto& item : Gts.pipes) {
                if (Gts.Used_pipes.find(item.first) == Gts.Used_pipes.end()) {
                    vec_pipe_id.push_back(item.first);
                    cout << item.second;
                }
            }
            cout << endl;
            if (!vec_pipe_id.empty()) {
                int pipe_rib_id;
                ch = true;
                cout << "Choose Pipe_rib from table by id: ";
                while (ch) {
                    ch = verification::choose_id(vec_pipe_id, pipe_rib_id);
                }
                Gts.add_link(cs_out_id, cs_in_id, pipe_rib_id);
            }
            Console_func::return_to_menu();
            break;
        }
        case 'b': {
            if (Gts.Used_pipes.empty()) {
                Console_func::Clear_console();
                cout << "You push wrong point in menu because you don't have any link \n\n";
                Console_func::Menu_out();
                break;
            }
            Console_func::Graph_table();
            cout << Gts;
            Console_func::return_to_menu();
            break;
        }
        case 'c': {
            if (Gts.Used_pipes.empty()) {
                Console_func::Clear_console();
                cout << "You push wrong point in menu because you don't have any link \n\n";
                Console_func::Menu_out();
                break;
            }
            Console_func::Graph_table();
            cout << Gts;
            cout << "Choose which link do you want delete by pipe id: ";
            vector<int> vec_pipe_id;
            for (const auto& item : Gts.Used_pipes) {
                vec_pipe_id.push_back(item.first);
            }
            if (!vec_pipe_id.empty()) {
                int pipe_rib_id;
                bool ch = true;
                while (ch) {
                    ch = verification::choose_id(vec_pipe_id, pipe_rib_id);
                }
                Gts.disclink(pipe_rib_id);
            }
            break;
        }
        case 'd': {
            Console_func::Clear_console();
            if (Gts.Used_pipes.empty()) {
                Console_func::Clear_console();
                cout << "You push wrong point in menu because you don't have any link \n\n";
                Console_func::Menu_out();
                break;
            }
            Gts.print_sort_cs_id();
            Console_func::return_to_menu();
            break;
        }
        default: {
            break;
        }
        }
        Console_func::Clear_console();
    }
}