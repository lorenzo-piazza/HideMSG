#include "hidemsg.h"

int main(int argc, char* argv[]) {
    InputParser inputParser(argc, argv);
    Options opt = inputParser.parseOptions();

    if (opt.doEncode) {
        //TODO: do encoding
    }
    else if (opt.doDecode) {
        //TODO implement decoding
    }

    return EXIT_SUCCESS;
}
