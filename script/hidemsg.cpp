#include "hidemsg.h"

int main(int argc, char* argv[]) {
    InputParser inputParser(argc, argv);
    Options opt = inputParser.parseOptions();

    //TODO do main
    if (opt.doEncode) {

    }
    else if (opt.doDecode) {
        
    }

    return EXIT_SUCCESS;
}
