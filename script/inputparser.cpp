#include "inputparser.h"

[[noreturn]] 
void InputParser::exitWithError(const std::string& msg) {
    std::cerr << "Errore: " << msg << std::endl;
    std::exit(EXIT_FAILURE);
}

Options InputParser::parseOptions() {
    Options opt;

    // Operazione richiesta
    opt.doEncode = cmdOptionExists("--encode");
    opt.doDecode = cmdOptionExists("--decode");
    if (!opt.doEncode && !opt.doDecode) {
        exitWithError("specificare almeno --encode o --decode");
    }

    // Mode (obbligatorio)
    if (!cmdOptionExists("--mode")) {
        exitWithError("manca l'argomento --mode");
    }
    try {
        opt.mode = std::stoi(getCmdOption("--mode"));
    } catch (const std::exception&) {
        exitWithError("valore non valido per --mode");
    }

    // Path (obbligatorio)
    if (!cmdOptionExists("--path")) {
        exitWithError("manca l'argomento --path");
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
            exitWithError("manca il messaggio da codificare");
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
    

