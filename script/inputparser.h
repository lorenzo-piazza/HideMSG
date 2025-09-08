#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional> 

struct Options {
    bool doEncode;
    bool doDecode;
    int mode;
    std::string path;
    std::optional<std::string> key;
    std::optional<std::string> message;
};

class InputParser {
    public:
        InputParser(int &argc, char *argv[]);
        Options parseOptions();
    private:
        const std::string& getCmdOption(const std::string &option) const;
        bool cmdOptionExists(const std::string &option) const;
        std::vector <std::string> tokens;
        int argc;
        char** argv;

        [[noreturn]] 
        void exitWithError(const std::string& msg);
};
#endif
