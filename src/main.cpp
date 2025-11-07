#include <cassert>
#include <iostream>

#include "algorithms/bwt.h"
#include "algorithms/rle.h"
#include "utils/file_io.h"

int main() {
    // RLE
    std::cout << "=== RLE Test ===\n";
    std::string rle_str = "hello hello foo bar baz world";
    std::vector<uint8_t> rle_data{rle_str.begin(), rle_str.end()};

    auto rle_compressed = RLE::compress(rle_data);
    auto rle_decompressed = RLE::decompress(rle_compressed);

    std::cout << "input: " << rle_str << "\n";
    std::cout << "compressed: ";
    for (size_t i = 0; i < rle_compressed.size(); i += 2) {
        char byte = static_cast<char>(rle_compressed[i]);
        int count = static_cast<int>(rle_compressed[i + 1]);
        std::cout << "(" << byte << "," << count << ") ";
    }
    std::cout << "\n\n";

    assert(rle_data == rle_decompressed);

    // BWT
    std::cout << "=== BWT Test ===\n";
    std::string bwt_str = "what is this xd";
    std::vector<uint8_t> bwt_data{bwt_str.begin(), bwt_str.end()};

    auto bwt_result = BWT::transform(bwt_data);
    auto bwt_inverse = BWT::inverse_transform(bwt_result);

    std::cout << "input: " << bwt_str << "\n";
    std::cout << "transformed: ";
    for (auto byte : bwt_result.transformed) {
        std::cout << static_cast<char>(byte);
    }
    std::cout << " (index: " << bwt_result.primary_index << ")\n\n";

    assert(bwt_data == bwt_inverse);

    // FileIO
    std::cout << "=== File IO Test ===\n";
    FileIO reader(512);

    if (!reader.open_for_reading("sample_files/test.txt")) {
        std::cout << "failed to open file\n";
        return 1;
    }

    size_t total_bytes = 0;
    while (reader.has_more_blocks()) {
        total_bytes += reader.read_next_block().size();
    }

    std::cout << "read " << total_bytes << " bytes\n";
    reader.close_input();

    return 0;
}