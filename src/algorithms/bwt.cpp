#include "bwt.h"

#include <algorithm>

// naive bwt
BWT::Result BWT::transform(const std::vector<uint8_t>& input) {
    // get all rotations of input
    std::vector<std::vector<uint8_t>> all_rotations{};
    all_rotations.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        all_rotations.push_back(rotate_vector(input, i));
    }

    // sort
    std::sort(all_rotations.begin(), all_rotations.end());

    // find inputs index in final sorted rotations vector
    // build transformed vector by concating the last byte the sorted rotations
    BWT::Result result{};
    for (size_t i = 0; i < all_rotations.size(); ++i) {
        const auto& current_rotation = all_rotations[i];
        if (current_rotation == input) {
            result.primary_index = i;
        }
        result.transformed.push_back(current_rotation.back());
    }

    return result;
}

std::vector<uint8_t> BWT::rotate_vector(const std::vector<uint8_t>& input, size_t n) {
    std::vector<uint8_t> rotated = input;
    n %= input.size();
    std::rotate(rotated.begin(), rotated.begin() + n, rotated.end());
    return rotated;
}

std::vector<uint8_t> BWT::inverse_transform(const Result& bwt_result) {
    std::vector<uint8_t> transformed = bwt_result.transformed;
    size_t primary_index = bwt_result.primary_index;

    // reconstruct all rotations
    std::vector<std::vector<uint8_t>> all_rotations{transformed.size()};
    for (size_t it = 0; it < transformed.size(); ++it) {
        for (size_t i = 0; i < transformed.size(); ++i) {
            auto& current_rotation = all_rotations[i];
            current_rotation.insert(current_rotation.begin(), transformed[i]);
        }
        std::sort(all_rotations.begin(), all_rotations.end());
    }

    return all_rotations[primary_index];
}