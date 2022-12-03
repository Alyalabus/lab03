#ifndef LAB_GTS_H
#define LAB_GTS_H
#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include <vector>

class GTS {
public:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, Pipe> Used_pipes;
    std::unordered_map<int, CS> compressors;
    std::unordered_map<int, CS> Used_compressors;
    std::vector<int> sort_id_CS;
    void add_link(const int& cs_out, const int& cs_in, const int& pipe_rib);
    friend std::ostream& operator << (std::ostream& out, const GTS& link);
    void disclink(int pipe_rib_id);
    void topsort(std::unordered_map<int, Pipe> Used_pipes_copy, std::unordered_map<int, CS> Used_compressors_copy, int degree = 0);
    void print_sort_cs_id();
};


#endif //LAB_GTS_H

