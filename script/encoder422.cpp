#include "encoder422.h"

Encoder422::Encoder422(const std::string &path) : Encoder(path)  {}
Encoder422::Encoder422(const std::string &path, const std::string key) : Encoder(path, key) {}

// Determine if the message length (in characters) can fit into the image data (no padding)
bool Encoder422::can_embed_message(const std::string &msg) {
    // Here each character consumes one byte (so one pixel) of embedding space
    return msg.length() <= _handler.get_size_without_padding(); 
}

// Embed the message into the image buffer using a 4:2:2 scheme
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
    // Iterate over each character in the message to embed
    for(int i = 0; i < msg.length(); ++i) {
        char character = msg[i]; // Get the current character to encode
        // Read embedding bits from the most significant bit (bit 7)
        for (int j = 7; j >= 0;) {
            // Check if we are still within the width of the image row
            if(cont < width) {
                // Determine how many bits to modify based on pixel position:
                // every third pixel gets 4 bits, otherwise just 1 bit
                int bit_to_write = (cont % 3 == 0) ? 4 : 1;
                // Iterate over each bit mask (from MSB to LSB) depending on bit_to_write
                for(int z = bit_to_write * 2; z > 0; z = z >> 1) {
                    bool bit = (character >> j) & 1; // Extract the j-th bit of the character
                    bool img_bit = *index & z;  // Extract the corresponding bit from the image byte
                    if(bit != img_bit) {
                        // If the bits differ, we update the image bit
                        if(img_bit)
                            *index = *index & (255 - z); // Clear the bit (set to 0)
                        else
                            *index = *index | z; // Set the bit (set to 1)
                    }
                    --j; // Move to the next bit of the character
                }
                ++cont; // Move to the next pixel component
                ++index;  // Move to the next byte in the image data
            }
            else {
                // If we reached the end of a row, skip padding bytes
                index += padding_length;
                cont = 0; // Reset pixel counter for the new row
            }
            
        }
    }
    index = nullptr;
    return img;
}
std::string Encoder422::decode() {
    short delimiter_cont = 0;
    int cont = 0;
    BitmapFileHandler::byte* img = _handler.get_pixels();
    if(img == nullptr)
        throw std::runtime_error("Error reading file");
    
    std::string msg;
    int size = _handler.get_size_with_padding();
    int row_padded = _handler.get_row_padded();
    int width = _handler.get_width() * 3; //* 3 needed to get width bytes number
    int padding_length = row_padded - width;

    // Read until three delimiters ('&') or end of image data
    while(delimiter_cont < 3 && cont < size) {
        for(int z = 0; z < width && delimiter_cont < 3; z += 3, ++cont) {
            BitmapFileHandler::byte tmp = 0;
            tmp = (tmp | (img[cont] & 15)) << 2; // Extract 4 LSBs from the first byte, shift left to make space
            tmp = (tmp | (img[++cont] & 3)) << 2; // Extract 2 LSBs from the second byte, shift left again
            tmp = tmp | (img[++cont] & 3); // Extract 2 LSBs from the third byte, no shift needed here
            if(tmp == '&')
                ++delimiter_cont;
            msg += tmp; 
        }
        // After reading one image row, skip padding bytes (if present)
        cont += padding_length;
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