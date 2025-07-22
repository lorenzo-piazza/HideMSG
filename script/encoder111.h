#ifndef ENCODER111_H
#define ENCODER111_H

#include "encoder.h"

class Encoder111 : public Encoder {
    public:
        Encoder111(const std::string &path);
        Encoder111(const std::string &path, const std::string key);
        BitmapFileHandler::byte* encode(std::string &msg) override;
        std::string decode() override;
        bool can_embed_message(const std::string &msg) override;
    private:
};

#endif