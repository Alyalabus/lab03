#ifndef LAB_CS_H
#define LAB_CS_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class CS {
private:
    int id;
    int degree_out, degree_in;
public:
    static int Max_ID;
    std::string name;
    int count_workshops;
    int count_ready_workshops;
    double efficiency;
    void Add_CS_attribute();
    int get_id() const;
    int get_degree_out() const;
    int get_degree_in() const;
    void decrease_degree_out();
    void decrease_degree_in();
    void increase_degree_out();
    void increase_degree_in();
    void change_workshops();
    static void CS_Clear(std::unordered_map<int, CS>& compressors);
    friend std::ostream& operator << (std::ostream& out, const CS& cs);
    friend std::ofstream& operator << (std::ofstream& f_out, const CS& cs);
    friend std::ifstream& operator >> (std::ifstream& f_in, CS& cs);
};


#endif //LAB_CS_H

