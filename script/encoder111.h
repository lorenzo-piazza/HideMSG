#ifndef ENCODER111_H
#define ENCODER111_H

#include "encoder.h"

class Encoder111 : public Encoder {
    public:
        Encoder111(const std::string &path);
        Encoder111(const std::string &path, const std::string key);
        byte* encode(const std::string &msg) override;
        byte* decode() override;
    private:
};

#endif