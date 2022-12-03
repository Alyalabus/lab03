#include "Pipe.h"
#include "verification.h"
#include "consolef.h"
#include <iomanip>

using namespace std;

int Pipe::Max_ID = 0;

void Pipe::Add_pipe_attribute() {
    Console_func::Clear_console();
    id = ++Max_ID;
    std::cout << "Enter the name of pipe, which have length in range (1 - 10): ";
    verification::check_string(name, 10);
    std::cout << "Enter the diameter in millimeters in the range{114 - 1420}: ";
    verification::add_attributes(diameter, 110, 1420);
    std::cout << "Enter the length in meters in the range{10 - 100}: ";
    verification::add_attributes(length, 10, 100);
    std::cout << "in Repair or not in repair? (Push 'y'(not in repair) or 'n'(in repair) button): ";
    verification::true_false(repair_or_not);
    Console_func::Clear_console();
}


int Pipe::get_id() const {
    return id;
}

void Pipe::PIPE_Clear(std::unordered_map<int, Pipe>& pipes) {
    pipes.clear();
    Max_ID = 0;
}

std::ostream& operator << (std::ostream& out, const Pipe& pipe) {
    out << std::setw(8) << pipe.get_id() << std::setw(20)
        << pipe.name << std::setw(20)
        << pipe.diameter << std::setw(20)
        << pipe.length;
    if (!pipe.repair_or_not) {
        out << std::setw(20) << "not in repair" << std::endl;
    }
    else {
        out << std::setw(20) << "in repair" << std::endl;
    }
    return out;
}

std::ofstream& operator << (std::ofstream& f_out, const Pipe& pipe) {
    f_out << pipe.get_id() << std::endl << pipe.name << std::endl << pipe.diameter << std::endl
        << pipe.length << std::endl;
    f_out << pipe.repair_or_not << std::endl;
    return f_out;
}

std::ifstream& operator >> (std::ifstream& f_in, Pipe& pipe) {
    int x;
    f_in >> x >> std::ws;
    if (Pipe::Max_ID <= x) {
        Pipe::Max_ID = x;
    }
    pipe.id = x;
    getline(f_in, pipe.name);
    f_in >> pipe.length;
    f_in >> pipe.diameter;
    f_in >> pipe.repair_or_not;
    f_in >> std::ws;
    return f_in;
}
