#include "hidemsg.h"

int main(int argc, char* argv[]) {
    InputParser inputParser(argc, argv);
    Options opt = inputParser.parseOptions();

    if (opt.doEncode) {
        // Qui puoi richiamare la tua funzione di encoding:
        // encode(opt.mode, opt.path, opt.key, *opt.message);
        std::cout << "Encoding del messaggio: " << *opt.message << std::endl;
    }
    else if (opt.doDecode) {
        // Qui puoi richiamare la tua funzione di decoding:
        // decode(opt.mode, opt.path, opt.key);
        std::cout << "Decoding del file in: " << opt.path << std::endl;
    }

    return EXIT_SUCCESS;
}
