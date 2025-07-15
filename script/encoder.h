#ifndef ENCODER_H
#define ENCODER_H

#define DELIMITER "&&&"

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include "../cryptopp/rijndael.h"
#include "../cryptopp/sha3.h"
#include "bitmapfilehandler.h"
#include <cstdlib>

class Encoder {
    public:
        Encoder(const std::string &path);
        Encoder(const std::string &path, const std::string key);
        ~Encoder();
        virtual BitmapFileHandler::byte* encode(std::string &msg) = 0;
        virtual std::string decode() = 0;
        void encode_and_save(std::string &msg);

        void set_key(const std::string &key);
    protected:
        std::string _key;
        BitmapFileHandler _handler;
        bool can_embed_message(const std::string &msg);
    private:
        std::string _path;
        const std::string& generate_path_name();
};

#endif