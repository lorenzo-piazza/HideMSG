#include "encoder.h"

Encoder::Encoder(const std::string &path) : Encoder(path, "") {}
Encoder::Encoder(const std::string &path, const std::string key) : _handler(path), _path(path) {
    set_key(key);
}

void Encoder::set_key(const std::string &key) {
    //SHA3-256
    if(!key.empty()) {
        CryptoPP::SHA3_256 hash;
        hash.Update((const BitmapFileHandler::byte*)key.data(), key.size());
        this->_key.resize(hash.DigestSize());
        hash.Final((BitmapFileHandler::byte*)&this->_key[0]);
    }
}

bool Encoder::can_embed_message(const std::string &msg) {
    return msg.length() * 8 <= _handler.get_size_with_padding(); 
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