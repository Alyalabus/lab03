#include "GTS.h"
#include <iomanip>

void GTS::add_link(const int& cs_out, const int& cs_in, const int& pipe_rib) {
    pipes[pipe_rib].cs_out = cs_out;
    pipes[pipe_rib].cs_in = cs_in;
    Used_pipes.insert({ pipe_rib, pipes[pipe_rib] });
    compressors[cs_out].increase_degree_out();
    compressors[cs_in].increase_degree_in();
    Used_compressors[cs_out] = compressors[cs_out];
    Used_compressors[cs_in] = compressors[cs_in];

}

std::ostream& operator << (std::ostream& out, const GTS& link) {
    for (const auto& item : link.Used_pipes) {
        out << std::setw(6) << item.second.cs_out << std::setw(31)
            << item.second.cs_in << std::setw(27) << item.first << std::endl;
    }
    return out;
}

void GTS::disclink(int pipe_rib_id) {
    compressors[pipes[pipe_rib_id].cs_out].decrease_degree_out();
    Used_compressors[pipes[pipe_rib_id].cs_out].decrease_degree_out();
    compressors[pipes[pipe_rib_id].cs_in].decrease_degree_in();
    Used_compressors[pipes[pipe_rib_id].cs_in].decrease_degree_in();
    if (compressors[pipes[pipe_rib_id].cs_out].get_degree_in() == 0 && compressors[pipes[pipe_rib_id].cs_out].get_degree_out() == 0) {
        Used_compressors.erase(Used_compressors.find(pipes[pipe_rib_id].cs_out));
    }
    if (compressors[pipes[pipe_rib_id].cs_in].get_degree_in() == 0 && compressors[pipes[pipe_rib_id].cs_in].get_degree_out() == 0) {
        Used_compressors.erase(Used_compressors.find(pipes[pipe_rib_id].cs_in));
    }
    pipes[pipe_rib_id].cs_out = 0;
    pipes[pipe_rib_id].cs_in = 0;
    Used_pipes.erase(Used_pipes.find(pipe_rib_id));
}

void GTS::topsort(std::unordered_map<int, Pipe> Used_pipes_copy, std::unordered_map<int, CS> Used_compressors_copy, int degree) {
    std::vector<int> idDelPipe;
    std::vector<int> idDelCS;
    int counter = 0;
    for (auto& item : Used_compressors_copy) {
        if (item.second.get_degree_in() == degree) {
            ++counter;
            idDelCS.push_back(item.first);
            sort_id_CS.push_back(item.first);
            for (auto& item1 : Used_pipes_copy) {
                if (item1.second.cs_out == item.first) {
                    idDelPipe.push_back(item1.first);
                }
            }
        }
    }
    for (const auto& id : idDelCS) {
        Used_compressors_copy.erase(id);
    }
    for (const auto& id : idDelPipe) {
        Used_compressors_copy.find(Used_pipes_copy.find(id)->second.cs_in)->second.decrease_degree_in();
        Used_pipes_copy.erase(id);
    }
    idDelCS.clear();
    idDelPipe.clear();
    if (counter == 0) {
        for (const auto& vert : Used_compressors_copy) {
            sort_id_CS.push_back(vert.first);
        }
        std::cout << "you have cycle" << std::endl;
        return;
    }
    if (Used_pipes_copy.empty() && Used_compressors_copy.empty()) {
        return;
    }
    topsort(Used_pipes_copy, Used_compressors_copy, 0);
}

void GTS::print_sort_cs_id() {
    sort_id_CS.clear();
    topsort(Used_pipes, Used_compressors, 0);
    for (const auto& id : sort_id_CS) {
        std::cout << id << ' ';
    }
    std::cout << std::endl;
}
