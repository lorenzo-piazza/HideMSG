#include "encoder111.h"

Encoder111::Encoder111(const std::string &path) : Encoder(path) {}
Encoder111::Encoder111(const std::string &path, const std::string key) : Encoder(path) {
    Encoder::set_key(key);
}

Encoder::byte* Encoder111::encode(const std::string &msg) {
    if(Encoder::key.empty()) {
        if(!can_embed_message(msg))
            throw std::runtime_error("Message too long for given image");
        
        Encoder::byte* img = Encoder::read_file();
        Encoder::byte* index = img;
        for(int i = 0; i < msg.length(); ++i) {
            char character = msg[i];
            for (int i = 7; i >= 0; --i) {
                bool bit = (character >> i) & 1;
                bool img_bit = *index & 00000001;
                if(bit != img_bit) {
                    if(img_bit)
                        *index = *index - 1;
                    else
                        *index = *index + 1;
                }
                ++index;
            }
        }
        return img;
    }
    else {
        //TODO: steganography with encryption
    }
}
Encoder::byte* Encoder111::decode() {}