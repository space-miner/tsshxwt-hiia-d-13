#ifndef RLE_H
#define RLE_H

#include <cstdint>
#include <vector>

class RLE {
   public:
    static std::vector<uint8_t> compress(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decompress(const std::vector<uint8_t>& compressed);
};

#endif