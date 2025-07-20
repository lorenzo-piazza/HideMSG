#include "../cryptopp/osrng.h"         // AutoSeededRandomPool
#include "../cryptopp/cryptlib.h"
#include "../cryptopp/hex.h"           // HexEncoder
#include "../cryptopp/filters.h"       // StreamTransformationFilter
#include "../cryptopp/aes.h"
#include "../cryptopp/modes.h"         // OFB_Mode
#include "../cryptopp/sha3.h"          // SHA3_256

#include <string>
class CipherHandler {
    public:
        CipherHandler(const std::string& passphrase);
        std::string encrypt(const std::string& plainText);
        std::string decrypt(const std::string& cipherHex);
    private:
        CryptoPP::SecByteBlock _key, _iv;
        const std::string xorStrings(const std::string& s1, const std::string& s2) const;
};