#ifndef FILE_IO_H
#define FILE_IO_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
 
class FileIO {
   private:
    size_t block_size_;
    std::ifstream file_reader_;
    std::ofstream file_writer_;

   public:
    FileIO(size_t block_size);

    ~FileIO();

    bool open_for_reading(const std::string& filename);
    std::vector<uint8_t> read_next_block();
    bool has_more_blocks();
    void close_input();

    bool open_for_writing(const std::string& filename);
    void write_block(const std::vector<uint8_t>& data);
    void close_output();

    size_t get_block_size() const;
    bool is_input_open() const;
    bool is_output_open() const;
};

#endif  
