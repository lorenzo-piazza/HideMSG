# HideMsg

HideMsg is a C++17 program designed to perform image steganography with optional AES encryption.
This project was developed by Lorenzo Piazza and Marco Borea as part of the Cryptography course at the University of Milan.

It allows users to embed a hidden message inside bitmap images and later extract and decrypt it if needed. 
The project was developed and tested on a MacBook with Apple Silicon (M1) running macOS Sequoia 15.5.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Tested on](#tested-on)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
  - [Encoding](#encoding)
  - [Decoding](#decoding)
- [Examples](#examples)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [Project Structure](#project-structure)
- [Contributors](#contributors)
- [License](#license)

---

## Introduction

HideMsg is a lightweight CLI tool that embeds textual messages into BMP images using bit-level steganography. 
It optionally supports AES encryption to ensure message confidentiality before embedding.

---

## Features

- Embed text messages in BMP images using LSB techniques
- Support for two encoding modes: `111` and `224`
- Optional AES encryption using Crypto++ library
- Message extraction with optional decryption
- Designed for Unix-like environments

---

## Tested on

- macOS Sequoia 15.5
- Apple Silicon M1
- C++17
- G++ (Apple Clang 17.0.0)
- Crypto++ (version 8.9.0)

---

## Requirements

- C++17 (or later)
- Crypto++ (version 8.9.0 or later)

---

## Installation

1. **Download Crypto++ (version 8.9.0)**

   Place the downloaded cryptopp folder inside HideMSG folder
   - [Official Website](https://www.cryptopp.com/)
   - [GitHub Repository](https://github.com/weidai11/cryptopp)

2. **Build Crypto++**

   Follow the official guide to build the library:  
   [Crypto++ Unix Build Guide](https://www.cryptopp.com/wiki/Linux_(Command_Line))

3. **Run make file**

   Reminder: To use the provided makefile place the downloaded cryptopp folder inside HideMSG folder.
   
   Execute the following:
   ```bash
      cd your/path/to/script/folder
      make
   ```

---

## Usage

### Encoding

```bash
./hidemsg.exe --encode --mode MODE --path PATH [--key KEY] MESSAGE
```

- `MODE`: `111` or `224`
- `PATH`: path to the cover image
- `KEY`: optional, AES key for encryption
- `MESSAGE`: text to embed

After the execution you'll find the stego image in PATH

### Decoding

```bash
./hidemsg.exe --decode --mode MODE --path PATH [--key KEY]
```

- `PATH`: path to the stego image
- `KEY`: optional, key for decryption

---

## Examples

### Embed a plain message

```bash
./hidemsg.exe --encode --mode 111 --path cover.bmp "This is a secret message"
```

### Decode a plain message

```bash
./hidemsg.exe --decode --mode 111 --path stego_image.bmp
```

### Embed an encrypted message

```bash
./hidemsg.exe --encode --mode 224 --path cover.bmp --key mysecretkey123 "Encrypted content"
```

### Decode an encrypted message

```bash
./hidemsg.exe --decode --mode 224 --path stego_image.bmp --key mysecretkey123
```

---

## Configuration

Encoding modes:

- `111`: 1 bit per RGB channel
- `224`: 2 bits in R, 2 bits in G, 4 bits in B. Futher explanation and motivation can be found here: (https://www.researchgate.net/publication/307802111_An_improved_LSB_based_image_steganography_technique_for_RGB_images)

---

## Troubleshooting

- **Linking errors**: Ensure the correct include and library paths for Crypto++
- **Unsupported image format**: Only BMP format is supported
- **Message too long**: Make sure the message size fits within the image capacity

---

## Project Structure

- `hidemsg.cpp`: main program logic
- `inputparser.*`: command-line argument parser
- `cipherhandler.*`: AES encryption and decryption
- `bitmapfilehandler.*`: BMP image handler
- `encoder.*`: base encoder logic
- `encoder111.*`, `encoder422.*`: specific encoding strategies

---

## Contributors

- Main Developer: Lorenzo Piazza, Marco Borea

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
