#include "encoder111.h"

Encoder111::Encoder111(const std::string &path) : Encoder(path)  {}
Encoder111::Encoder111(const std::string &path, const std::string key) : Encoder(path, key) {}

bool Encoder111::can_embed_message(const std::string &msg) {
    return msg.length() * 8 <= _handler.get_size_with_padding(); 
}

BitmapFileHandler::byte* Encoder111::encode(std::string &msg) {
    if(!Encoder::_key.empty()) {
        msg = _aes.encrypt(msg);
    }
    //forall character c in msg and forall bit b of c
    //copy b into the lsb of one byte of img
    msg.append(DELIMITER); //Adding delimiter

    // Ensure the message (plus delimiter) will fit
    if(!can_embed_message(msg))
        throw std::runtime_error("Message too long for given image");
    
    BitmapFileHandler::byte* img = _handler.get_pixels();
    if(img == nullptr)         
        throw std::runtime_error("Error reading file");
    
    // Embed each bit of each character into pixel LSB
    BitmapFileHandler::byte* index = img;
    for(int i = 0; i < msg.length(); ++i) {
        char character = msg[i];
        // Process bits from MSB to LSB
        for (int j = 7; j >= 0; --j) { 
            bool bit = (character >> j) & 1;
            bool img_bit = *index & 1;
            // Flip LSB if it doesn't match message bit
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
    short delimiter_cont = 0;
    int image_cont = 0;
    BitmapFileHandler::byte* img = _handler.get_pixels();
    if(img == nullptr)
        throw std::runtime_error("Error reading file");
    
    std::string msg;
    BitmapFileHandler::size_type size = _handler.get_size_with_padding();
    // Read until delimiter appears three times or end of data
    while(delimiter_cont < 3 && image_cont < size) {
        /*
            initialize byte value as 00000000
            OR with bit to be inserted
            left shift by 1
        */
        BitmapFileHandler::byte tmp = 0;
        for(int i = 0; i < 8 && image_cont < size; ++i, ++image_cont) {
            bool bit = img[image_cont] & 1;
            tmp = (tmp << 1) | bit;
        }
        if(tmp == '&')
            ++delimiter_cont;
        else
            delimiter_cont = 0;
        msg += tmp;
    }
    delete[] img;
    img = nullptr;
    // Remove delimiter characters from message
    msg = msg.substr(0, msg.length() - 3);
    if(!Encoder::_key.empty()) {
        msg = _aes.decrypt(msg);
    }
    return msg;
}