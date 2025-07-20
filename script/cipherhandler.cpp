#include "cipherhandler.h"

CipherHandler::CipherHandler(const std::string& passphrase) {
    CryptoPP::SecByteBlock digest(CryptoPP::SHA3_256::DIGESTSIZE);
    CryptoPP::SHA3_256().CalculateDigest(digest, 
        reinterpret_cast<const CryptoPP::byte*>(passphrase.data()), 
        passphrase.size());

    // 2) Set key to 32 byte (AES-256)
    _key = digest;

    // 3) Generate IV
    const std::string salt = "notsecretsalt";
    const std::string xor_passphrase = xorStrings(passphrase, salt);
    CryptoPP::SecByteBlock fullDigest(CryptoPP::SHA3_256::DIGESTSIZE);
    CryptoPP::SHA3_256 hash;
    hash.CalculateDigest(fullDigest, reinterpret_cast<const CryptoPP::byte*>(xor_passphrase.data()), xor_passphrase.size());

    // Prendi solo i primi 16 byte
    CryptoPP::SecByteBlock iv(fullDigest, 16);
    _iv = iv;
}

const std::string CipherHandler::xorStrings(const std::string& s1, const std::string& s2) const {
    std::string result;
    size_t len = std::min(s1.size(), s2.size());
    result.reserve(len);

    for (size_t i = 0; i < len; ++i) {
        result.push_back(s1[i] ^ s2[i]);
    }
    return result;
}

std::string CipherHandler::encrypt(const std::string& plainText) {
    std::string cipher;
    CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKeyWithIV(_key, _key.size(), _iv);

    CryptoPP::StringSource(plainText, true,
            new CryptoPP::StreamTransformationFilter(enc,
            new CryptoPP::StringSink(cipher)
        )
    );
    // hex-encode cast before return
    std::string hex;
    CryptoPP::StringSource(cipher, true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(hex))
    );
    return hex;
}

std::string CipherHandler::decrypt(const std::string& cipherHex) {
    // 1) hex decoding
    std::string cipher;
    CryptoPP::StringSource(cipherHex, true,
        new CryptoPP::HexDecoder(new CryptoPP::StringSink(cipher))
    );

    // 2) decoding
    std::string recovered;
    CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(_key, _key.size(), _iv);

    CryptoPP::StringSource(cipher, true,
            new CryptoPP::StreamTransformationFilter(dec,
            new CryptoPP::StringSink(recovered)
        )
    );
    return recovered;
}