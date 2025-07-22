#include "encoder422.h"

Encoder422::Encoder422(const std::string &path) : Encoder(path)  {}
Encoder422::Encoder422(const std::string &path, const std::string key) : Encoder(path, key) {}

bool Encoder422::can_embed_message(const std::string &msg) {
    return msg.length() <= _handler.get_size_without_padding(); 
}

BitmapFileHandler::byte* Encoder422::encode(std::string &msg) {
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
    int row_padded = _handler.get_row_padded();
    int width = _handler.get_width() * 3; //* 3 needed to get width bytes number
    int padding_length = row_padded - width;
    int cont = 0; //cont % 3 = 0 -> byte blue, cont % 3 = 1 -> byte green, cont % 3 = 2 byte red
    for(int i = 0; i < msg.length(); ++i) {
        char character = msg[i];
        for (int j = 7; j >= 0;) {
            if(cont < width) {
                int bit_to_write = (cont % 3 == 0) ? 4 : 1;
                for(int z = bit_to_write * 2; z > 0; z = z >> 1) {
                    bool bit = (character >> j) & 1;
                    bool img_bit = *index & z;
                    if(bit != img_bit) {
                        if(img_bit)
                            *index = *index & (255 - z);
                        else
                            *index = *index | z;
                    }
                    --j;
                }
                ++cont;
                ++index;
            }
            else {
                index += padding_length; //skip padding bytes
                cont = 0;
            }
            
        }
    }
    index = nullptr;
    return img;
}
std::string Encoder422::decode() {
    //TODO
}