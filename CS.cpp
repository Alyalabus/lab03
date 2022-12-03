#include "CS.h"
#include <iostream>
#include "verification.h"
#include "consolef.h"
#include <iomanip>

int CS::Max_ID = 0;

void CS::Add_CS_attribute() {
    Console_func::Clear_console();
    id = ++Max_ID;
    std::cout << "Enter the name of cs, which have length in range (1 - 10):  ";
    verification::check_string(name,10);
    std::cout << "Enter the count of workshops in range (1 - 20): ";
    verification::add_attributes(count_workshops, 1, 20);
    std::cout << "Enter the count of ready's workshops in range (0 - n) (n - is how many workshops you have): ";
    verification::add_attributes(count_ready_workshops, 0, count_workshops);
    std::cout << "Enter the efficiency in range (0 - 100%): ";
    verification::add_attributes(efficiency, 0, 100);
    Console_func::Clear_console();
}


int CS::get_id() const {
    return id;
}

int CS::get_degree_out() const {
    return degree_out;
}

int CS::get_degree_in() const {
    return degree_in;
}

void CS::decrease_degree_out() {
    degree_out -= 1;
}

void CS::decrease_degree_in() {
    degree_in -= 1;
}

void CS::increase_degree_in() {
    degree_in += 1;
}

void CS::increase_degree_out() {
    degree_out += 1;
}


void CS::change_workshops() {
    std::cout << "Your CS with id " << id << " has " << count_ready_workshops << " ready workshops" << std::endl;
    std::cout << "Enter the count of ready's workshops in range (0 - n) (n - is how many workshops you have):";
    verification::add_attributes(count_ready_workshops, 0, count_workshops);
}

void CS::CS_Clear(std::unordered_map<int, CS>& compressors) {
    compressors.clear();
    Max_ID = 0;
}

std::ostream& operator << (std::ostream& out, const CS& cs) {
    out << std::setw(6) << cs.get_id() << std::setw(17)
        << cs.name << std::setw(27)
        << cs.count_workshops << std::setw(32)
        << cs.count_ready_workshops << std::setw(20)
        << cs.efficiency << std::endl;
    return out;
}

std::ofstream& operator << (std::ofstream& f_out, const CS& cs) {
    f_out << cs.get_id() << std::endl << cs.name << std::endl << cs.count_workshops
        << std::endl << cs.count_ready_workshops << std::endl
        << cs.efficiency << std::endl;
    return f_out;
}

std::ifstream& operator >> (std::ifstream& f_in, CS& cs) {
    int x;
    f_in >> x >> std::ws;
    if (CS::Max_ID <= x) {
        CS::Max_ID = x;
    }
    cs.id = x;
    getline(f_in, cs.name);
    f_in >> cs.count_workshops;
    f_in >> cs.count_ready_workshops;
    f_in >> cs.efficiency;
    f_in >> std::ws;
    return f_in;
}

