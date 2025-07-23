#include "inputparser.h"

[[noreturn]] 
void InputParser::exitWithError(const std::string& msg) {
    std::cerr << "Error: " << msg << std::endl;
    std::exit(EXIT_FAILURE);
}

Options InputParser::parseOptions() {
    Options opt;

    // Operazione richiesta
    opt.doEncode = cmdOptionExists("--encode");
    opt.doDecode = cmdOptionExists("--decode");
    if (!opt.doEncode && !opt.doDecode) {
        exitWithError("--encode or --decode required");
    }

    // Mode (obbligatorio)
    if (!cmdOptionExists("--mode")) {
        exitWithError("missing --mode");
    }
    try {
        opt.mode = std::stoi(getCmdOption("--mode"));
        if(opt.mode != 111 && opt.mode != 224)
            exitWithError("Not valid mode value");
    } catch (const std::exception&) {
        exitWithError("Not valid mode value");
    }

    // Path (obbligatorio)
    if (!cmdOptionExists("--path")) {
        exitWithError("Missing --path");
    }
    opt.path = getCmdOption("--path");

    // Key (opzionale)
    if (cmdOptionExists("--key")) {
        opt.key = getCmdOption("--key");
    }

    // Message (solo per encode)
    if (opt.doEncode) {
        // L'indice del messaggio dipende dalla presenza di --key
        int expectedArgs = cmdOptionExists("--key") ? 8 : 6;
        if (argc <= expectedArgs) {
            exitWithError("Message argument missing");
        }
        opt.message = argv[expectedArgs];
    }

    return opt;
}


InputParser::InputParser (int &argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
    for (int i=1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
}

const std::string& InputParser::getCmdOption(const std::string &option) const{
    std::vector<std::string>::const_iterator itr;
    itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::cmdOptionExists(const std::string &option) const{
    return std::find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
}
    

