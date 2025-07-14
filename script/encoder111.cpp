#include "encoder111.h"

Encoder111::Encoder111(const std::string &path) : Encoder(path) {}
Encoder111::Encoder111(const std::string &path, const std::string key) : Encoder(path) {
    Encoder::set_key(key);
}

Encoder::byte* Encoder111::encode(std::string &msg) {
    if(Encoder::key.empty()) {
        //TODO: add comments
        msg.append(DELIMITER); //Adding delimiter

        if(!can_embed_message(msg))
            throw std::runtime_error("Message too long for given image");
        
        Encoder::byte* img = Encoder::read_file();
        Encoder::byte* index = img;
        for(int i = 0; i < msg.length(); ++i) {
            char character = msg[i];
            for (int j = 7; j >= 0; --j) {
                bool bit = (character >> j) & 1;
                bool img_bit = *index & 1;
                if(bit != img_bit) {
                    if(img_bit)
                        *index = *index - 1;
                    else
                        *index = *index + 1;
                }
                ++index;
            }
        }
        index = nullptr;
        return img;
    }
    else {
        //TODO: steganography with encryption
    }
}
std::string Encoder111::decode() {
    //initialize byte value as 00000000
    //OR with bit to be inserted
    //left shift by 1
    short delimiter_cont = 0;
    Encoder::byte* img = Encoder::read_file();
    Encoder::byte* index = img;
    std::string msg;
    while(delimiter_cont < 2 || *index != '\0') {
        Encoder::byte tmp = 0;
        for(int i = 0; i < 7; ++i, ++index) {
            bool bit = *index & 1;
            tmp = (tmp << 1) || bit;
        }
        std::string character(1, tmp); //create a string with length = 1 and copy inside tmp
        msg.append(character);
    }
    delete img;
    img = nullptr;
    index = nullptr;
    return msg;
}