//
// Created by igor on 18.01.18.
//

#ifndef AAL_APPLICATION_H
#define AAL_APPLICATION_H

#include <sstream>
#include <iostream>
#include <unordered_map>

class Application {
public:
    class InsufficientNumberOfParameters : public std::exception {};
    class CommandLineReader {
    public:
        CommandLineReader(int argc, char **argv);


        template <typename T>
        std::istream& operator>>(T& out) {
            if(!assert_next_parameter()) {
                print_usage();
                throw InsufficientNumberOfParameters();
            }
            in >> out;
        }

        void print_usage();
    private:
        std::stringstream in;
        int num_of_parameters;

        bool assert_next_parameter();
    };
    enum Flags {none, m1, m2, m3};

    Application(int argc, char **argv);

    void start();
private:
    CommandLineReader reader;
    std::unordered_map<std::string, Flags> flags_map;
};


#endif //AAL_APPLICATION_H
