#include "consolef.h"
#include <iomanip>

void Console_func::Menu_out() {
    std::cout << "1. Add pipe\n"
        "2. Add CS\n"
        "3. Viewing all objects\n"
        "4. Edit pipe\n"
        "5. Edit cs\n"
        "6. Save\n"
        "7. Download\n"
        "8. Delete pipe\n"
        "9. Delete CS\n"
        "a. Adding a link\n"
        "b. Output of links\n"
        "c. Delete links\n"
        "d. Topologicheskaya sortirovka\n"
        "0. Exit\n";
}

void Console_func::Pipe_table() {
    std::cout << "Pipe info:" << std::endl;
    std::cout << "Pipe id:" << std::setw(20) << "Pipe's name:" << std::setw(20) << "Pipe diameter:" <<
        std::setw(20) << "Pipe length:" << std::setw(20) << "repair or not:" << std::endl;
}
void Console_func::CS_table() {
    std::cout << "CS info:" << std::endl;
    std::cout << "CS id:" << std::setw(17) << "Cs name:" << std::setw(27) << "CS count workshops:" <<
        std::setw(32) << "CS count ready workshops:" << std::setw(20) << "CS efficiency:" << std::endl;
}

void Console_func::Edit_menu(const std::string& str) {
    std::cout << "1. " << "Edit all " << str << " in table" << std::endl
        << "2. " << "Edit certain " << str << std::endl
        << "0. " << "Exit to menu press" << std::endl;
}

void Console_func::Delete_menu() {
    std::cout << "1. " << "Delete all pipes in table" << std::endl
        << "2. " << "Delete certain pipes" << std::endl
        << "0. " << "Exit to menu press" << std::endl;
}

void Console_func::Filter_Pipe_menu() {
    std::cout << "1. " << "Filter by repair" << std::endl
        << "2. " << "Filter by name" << std::endl
        << "0. " << "Exit to menu press" << std::endl;
}

void Console_func::Filter_CS_menu() {
    std::cout << "1. " << "Filter by percent workshops" << std::endl
        << "2. " << "Filter by name" << std::endl
        << "0. " << "Exit to menu press" << std::endl;
}


void Console_func::Clear_console() {
    std::cout << std::string(20, '\n');
}

void Console_func::return_to_menu() {
    std::cout << "for return to menu push '1' button: ";
    std::cin >> std::ws;
    while (true) {
        if (std::cin.get() == '1') {
            break;
        }
        else {
            Clear_console();
            std::cout << "for return to menu push '1' button, you push wrong button: ";
        }
    }
}

void Console_func::Out_to_File(GTS& Gts, std::string& File_name) {
    std::ofstream out;
    out.open("../data_file/" + File_name);
    if (!out.is_open()) {
        std::cout << "File didn't find ";
        Console_func::return_to_menu();
        return;
    }
    if (!Gts.pipes.empty()) {
        out << "Pipe" << std::endl << Gts.pipes.size() << std::endl;
        for (const auto& [id, item] : Gts.pipes) {
            out << item;
        }
    }

    if (!Gts.compressors.empty()) {
        out << "CS" << std::endl << Gts.compressors.size() << std::endl;
        for (const auto& item : Gts.compressors) {
            out << item.second;
        }
    }
    if (!Gts.Used_pipes.empty()) {
        out << "Links" << std::endl << Gts.Used_pipes.size() << std::endl;
        for (const auto& item : Gts.Used_pipes) {
            out << item.second.cs_out << std::endl;
            out << item.second.cs_in << std::endl;
            out << item.first << std::endl;
        }
    }
    std::cout << "Data is upload to file" << std::endl;
    out.close();
    Console_func::return_to_menu();
    Console_func::Clear_console();
    Console_func::Menu_out();
}

void Console_func::Choise_table_point(char& pointer) {
    std::cin >> std::ws;
    pointer = std::cin.get();
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void Console_func::In_from_file(GTS& Gts, std::string& File_name) {
    std::ifstream in("/Users/Мой пк/Desktop/3 семестр/Папилина/333/laba3/data_file/" + File_name);
    if (!in.is_open()) {
        std::cout << "File didn't find" << std::endl;
        Console_func::return_to_menu();
        return;
    }
    else if (in.eof()) {
        std::cout << "File is empty" << std::endl;
        Console_func::return_to_menu();
        return;
    }
    std::string check;
    in >> check;
    if (check == "Pipe") {
        Pipe::PIPE_Clear(Gts.pipes);
        int count_pipe;
        in >> count_pipe;
        for (int i = 0; i < count_pipe; ++i) {
            Pipe new_pipe;
            in >> new_pipe;
            Gts.pipes.insert({ new_pipe.get_id(), new_pipe });
        }
        if (!in.eof()) {
            in >> check;
        }
    }
    if (check == "CS") {
        CS::CS_Clear(Gts.compressors);
        int count_cs;
        in >> count_cs;
        for (int i = 0; i < count_cs; ++i) {
            CS new_cs;
            in >> new_cs;
            Gts.compressors.insert({ new_cs.get_id(), new_cs });
        }
        if (!in.eof()) {
            in >> check;
        }
    }
    if (check == "Links") {
        int count_links;
        in >> count_links;
        for (int i = 0; i < count_links; ++i) {
            int id_cs_in, id_cs_out, id_pipe_rib;
            in >> id_cs_out;
            in >> id_cs_in;
            in >> id_pipe_rib;
            Gts.add_link(id_cs_out, id_cs_in, id_pipe_rib);
        }
    }
    std::cout << "You download data from file" << std::endl;
    in.close();
    Console_func::return_to_menu();
}

void Console_func::Graph_table() {
    std::cout << "Links info:" << std::endl;
    std::cout << "CS_out id:" << std::setw(30) << "Cs_in id:" << std::setw(30) << "Pipe_rib_id:" <<
        std::setw(30) << std::endl;
}

