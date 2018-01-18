//
// Created by igor on 18.01.18.
//

#include "Application.h"
#include <iostream>

Application::CommandLineReader::CommandLineReader(int argc, char **argv) :
    num_of_parameters(argc-1) {
    for (int i = 1; i < argc; ++i) {
        in << argv[i] << " ";
    }
}

bool Application::CommandLineReader::assert_next_parameter() {
    return --num_of_parameters >= 0;
}

void Application::CommandLineReader::print_usage() {
    std::cout << R"(
Usage:
    -m[1|2|3] - specifies mode
Modes:
    -m1: read test from stream, write output to stream.
        Example:
            -m1 << in.txt >> out.txt
    -m2: generate random test and solve it
    -m3: generate n random tests and solve them
         write stats.
    )";
}

Application::Application(int argc, char **argv) :
        reader(argc, argv) {
        flags_map["-m1"] = Application::Flags::m1;
        flags_map["-m2"] = Application::Flags::m2;
        flags_map["-m3"] = Application::Flags::m3;

}

void Application::start() {
    std::string mode;
    reader >> mode;
    switch(flags_map[mode]) {
        case Flags::m1:
            break;
        case Flags::m2:
            break;
        case Flags::m3:
            break;
        default:
            reader.print_usage();
            break;
    }
}
