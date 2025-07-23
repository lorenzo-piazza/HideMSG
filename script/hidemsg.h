#ifndef HIDEMSG_H
#define HIDEMSG_H
#include "inputparser.h"
#include "encoder111.h"
#include "encoder422.h"
#include <iostream>
#include <optional>
#include <string>
#include <stdexcept>

#define ENCODER111 111
#define ENCODER224 224

int main(int argc, char* argv[]);
Encoder* create_encoder(const Options& opt);
#endif
