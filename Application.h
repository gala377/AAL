//
// Created by igor on 18.01.18.
//

#ifndef AAL_APPLICATION_H
#define AAL_APPLICATION_H

#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

class Application {
public:
    using Result=std::pair<unsigned long long int, unsigned long long int>;
    using Performance=std::array<std::vector<Result>, 3>;

    class InsufficientNumberOfParameters : public std::exception {};
    class CommandLineReader {
    public:
        CommandLineReader(int argc, char **argv);


        template <typename T>
        std::istream& operator>>(T& out) {
            if(!assert_next_parameter()) {
                //print_usage();
                throw InsufficientNumberOfParameters();
            }
            T test;
            in >> test;
            //std::cout << "Reading: " << test << "\n";
            out = test;
            //std::cout << "Read\n";
            return in;
        }


        void print_usage();
    private:
        std::stringstream in;
        int num_of_parameters;

        bool assert_next_parameter();
    };
    enum Flags {none, m1, m2, m3, n, k, min_p, max_p, min_free_space,
                max_free_space, shuffle_moves, gen_start,
                step, num_of_tests, instances};

    Application(int argc, char **argv);

    void start();
    void run_test_from_stream();
    void run_random();
    void run_test_case();
private:
    CommandLineReader reader;
    std::unordered_map<std::string, Flags> flags_map;

    void create_and_run_test(int start, int step, int num_of_steps, int instances);
    void print_table(Performance p, std::array<int, 3> unresolved);
    Result get_average(std::vector<Result> v);
    template <typename T>
    std::pair<int, unsigned long long int> time_it(T&& func);
};


#endif //AAL_APPLICATION_H
