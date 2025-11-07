#include "rle.h"

std::vector<uint8_t> RLE::compress(const std::vector<uint8_t>& input) {
    std::vector<uint8_t> compressed{};
    compressed.reserve(input.size() * 2);

    if (input.empty()) return compressed;

    for (size_t i = 0; i < input.size();) {
        uint8_t byte = input[i];
        uint8_t run_length = 1;

        // count how many consecutive bytes are the same (capped at 255)
        while (i + run_length < input.size() && input[i + run_length] == byte && run_length < 255) {
            run_length++;
        }

        compressed.push_back(byte);
        compressed.push_back(run_length);
        i += run_length;
    }

    return compressed;
}

std::vector<uint8_t> RLE::decompress(const std::vector<uint8_t>& compressed) {
    std::vector<uint8_t> decompressed{};

    if (compressed.size() % 2 != 0) {
        return decompressed;
    }

    // pre-allocate buffer
    size_t n = 0;
    for (size_t i = 0; i < compressed.size(); i += 2) {
        n += compressed[i + 1];
    }
    decompressed.reserve(n);

    for (size_t i = 0; i < compressed.size(); i += 2) {
        uint8_t byte = compressed[i];
        uint8_t run_length = compressed[i + 1];
        decompressed.insert(decompressed.end(), run_length, byte);
    }

    return decompressed;
}