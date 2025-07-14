#include "hidemsg.h"

int main(int argc, char* argv[]) {
    InputParser inputParser(argc, argv);
    Options opt = inputParser.parseOptions();

    if (opt.doEncode) {
        //TODO: do encoding
        //Encoding111 done, test by saving image on file and retrieving message
    }
    else if (opt.doDecode) {
        //TODO implement decoding
    }

    return EXIT_SUCCESS;
}
