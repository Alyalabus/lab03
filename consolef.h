#ifndef LAB_CONSOLEF_H
#define LAB_CONSOLEF_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "GTS.h"

namespace Console_func {
    void Menu_out();
    void Clear_console();
    void return_to_menu();
    void Out_to_File(GTS& Gts, std::string& File_name);
    void In_from_file(GTS& Gts, std::string& File_name);
    void Pipe_table();
    void CS_table();
    void Edit_menu(const std::string& str);
    void Choise_table_point(char& pointer);
    void Delete_menu();
    void Filter_Pipe_menu();
    void Filter_CS_menu();
    void Graph_table();
}

#endif //LAB_CONSOLEF_H
