#include "encoder.h"

Encoder::Encoder(const std::string &path) : path(path) {}
Encoder::Encoder(const std::string &path, const std::string key) : path(path) {
    set_key(key);
}

void Encoder::print_size() {
    byte* p = read_file();
    std::cout << width << " " << height << std::endl;
    std::cout << p << std::endl;
    delete p;
    p = nullptr;
}

void Encoder::set_key(const std::string &key) {
    if(key.empty())
        throw "Empty key";

    //SHA3-256
    CryptoPP::SHA3_256 hash;
    hash.Update((const byte*)key.data(), key.size());
    this->key.resize(hash.DigestSize());
    hash.Final((byte*)&this->key[0]);
}

bool Encoder::can_embed_message(const std::string &msg) {
    return msg.length() * 8 <= get_size(); 
}

Encoder::size_type Encoder::get_size() {
    FILE* f = open_file_safe();
    //extract image size using header bitmap
    byte header[HEADER_LENGTH];
    fread(header, sizeof(byte), HEADER_LENGTH, f);
    
    width = *(int*)&header[WIDTH_BYTE_N];
    height = *(int*)&header[HEIGHT_BYTE_N];
    fclose(f);
    return 3 * width * height;
}

Encoder::byte* Encoder::read_file() {
    //open the file
    FILE* f = open_file_safe();
    fseek(f, HEADER_LENGTH, 0); //jump header
    //read image and save to heap
    size_type size = get_size();
    byte* cover_image = new byte[size];
    fread(cover_image, sizeof(byte), size, f);
    fclose(f);
    return cover_image;
}

FILE* Encoder::open_file_safe() {
    FILE* f = fopen(path.c_str(), "rb");
    if(f == NULL) {
        std::cerr << "Path non valido" << std::endl;
        exit(EXIT_FAILURE);
    }
    return f;
}

Encoder::~Encoder() {

}