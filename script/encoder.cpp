#include "encoder.h"

Encoder::Encoder(const std::string &path) : Encoder(path, "") {}
Encoder::Encoder(const std::string &path, const std::string key) : _handler(path), _path(path), _aes(_key) {
    set_key(key);
}

void Encoder::set_key(const std::string &key) {
    if(!key.empty()) {
        _key = key;
    }
}

void Encoder::encode_and_save(std::string &msg) {
    BitmapFileHandler::byte* img = encode(msg);
    if(img == nullptr)
        throw std::runtime_error("Error while generating file");

    _handler.change_pixels(img);
    _handler.save_file(generate_path_name());
    delete[] img;
    img = nullptr;
}

const std::string& Encoder::generate_path_name() {
    srand(time(0));
    int random = rand() % 100000;
    std::string name = "_stega" + std::to_string(random) + ".bmp";
    return _path.replace(_path.find_last_of("."), 4, name);
}

Encoder::~Encoder() {

}