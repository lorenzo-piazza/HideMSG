#ifndef BITMAPFILEHANDLER_H
#define BITMAPFILEHANDLER_H

#include <stdio.h>
#include <iostream>
#include <stdexcept>

#define BITMAP_FILE_HEADER_SIZE 14
#define WIDTH_BYTE_N 18
#define HEIGHT_BYTE_N 22
#define SIZE_BYTE_N 34

class BitmapFileHandler {
    public:
        typedef unsigned char byte;
        typedef unsigned int size_type;
        BitmapFileHandler(const std::string &path);
        ~BitmapFileHandler();
        const byte* get_header() const;
        size_type get_header_size() const;
        size_type get_width() const;
        size_type get_height() const;
        size_type get_row_padded() const;

        byte* get_pixels();
        size_type get_size_with_padding() const;
        size_type get_size_without_padding() const;

        void change_pixels(const byte* pixels);
        void save_file(const std::string& path);
    private:
        FILE* open_file_safe();
        void extract_dimensions();
        const std::string _path;
        size_type _width;
        size_type _height;
        size_type _size;
        size_type _DIB_size;
        byte* _header;
        byte* _pixels;
};

#endif