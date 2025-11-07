#ifndef BWT_H
#define BWT_H

#include <cstdint>
#include <vector>

class BWT {
   private:
    static std::vector<uint8_t> rotate_vector(const std::vector<uint8_t>& input, size_t n);

   public:
    struct Result {
        std::vector<uint8_t> transformed;
        size_t primary_index;
    };

    static Result transform(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> inverse_transform(const Result& bwt_result);
};

#endif