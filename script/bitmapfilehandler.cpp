#include "bitmapfilehandler.h"

BitmapFileHandler::BitmapFileHandler(const std::string &path) : _path(path) {
    FILE* f = open_file_safe();
    //extract image size using header bitmap
    fseek(f, 14, SEEK_SET);
    fread(&_DIB_size, sizeof(byte), 4, f);
    fseek(f, 0, SEEK_SET);
    _header = new byte[BITMAP_FILE_HEADER_SIZE + _DIB_size];
    fread(_header, sizeof(byte), BITMAP_FILE_HEADER_SIZE + _DIB_size, f);
    extract_dimensions();
    _pixels = new byte[_size];
    fread(_pixels, sizeof(byte), _size, f);
    fclose(f);
}

BitmapFileHandler::~BitmapFileHandler() {
    delete[] _header;
    delete[] _pixels;
    _header = nullptr;
    _pixels = nullptr;
}

void BitmapFileHandler::extract_dimensions() {
    if(_header != nullptr) {
        _width = *(int*)&_header[WIDTH_BYTE_N];
        _height = *(int*)&_header[HEIGHT_BYTE_N];
        _size = *(int*)&_header[SIZE_BYTE_N];
    }
}

FILE* BitmapFileHandler::open_file_safe() {
    FILE* f = fopen(_path.c_str(), "rb");
    if(f == NULL)
        throw std::runtime_error("Invalid path");
    return f;
}

BitmapFileHandler::byte* BitmapFileHandler::get_pixels() {
    byte* pixels_cpy = new byte[_size];
    if(pixels_cpy != nullptr) {
        std::memcpy(pixels_cpy, _pixels, _size);
        return pixels_cpy;
    }
    return nullptr;
}

BitmapFileHandler::size_type BitmapFileHandler::get_size_with_padding() const {
    return _size;
}

BitmapFileHandler::size_type BitmapFileHandler::get_size_without_padding() const {
    return _height * _width;
}

const BitmapFileHandler::byte* BitmapFileHandler::get_header() const {
    byte* header_cpy = new byte[BITMAP_FILE_HEADER_SIZE + _DIB_size];
    if(header_cpy != nullptr) {
        std::memcpy(header_cpy, _header, BITMAP_FILE_HEADER_SIZE + _DIB_size);
        return header_cpy;
    }
    return nullptr;
}

BitmapFileHandler::size_type BitmapFileHandler::get_header_size() const {
    return BITMAP_FILE_HEADER_SIZE + _DIB_size;
}

BitmapFileHandler::size_type BitmapFileHandler::get_width() const {
    return _width;
}

BitmapFileHandler::size_type BitmapFileHandler::get_height() const {
    return _height;
}

BitmapFileHandler::size_type BitmapFileHandler::get_row_padded() const {
    return (_width * 3 + 3) & (~3);
}

void BitmapFileHandler::change_pixels(const byte* pixels) {
    if(pixels != nullptr)
        std::memcpy(_pixels, pixels, _size);
}

void BitmapFileHandler::save_file(const std::string& path) {
    byte* buffer = new BitmapFileHandler::byte[BITMAP_FILE_HEADER_SIZE + _DIB_size + _size];
    if(buffer == nullptr)
        throw std::runtime_error("Something went wrong");

    std::memcpy(buffer, _header, BITMAP_FILE_HEADER_SIZE + _DIB_size);
    std::memcpy(buffer + BITMAP_FILE_HEADER_SIZE + _DIB_size, _pixels, _size);

    FILE* stega_f = fopen(path.c_str(), "wb");
    if(stega_f == nullptr)
        throw std::runtime_error("Something went wrong");
   
    fwrite(buffer, sizeof(BitmapFileHandler::byte), BITMAP_FILE_HEADER_SIZE + _DIB_size + _size, stega_f);
    fclose(stega_f);
    delete[] buffer;
    buffer = nullptr;
}