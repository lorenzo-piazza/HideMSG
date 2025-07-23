#include "hidemsg.h"

Encoder* create_encoder(const Options& opt) {
    if (opt.mode == 111) {
        return opt.key.has_value() ? new Encoder111(opt.path, opt.key.value())
                                  : new Encoder111(opt.path);
    } else {
        return opt.key.has_value() ? new Encoder422(opt.path, opt.key.value())
                                  : new Encoder422(opt.path);
    }
}

int main(int argc, char* argv[]) {
    InputParser inputParser(argc, argv);
    Options opt = inputParser.parseOptions();
    Encoder* e = create_encoder(opt);
    try {
        if (opt.doEncode) {
            e->encode_and_save(opt.message.value());
        }
        else if (opt.doDecode) {
            std::cout << e->decode() << std::endl;
        }
    }
    catch(...) {
        delete e;
        e = nullptr;
    }
    delete e;
    e = nullptr;
    return EXIT_SUCCESS;
}
