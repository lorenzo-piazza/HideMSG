#ifndef ENCODER_H
#define ENCODER_H

#define HEADER_LENGTH 54
#define WIDTH_BYTE_N 18
#define HEIGHT_BYTE_N 22

#include <fstream>
#include <iostream>
#include <stdexcept>
#include "../cryptopp/rijndael.h"
#include "../cryptopp/sha3.h"

class Encoder {
    public:
        typedef unsigned char byte;
        typedef unsigned int size_type;
        
        Encoder(const std::string &path);
        Encoder(const std::string &path, const std::string key);
        ~Encoder();
        virtual byte* encode(const std::string &msg) = 0;
        virtual byte* decode() = 0;
        void print_size();
        void set_key(const std::string &key);
    protected:
        std::string key;
        byte* read_file();
        size_type get_size();
        bool can_embed_message(const std::string &msg);
    private:
        const std::string path;
        size_type width;
        size_type height;
        FILE* open_file_safe();
        
};

#endif