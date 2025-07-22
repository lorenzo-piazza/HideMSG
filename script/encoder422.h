#ifndef ENCODER422_H
#define ENCODER422_H

#include "encoder.h"

class Encoder422 : public Encoder {
    public:
        Encoder422(const std::string &path);
        Encoder422(const std::string &path, const std::string key);
        BitmapFileHandler::byte* encode(std::string &msg) override;
        std::string decode() override;
        bool can_embed_message(const std::string &msg) override;
    private:
};

#endif