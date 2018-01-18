//
// Created by igor on 18.01.18.
//

#include "Application.h"
#include <iostream>
#include <chrono>
#include "generator.h"
#include "Naive.h"
#include "BFS.h"
#include "AStar.h"
#include <functional>

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
        flags_map["-n"] = Application::Flags::n;
        flags_map["-k"] = Application::Flags::k;
        flags_map["--min-p"] = Application::Flags::min_p;
        flags_map["--max-p"] = Application::Flags::max_p;
        flags_map["--min-free-space"] = Application::Flags::min_free_space;
        flags_map["--max-free-space"] = Application::Flags::max_free_space;
        flags_map["--shuffle-moves"] = Application::Flags::shuffle_moves;
        flags_map["-gs"] = Application::Flags::gen_start;
        flags_map["-s"] = Application::Flags::step;
        flags_map["-t"] = Application::Flags::num_of_tests;
        flags_map["-r"] = Application::Flags::instances;


}

void Application::start() {
    std::string mode;
    try {
        reader >> mode;
    } catch (InsufficientNumberOfParameters& e) {
        reader.print_usage();
        return;
    }
    switch(flags_map[mode]) {
        case Flags::m1:
            run_test_from_stream();
        case Flags::m2:
            run_random();
        case Flags::m3:
            break;
        default:
            reader.print_usage();
            break;
    }
}

void Application::run_test_from_stream()    {
    generator::Test t;
    std::cin >> t;

    auto fin  = time_it(std::bind(&algorithm::Naive::run, algorithm::Naive(t)));
    std::cout << "Naive Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
    fin = time_it(std::bind(&algorithm::AStar::run, algorithm::AStar(t)));
    std::cout << "AStar Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
    fin = time_it(std::bind(&algorithm::BFS::run, algorithm::BFS(t)));
    std::cout << "BFS Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
}

void Application::run_random() {
    int n=10, k=10, min_p=3, max_p=10;
    int min_free_space=1, max_free_space=4, shuffle_moves=100;
    const int num_of_parameters = 7;
    try {
        for(int i = 0; i < num_of_parameters; ++i) {
            std::string flag;
            int value;
            reader >> flag;
            reader >> value;
            //std::cout << "reading: " << flag << "=" << value <<"\n";
            switch(flags_map[flag]) {
                case Flags::n:
                    n = value;
                    break;
                case Flags::k:
                    k = value;
                    break;
                case Flags::min_p:
                    min_p = value;
                    break;
                case Flags::max_p:
                    max_p = value;
                    break;
                case Flags::min_free_space:
                    min_free_space = value;
                    break;
                case Flags::max_free_space:
                    max_free_space = value;
                    break;
                case Flags::shuffle_moves:
                    shuffle_moves = value;
                    break;
                default:
                    std::cout << flag << "=" << value << " " << ":" << flags_map[flag] << "\n";
                    reader.print_usage();
                    return;
            }
        }
    }
    catch (InsufficientNumberOfParameters&) { }
    generator::Test t = generator::generate_test(n,
                                                 k,
                                                 min_p,
                                                 max_p,
                                                 min_free_space,
                                                 max_free_space,
                                                 shuffle_moves);

    std::cout << "TEST" << "\n" << t;

    auto fin  = time_it(std::bind(&algorithm::Naive::run, algorithm::Naive(t)));
    std::cout << "Naive Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
    fin = time_it(std::bind(&algorithm::AStar::run, algorithm::AStar(t)));
    std::cout << "AStar Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
    fin = time_it(std::bind(&algorithm::BFS::run, algorithm::BFS(t)));
    std::cout << "BFS Resolved in: " << fin.first << "\n";
    std::cout << "Duration: " << fin.second << "miliseconds\n";
}

void Application::run_test_case() {
    int start=1, step=1, num_of_tests=5, instances=5;
    const int num_of_parameters = 4;
    try {
        for(int i = 0; i < num_of_parameters; ++i) {
            std::string flag;
            int value;
            reader >> flag;
            reader >> value;
            switch(flags_map[flag]) {
                case Flags::gen_start:
                    start = value;
                    break;
                case Flags::step:
                    step = value;
                    break;
                case Flags::num_of_tests:
                    num_of_tests = value;
                    break;
                case Flags ::instances:
                    instances = value;
                    break;
                default:
                    reader.print_usage();
                    break;
            }
        }
    } catch(InsufficientNumberOfParameters& e) {}
    create_and_run_test(start, step, num_of_tests, instances);

}

template<typename T>
std::pair<auto, unsigned long long int> Application::time_it(T &&func) -> decltype(func()){
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now() ;

    auto res = func();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() ;

    typedef std::chrono::duration<int,std::milli> millisecs_t ;
    millisecs_t duration( std::chrono::duration_cast<millisecs_t>(end-start) ) ;

    return std::make_pair(res, duration.count());
}

void Application::create_and_run_test(int start, int step, int num_of_steps, int instances) {
    Performance performances;
    std::array<int, 3> unresolved = {0, 0, 0};
    for (int i = 0; i < num_of_steps; ++i) {
        for(int j = 0; j < instances; ++j) {
            generator::Test t = generator::generate_test(start + step * i,
                                                         start + step * i,
                                                         3,
                                                         10,
                                                         1,
                                                         4,
                                                         100);
            auto fin = time_it(std::bind(&algorithm::Naive::run, algorithm::Naive(t)));
            if (fin == -1) {
                unresolved[0] += 1;
            } else {
                performances[0].push_back(fin);
            }
            fin = time_it(std::bind(&algorithm::AStar::run, algorithm::AStar(t)));
            if (fin == -1) {
                unresolved[1] += 1;
            } else {
                performances[1].push_back(fin);
            }
            fin = time_it(std::bind(&algorithm::BFS::run, algorithm::BFS(t)));
            if (fin == -1) {
                unresolved[2] += 1;
            } else {
                performances[2].push_back(fin);
            }
        }
    }
    print_table(performances, unresolved);
}

void Application::print_table(Application::Performance p, std::array<int, 3> unresolved) {
    for(int i = 0; i < 3; ++i) {
        switch(i) {
            case 0:
            std::cout << "NAIVE:\t";
                break;
            case 1:
            std::cout << "A*:\t";
                break;
            case 2:
            std::cout << "BFS:\t";
                break;
        }


    }
}

Application::Result Application::get_average(std::vector<Application::Result> v) {
    Result average;

}


