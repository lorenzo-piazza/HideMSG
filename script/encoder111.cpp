#include "encoder111.h"

Encoder111::Encoder111(const std::string &path) : Encoder(path)  {}
Encoder111::Encoder111(const std::string &path, const std::string key) : Encoder(path, key) {}

BitmapFileHandler::byte* Encoder111::encode(std::string &msg) {
    if(!Encoder::_key.empty()) {
        msg = _aes.encrypt(msg);
    }
    //forall character c in msg and forall bit b of c
    //copy b into the lsb of one byte of img
    msg.append(DELIMITER); //Adding delimiter

    if(!can_embed_message(msg))
        throw std::runtime_error("Message too long for given image");
    
    BitmapFileHandler::byte* img = _handler.get_pixels();
    if(img == nullptr)         
        throw std::runtime_error("Error reading file");
    
    BitmapFileHandler::byte* index = img;
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
std::string Encoder111::decode() {
    //initialize byte value as 00000000
    //OR with bit to be inserted
    //left shift by 1
    short delimiter_cont = 0;
    int image_cont = 0;
    BitmapFileHandler::byte* img = _handler.get_pixels();
    if(img == nullptr)
        throw std::runtime_error("Error reading file");
    
    std::string msg;
    BitmapFileHandler::size_type size = _handler.get_size_with_padding();
    while(delimiter_cont < 3 && image_cont < size) {
        BitmapFileHandler::byte tmp = 0;
        for(int i = 0; i < 8 && image_cont < size; ++i, ++image_cont) {
            bool bit = img[image_cont] & 1;
            tmp = (tmp << 1) | bit;
        }
        if(tmp == '&')
            ++delimiter_cont;
        msg += tmp;
    }
    delete[] img;
    img = nullptr;
    msg = msg.substr(0, msg.length() - 3);
    if(!Encoder::_key.empty()) {
        msg = _aes.decrypt(msg);
    }
    return msg;
}